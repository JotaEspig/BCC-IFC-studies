%{
#include <stdio.h>
%}

%%
[0-9]+          { printf("NUMBER: %s\n", yytext); }
[a-zA-Z]+       { printf("WORD: %s\n", yytext); }
[ \t]+          { /* ignora espaços */ }
\n              { /* ignora quebras de linha */ }
.               { printf("UNKNOWN: %s\n", yytext); }
%%

int yywrap(void) {
    return 1;
}

int main(void) {
    yylex();
    return 0;
}
