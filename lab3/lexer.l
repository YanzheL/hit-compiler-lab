%option noyywrap
%{
#include <iostream>
#include <string>
#include "node.h"
#include "parser.h"
#define SAVE_TOKEN(t) { yylval.text = new std::string(yytext, yyleng); }
#define TOKEN(t) { yylval.token = t; }
%}

%%

[ \t\n]                 ;
if                      SAVE_TOKEN(TIF) return TIF;
then                    SAVE_TOKEN(TTHEN) return TTHEN;
else                    SAVE_TOKEN(TELSE) return TELSE;
while                   SAVE_TOKEN(TWHILE) return TWHILE;
do                      SAVE_TOKEN(TDO) return TDO;
[a-zA-Z_][a-zA-Z0-9_]*  SAVE_TOKEN(TIDENTIFIER) return TIDENTIFIER;
[0-9]+                  SAVE_TOKEN(TINTEGER) return TINTEGER;
"="                     SAVE_TOKEN(TEQUAL) return TEQUAL;
"=="                    SAVE_TOKEN(TCEQ) return TCEQ;
"!="                    SAVE_TOKEN(TCNE) return TCNE;
"<"                     SAVE_TOKEN(TCLT) return TCLT;
"<="                    SAVE_TOKEN(TCLE) return TCLE;
">"                     SAVE_TOKEN(TCGT) return TCGT;
">="                    SAVE_TOKEN(TCGE) return TCGE;
"("                     SAVE_TOKEN(TLPAREN) return TLPAREN;
")"                     SAVE_TOKEN(TRPAREN) return TRPAREN;
"."                     SAVE_TOKEN(TDOT) return TDOT;
"'"                     SAVE_TOKEN(TSQUOTE) return TSQUOTE;
"+"                     SAVE_TOKEN(TPLUS) return TPLUS;
"-"                     SAVE_TOKEN(TMINUS) return TMINUS;
"*"                     SAVE_TOKEN(TMUL) return TMUL;
"/"                     SAVE_TOKEN(TDIV) return TDIV;
";"                     SAVE_TOKEN(TSEMI) return TSEMI;
.                       std::cout<< "Unknown token!" << std::endl; yyterminate();

%%