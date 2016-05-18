/* recognize tokens for the calculator */
%option noyywrap nodefault yylineno

%{
#include "elemcompiler.h"
#include "elemcompiler.tab.h"

//extern FILE *yyin;
%}

EXP ([Ee][-+]?[0-9]+)

%%

"->"                    { return TO; }

"+" |
"-" |
"*" |
"/" |
"%" |
"=" |
"|" |
"," |
";" |
"(" |
")" |
"{" |
"}"                     { return yytext[0]; }

">"                     { yylval.cmptype = 1; return CMP; }
"<"                     { yylval.cmptype = 2; return CMP; }
"<>"                    { yylval.cmptype = 3; return CMP; }
"=="                    { yylval.cmptype = 4; return CMP; }
">="                    { yylval.cmptype = 5; return CMP; }
"<="                    { yylval.cmptype = 6; return CMP; }

"if"                    { return IF; }
"loop"                  { return LOOP; }

[a-zA-Z][a-zA-Z0-9]*    { yylval.sym = lookup(yytext); return VAR; }    

[0-9]+                  { yylval.num = atoi(yytext); return NUMBER; }

"//".*
[ \t]                   /* ignore whitespace */

\\\n                    /* ignore line continuation */

^\n                     /* ignore empty line */
\n                      { return EOL; }

.                       { yyerror("Mystery character %c\n", *yytext); }

%%
