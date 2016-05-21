/* recognize tokens for the calculator */
%option noyywrap nodefault yylineno

%{
#include "elemcompiler.h"
#include "elemcompiler.tab.h"

static int64_t hexToDec(char *str);
static int64_t strToDec(char *str);
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

"if"                    { return IF; }
"loop"                  { return LOOP; }
"print"                 { return PRINT; }

\"[ -~]+\"              { 
                            yylval.str = strdup(yytext); 
                            //printf("%s\n", yylval.str);
                            // push_label("newone");
                            // .newone:
                            // .string yylval.str
                            return STRING; 
                        }

0(x|X)[a-fA-F0-9]+      { yylval.num = hexToDec(yytext); return NUMBER; }
[0-9]+                  { yylval.num = strToDec(yytext); return NUMBER; }

[a-zA-Z][a-zA-Z0-9]*    { yylval.sym = lookup(yytext); return VAR; }    


"//".*
[ \t]                   /* ignore whitespace */

\\\n                    /* ignore line continuation */

^\n                     /* ignore empty line */
\n                      { return EOL; }

.                       { yyerror("Mystery character %c\n", *yytext); }

%%

static int64_t c_power(uint8_t base, uint8_t index)
{
    int64_t result = 1;
    uint8_t count;

    for (count = index; count; --count)
        result *= base;

    return result;
}

static int64_t hexToDec(char *str)
{
    uint8_t len;
    uint8_t count = 0;
    int64_t result = 0;
    char *startstr = (str + 2);

    for (len = (strlen(startstr)); len; --len) {
        char ch = (*(startstr + (len - 1)));

        if (ch > 96)
            result += (ch-87) * c_power(16, count);
        else if (ch > 64)
            result += (ch-55) * c_power(16, count);
        else
            result += (ch-48) * c_power(16, count);

        ++count;
    }

    return result;
}


static int64_t strToDec(char *str)
{
    uint8_t len;
    uint8_t count = 0;
    int64_t result = 0;

    for (len = (strlen(str)); len; --len) {
        char ch = (*(str + (len - 1)));

        result += (ch-48) * c_power(10, count);

        ++count;
    }

    return result;
}
