/*
 * Declaration for a calculator.
 */

#include <stdint.h>

#define NHASH 9997

/* symbol table */
struct symbol {             /* a variable name */
    char *name;
    int64_t value;
    uint8_t offset;
};

/* node types
 * + - * / %
 * M unary minus
 * E expression list
 * C IF statement
 * L LOOP statement่
 * ์V symbol ref
 * = assignment
 * K constant
 * S literal string
 * A Expression
 */

/* node in the abstraction syntax tree */
/* all have common initial nodetype */
struct ast {
    int nodetype;
    struct ast *l;
    struct ast *r;
};

struct cond {
    int nodetype;       /* type C */
    struct ast *cond;   /* condition */
    struct ast *tl;     /* then branch or do list */
};

struct loop {
    int nodetype;       /* type L */
    struct ast *from;   /* start number */
    struct ast *to;     /* end number */
    struct ast *inc;    /* incremental number */
    struct ast *tl;     /* then branch or do list */
};

struct litstr {
    char *str;
    uint8_t label;
};

struct print {
    int nodetype;           /* type S or A */
    union arg {             /* argument of the print function */
        struct litstr *ls;  /* string argument */
        struct ast *exp;    /* expression argument */
    } arg;
};

struct numval {
    int nodetype;       /* type K */
    int64_t number;
};

struct symref {
    int nodetype;       /* type V */
    struct symbol *s;
};

struct symasgn {
    int nodetype;       /* type = */
    struct symbol *s;
    struct ast *v;      /* value */
};

/* simple symtab of fixed size */
struct symbol symtab[NHASH];

struct symbol *lookup(char*);

/* build an AST */
struct ast *newast (int nodetype, struct ast *l, struct ast *r);
struct ast *newprint (int nodetype, struct ast *exp, char *str);
struct ast *newref (struct symbol *s);
struct ast *newasgn (struct symbol *s, struct ast *v);
struct ast *newnum (int64_t d);
struct ast *newcond (struct ast *cond, struct ast *tl);
struct ast *newloop (struct ast *from, struct ast *to, struct ast *inc, struct ast *tl);

/* evaluate an AST */
int64_t eval (struct ast *);
void gen_asm (struct ast *);

/* delete and free an AST */
void treefree (struct ast *);

/* interface to the lexer */
extern int yylineno;    /* from lexer */
void yyerror (char *s, ...);

