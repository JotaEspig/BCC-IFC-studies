%{
#include <cstdlib>

#include "scanner.hpp"
%}

%option c++
%option noyywrap
%option yyclass="Scanner"

%%
[0-9]+                        { yylval = atoi(yytext); return NUMBER; }
(int|float)                   { yylval = (VarType)(yytext[0] == 'i' ? INT : FLOAT); return VAR_TYPE; }
[_a-zA-Z][_a-zA-Z0-9]*        { yylval = std::string(yytext); return WORD; }
"{"                           { return LBRACE; }
"}"                           { return RBRACE; }
[ \t]+                        { /* ignora espaços */ }
\n                            { return '\n'; }
.                             { return yytext[0]; }
%%
