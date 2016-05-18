/*
 * helper functions for calculator
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "elemcompiler.h"

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

    if (!a) {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = nodetype;

    if (nodetype == 'A')
        a->arg.exp = exp;
    else
        a->arg.str = str;

    return (struct ast*) a;
}

struct ast* newcmp (int cmptype, struct ast *l, struct ast *r)
{
    struct ast *a = (struct ast*) malloc(sizeof(struct ast));

    if (!a) {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = '0' + cmptype;
    a->l = l;
    a->r = r;

    return a;
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
            free(((struct print*)a)->arg.str);
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

int64_t eval (struct ast *a)
{
    int64_t v = 0;
    //int64_t count;

    if (!a) {
        yyerror("internal error, null eval");

        return 0;
    }

    switch (a->nodetype) {
        /* constant */
        case 'K':
            v = ((struct numval*)a)->number;
            break;
            
        /*num reference */
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
            printf("%s\n", (((struct print*)a)->arg.str));
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

            /* comparisons */
        case '1':
            v = (eval(a->l) > eval(a->r)) ? 1 : 0;
            break;
        case '2':
            v = (eval(a->l) < eval(a->r)) ? 1 : 0;
            break;
        case '3':
            v = (eval(a->l) != eval(a->r)) ? 1 : 0;
            break;
        case '4':
            v = (eval(a->l) == eval(a->r)) ? 1 : 0;
            break;
        case '5':
            v = (eval(a->l) >= eval(a->r)) ? 1 : 0;
            break;
        case '6':
            v = (eval(a->l) <= eval(a->r)) ? 1 : 0;
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


    return yyparse();
}
