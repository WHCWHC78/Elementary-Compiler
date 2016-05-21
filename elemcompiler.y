/* calculator with AST */

%{
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "elemcompiler.h"
%}

%union {
    struct ast *node;
    struct symbol *sym;         /* which symbol */
    int64_t num;
    char *str;                  /* literal string */
}

/* declare tokens */
%token <str> STRING
%token <num> NUMBER
%token <sym> VAR
%token EOL
%token IF LOOP TO PRINT

%right '='
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMINUS

%type <node> term factor exp explist stmt

%start root
%%

root: /*nothing */
    | root stmt EOL         {
                                //eval($2);
                                //printf("# new one\n");
                                gen_asm($2);
                                treefree($2);
                            }
    | root error EOL        { yyerrok; }
    ;

stmt: exp ';'
    | IF '(' exp ')' '{' explist '}'                               { $$ = newcond($3, $6); }
    | LOOP '(' NUMBER TO NUMBER ',' NUMBER ')' '{' explist '}'     { $$ = newloop(newnum($3), newnum($5), newnum($7), $10); }
    ;

exp: factor
   | exp '+' factor                 { $$ = newast('+', $1, $3); }
   | exp '-' factor                 { $$ = newast('-', $1, $3); }
   | VAR '=' exp                    { $$ = newasgn($1, $3); }
   | PRINT '(' STRING ')'           { $$ = newprint('S', NULL, $3); }
   | PRINT '(' exp ')'              { $$ = newprint('A', $3, NULL); }
   ;

factor: term
      | factor '*' term             { $$ = newast('*', $1, $3); }
      | factor '/' term             { $$ = newast('/', $1, $3); }
      | factor '%' term             { $$ = newast('%', $1, $3); }
      ;

term: NUMBER                        { $$ = newnum($1); }
    | VAR                           { $$ = newref($1); }
    | '(' exp ')'                   { $$ = $2; }
    | '-' term %prec UMINUS         { $$ = newast('M', $2, NULL); }

explist: /* nothing */              { $$ = NULL; }
       | exp ';' explist            {
                                        if ($3 == NULL)
                                            $$ = $1;
                                        else
                                            $$ = newast('E', $1, $3);
                                    }
       ;

