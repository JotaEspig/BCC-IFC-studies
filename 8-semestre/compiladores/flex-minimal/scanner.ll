%{
#include <cstdlib>

#include "scanner.hpp"
%}

%option c++
%option noyywrap
%option yyclass="Scanner"

%%
[0-9]+      { yylval = atoi(yytext); return NUMBER; }
"int"       { yylval = 0; return VAR_TYPE; }
[a-zA-Z]+   { yylval = std::string(yytext); return WORD; }
[ \t]+      { /* ignora espaços */ }
\n          { return '\n'; }
.           { return yytext[0]; }
%%
