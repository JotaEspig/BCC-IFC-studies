#pragma once

#include "context.hpp"
#ifndef yyFlexLexerOnce
#include <FlexLexer.h>
#endif

#include "tokens.hpp"

class Scanner : public yyFlexLexer {
public:
    TokenVal yylval;
    Context &context;

    Scanner(Context &context) :
      context(context) {
    }

    int yylex() override;
};
