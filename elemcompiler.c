/*
 * helper functions for calculator
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "elemcompiler.h"
#include "codegen.h"

static uint8_t offsetCount = 0;
static uint8_t branchCount = 0;
static uint8_t litstrCount = 2;
static uint8_t symCount = 0;

static FILE *fp;
static char *text;
static char *data;



/* symbol table */
/* hash a symbol */
static unsigned symhash (char *sym)
{
    unsigned int hash = 0;
    unsigned c;
    
    while ((c = (*(sym++)))) 
        hash = hash * 9 ^ c;

    return hash;
}

struct symbol* lookup (char *sym)
{
    struct symbol *sp = &symtab[symhash(sym)%NHASH];
    int scount = NHASH;     /* how many have we looked at */

    while (--scount >= 0) {
        if (sp->name && !strcmp(sp->name, sym))
            return sp;

        if (!sp->name) {    /* new entry */
            sp->name = strdup(sym);
            sp->value = 0;
            sp->offset = 0;

            ++symCount;

            return sp;
        }

        if (++sp >= symtab+NHASH)
            sp = symtab;    /* try the next entry */
    }

    yyerror("symbol table overflow\n");
    abort(); /* tried them all, table is full */
}

struct ast* newast (int nodetype, struct ast *l, struct ast *r)
{
    struct ast *a = (struct ast*) malloc(sizeof(struct ast));

    if (!a) {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = nodetype;
    a->l = l;
    a->r = r;

    return a;
}

struct ast* newnum (int64_t num)
{
    struct numval *a = (struct numval*) malloc(sizeof(struct numval));

    if (!a) {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = 'K';
    a->number = num;

    return (struct ast*) a;
}

struct ast* newprint (int nodetype, struct ast *exp, char *str)
{
    struct print *a = (struct print*) malloc(sizeof(struct print));
    struct litstr *ls = (struct litstr*) malloc(sizeof(struct litstr));

    if (!a) {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = nodetype;

    if (nodetype == 'A')
        a->arg.exp = exp;
    else {
        char buf[21];

        sprintf(buf, "LC%u", litstrCount);
        data = buildDataSection(data, defineString(buf, str));

        ls->str = str;
        ls->label = litstrCount++;
        a->arg.ls = ls;
    }

    return (struct ast*) a;
}

struct ast* newref (struct symbol *s)
{
    struct symref *a = (struct symref*) malloc(sizeof(struct symref));

    if (!a) {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = 'V';
    a->s = s;

    return (struct ast*) a;
}

struct ast* newasgn (struct symbol *s, struct ast *v)
{
    struct symasgn *a = (struct symasgn*) malloc(sizeof(struct symasgn));

    if (!a) {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = '=';
    a->s = s;
    a->v = v;

    return (struct ast*) a;
}

struct ast* newcond (struct ast *cond, struct ast *tl)
{
    struct cond *a = (struct cond*) malloc(sizeof(struct cond));

    if (!a) {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = 'C';
    a->cond = cond;
    a->tl = tl;

    return (struct ast*) a;
}

struct ast* newloop (struct ast *from, struct ast *to, struct ast *inc, struct ast *tl)
{
    struct loop *a = (struct loop*) malloc(sizeof(struct loop));

    if (!a) {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = 'L';
    a->from = from;
    a->to = to;
    a->inc = inc;
    a->tl = tl;

    return (struct ast*) a;
}

/* free a tree of ASTs */
void treefree (struct ast *a)
{
    switch (a->nodetype) {
        /* two subtrees */
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case 'E':
            treefree(a->r);

        /* one subtrees */
        case 'M':
            treefree(a->l);

        /* no subtree */
        case 'K':
        case 'V':
            break;

        /* print expression */
        case 'A':
            treefree(((struct print*)a)->arg.exp);
            break;

        /* print string */
        case 'S':
            free(((struct print*)a)->arg.ls->str);
            free(((struct print*)a)->arg.ls);
            break;

        /* assignment */
        case '=':
            treefree(((struct symasgn*)a)->v);
            break;

        /* condtion */
        case 'C':
            treefree(((struct cond*)a)->cond);

            if (((struct cond*)a)->tl)
                treefree(((struct cond*)a)->tl);

            break;

        /* loop */
        case 'L':
            treefree(((struct loop*)a)->from);
            treefree(((struct loop*)a)->to);
            treefree(((struct loop*)a)->inc);

            if (((struct loop*)a)->tl)
                treefree(((struct loop*)a)->tl);

            break;

        default:
            printf("internal error: free bad node %c\n", a->nodetype);
    }

    free(a); /*always free the node itself */
}

void gen_asm (struct ast *a)
{
    struct symbol *s;
    char buf[21];

    if (!a) {
        yyerror("internal error, null eval");

        return;
    }

    switch (a->nodetype) {
        /* constant */
        case 'K':
            //printf("\n# constant\n");

            text = buildTextSection(text, sub("$8", "%rsp"));
            sprintf(buf, "$%ld", ((struct numval*)a)->number);
            text = buildTextSection(text, movl(buf, "%eax"));
            text = buildTextSection(text, movq("%rax", "(%rsp)"));

            break;
            
        /*symbol reference */
        case 'V':
            //printf("\n# reference\n");

            s = lookup(((struct symasgn*)a)->s->name);

            if (s->offset == 0) {
                s->offset = (++offsetCount) * 8;
                sprintf(buf, "-%u(%%rbp)", s->offset);
                text = buildTextSection(text, movq("$0", buf));
            }

            sprintf(buf, "-%u(%%rbp)", s->offset);
            text = buildTextSection(text, movq(buf, "%rax"));
            text = buildTextSection(text, sub("$8", "%rsp"));
            text = buildTextSection(text, movq("%rax", "(%rsp)"));

            break;
            
        /* print expression */
        case 'A':
            gen_asm(((struct print*)a)->arg.exp);

            //printf("\n# print A\n");

            text = buildTextSection(text, movq("(%rsp)", "%rax"));
            text = buildTextSection(text, add("$8", "%rsp"));
            text = buildTextSection(text, movq("%rax", "%rsi"));
            text = buildTextSection(text, movl("$.LC0", "%edi"));
            text = buildTextSection(text, movl("$0", "%eax"));
            text = buildTextSection(text, sysCallPrint());

            break;
            
        /* print literal string */
        case 'S':
            //printf("\n# print S\n");

            sprintf(buf, "$.LC%u", ((struct print*)a)->arg.ls->label);
            text = buildTextSection(text, movl(buf, "%esi"));
            text = buildTextSection(text, movl("$.LC1", "%edi"));
            text = buildTextSection(text, movl("$0", "%eax"));
            text = buildTextSection(text, sysCallPrint());
            break;

            /* assignment */
        case '=':
            s = lookup(((struct symasgn*)a)->s->name);

            if (s->offset == 0) {
               s->offset = (++offsetCount) * 8;
            }

            gen_asm(((struct symasgn*)a)->v);

            //printf("\n# assignment\n");

            text = buildTextSection(text, movq("(%rsp)", "%rax"));
            text = buildTextSection(text, add("$8", "%rsp"));
            sprintf(buf, "-%u(%%rbp)", s->offset);
            text = buildTextSection(text, movq("%rax", buf));
            break;

            /* expressions */
        case '+':
            gen_asm(a->r);
            gen_asm(a->l);

            //printf("\n# addition\n");

            text = buildTextSection(text, movq("(%rsp)", "%rdx"));
            text = buildTextSection(text, add("$8", "%rsp"));
            text = buildTextSection(text, movq("(%rsp)", "%rax"));
            text = buildTextSection(text, add("$8", "%rsp"));
            text = buildTextSection(text, add("%rdx", "%rax"));
            text = buildTextSection(text, sub("$8", "%rsp"));
            text = buildTextSection(text, movq("%rax", "(%rsp)"));

            break;
        case '-':
            gen_asm(a->r);
            gen_asm(a->l);

            //printf("\n# subtraction\n");

            text = buildTextSection(text, movq("(%rsp)", "%rax"));
            text = buildTextSection(text, add("$8", "%rsp"));
            text = buildTextSection(text, sub("(%rsp)", "%rax"));
            text = buildTextSection(text, movq("%rax", "(%rsp)"));

            break;
        case '*':
            gen_asm(a->r);
            gen_asm(a->l);

            //printf("\n# multiplication\n");

            text = buildTextSection(text, movq("(%rsp)", "%rax"));
            text = buildTextSection(text, add("$8", "%rsp"));
            text = buildTextSection(text, imul("(%rsp)", "%rax"));
            text = buildTextSection(text, movq("%rax", "(%rsp)"));

            break;
        case '/':
            gen_asm(a->r);
            gen_asm(a->l);

            //printf("\n# division\n");

            text = buildTextSection(text, movq("(%rsp)", "%rax"));
            text = buildTextSection(text, add("$8", "%rsp"));
            text = buildTextSection(text, cqto());
            text = buildTextSection(text, idiv("(%rsp)"));
            text = buildTextSection(text, movq("%rax", "(%rsp)"));

            break;
        case '%':
            gen_asm(a->r);
            gen_asm(a->l);

            //printf("\n# modulation\n");

            text = buildTextSection(text, movq("(%rsp)", "%rax"));
            text = buildTextSection(text, add("$8", "%rsp"));
            text = buildTextSection(text, cqto());
            text = buildTextSection(text, idiv("(%rsp)"));
            text = buildTextSection(text, movq("%rdx", "(%rsp)"));

            break;
        case 'M':
            gen_asm(a->l);

            //printf("\n# Negation\n");

            text = buildTextSection(text, movq("(%rsp)", "%rax"));
            text = buildTextSection(text, neg("%rax"));
            text = buildTextSection(text, movq("%rax", "(%rsp)"));

            break;

            /* control flow */
            /* null expressions allowed in the grammar, so check for them */

            /* condition */
        case 'C':
            gen_asm(((struct cond*)a)->cond);

            //printf("\n# Condition\n");

            text = buildTextSection(text, compare("$0", "(%rsp)"));
            sprintf(buf, "L%u", branchCount);
            text = buildTextSection(text, buildJump("je", buf));

            if (((struct cond*)a)->tl)
                gen_asm(((struct cond*)a)->tl);

            sprintf(buf, "L%u", branchCount++);
            text = buildTextSection(text, buildLabel(buf));

            break;

            /* loop */
        case 'L':
            if (((struct loop*)a)->tl) {
                //printf("\n# Loop\n");

                sprintf(buf, "$%ld", eval(((struct loop*)a)->from));
                text = buildTextSection(text, movl(buf, "%eax"));
                text = buildTextSection(text, movq("%rax", "from(%rip)"));
                sprintf(buf, "L%u", branchCount);
                text = buildTextSection(text, buildJump("jmp", buf));
                sprintf(buf, "L%u", ++branchCount);
                text = buildTextSection(text, buildLabel(buf));

                gen_asm(((struct loop*)a)->tl);

                text = buildTextSection(text, movq("from(%rip)", "%rdx"));
                sprintf(buf, "$%ld", eval(((struct loop*)a)->inc));
                text = buildTextSection(text, movl(buf, "%eax"));
                text = buildTextSection(text, add("%rdx", "%rax"));
                text = buildTextSection(text, movq("%rax", "from(%rip)"));
                sprintf(buf, "L%u", (branchCount - 1));
                text = buildTextSection(text, buildLabel(buf));
                sprintf(buf, "$%ld", eval(((struct loop*)a)->to));
                text = buildTextSection(text, movl(buf, "%eax"));
                text = buildTextSection(text, compare("%rax", "from(%rip)"));
                sprintf(buf, "L%u", branchCount);
                text = buildTextSection(text, buildJump("jle", buf));

                ++branchCount;
            }

            break;

            /* list of statements */
        case 'E':
            gen_asm(a->l);
            gen_asm(a->r);
            break;

        default:
            printf("internal error: bad node %c\n", a->nodetype);
    }
}

int64_t eval (struct ast *a)
{
    int64_t v = 0;

    if (!a) {
        yyerror("internal error, null eval");

        return 0;
    }

    switch (a->nodetype) {
        /* constant */
        case 'K':
            v = ((struct numval*)a)->number;
            break;
            
        /*symbol reference */
        case 'V':
            v = ((struct symref*)a)->s->value;
            break;
            
        /* print expression */
        case 'A':
            v = eval(((struct print*)a)->arg.exp);
            printf("%ld\n", v);
            break;
            
        /* print literal string */
        case 'S':
            printf("%s\n", (((struct print*)a)->arg.ls->str));
            break;

            /* assignment */
        case '=':
            v = ((struct symasgn*)a)->s->value = eval(((struct symasgn*)a)->v);
            break;

            /* expressions */
        case '+':
            v = eval(a->l) + eval(a->r);
            break;
        case '-':
            v = eval(a->l) - eval(a->r);
            break;
        case '*':
            v = eval(a->l) * eval(a->r);
            break;
        case '/':
            v = eval(a->l) / eval(a->r);
            break;
        case '%':
            v = eval(a->l) % eval(a->r);
            break;
        case 'M':
            v = -eval(a->l);
            break;

            /* control flow */
            /* null expressions allowed in the grammar, so check for them */

            /* condition */
        case 'C':
            if (eval(((struct cond*)a)->cond) != 0) {
                if (((struct cond*)a)->tl)
                    v = eval(((struct cond*)a)->tl);
            }
            break;

            /* loop */
        case 'L':
            if (((struct loop*)a)->tl) {
                int64_t count = eval(((struct loop*)a)->from);
                int64_t to = eval(((struct loop*)a)->to);
                int64_t inc = eval(((struct loop*)a)->inc);

                while (count <= to) {
                    v = eval(((struct loop*)a)->tl);
                    count += inc;
                }
            }

            break;

            /* list of statements */
        case 'E':
            eval(a->l);
            v = eval(a->r);
            break;

        default:
            printf("internal error: bad node %c\n", a->nodetype);
    }

    return v;
}

void yyerror (char *s, ...)
{
    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

int main(int argc, char **argv)
{
    extern FILE *yyin;
    char *asmFile;
    char *ptr;
    char buf[21];

    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]);
            return 1;
        }
    }
    else {
        printf("\nPlease specify a source file.\n\n");
        return 1;
    }

    text = (char *) malloc(sizeof(char));
    data = (char *) malloc(sizeof(char));
    *(text) = '\0';
    *(data) = '\0';
    asmFile = strdup(argv[1]);
    ptr = strchr(asmFile, '.');

    *(ptr+1) = 's';
    *(ptr+2) = '\0';

    fp = createFile(asmFile);

    printf("Start Parsing ...\n");
    printf("...\n");
    printf("...\n");

    if (yyparse()) {
        printf("\nParsing Error\n");
        closeFile(fp);

        return -1;
    }

    sprintf(buf, "$%u", (symCount+1)*8);
    text = buildTextSection(sub(buf, "%rsp"), text);

    putBssSection(fp, "");
    putDataSection(fp, data);
    putTextSection(fp, text);
    closeFile(fp);

    printf("Finished Parsing\n");

    return 0;
}
