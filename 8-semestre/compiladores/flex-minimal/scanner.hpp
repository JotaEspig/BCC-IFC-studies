#pragma once

#ifndef yyFlexLexerOnce
#include <FlexLexer.h>
#endif

#include "tokens.hpp"

class Scanner : public yyFlexLexer {
public:
  TokenVal yylval;

  int yylex() override;
};
