%option noyywrap
%{
#include <iostream>
#include <string>
#include "node.h"
#include "parser.h"
#define ADD_LEAF(t) {                                                          \
                      auto leaf = new Node(t);                                 \
                      leaf->text = yylval->text;                               \
                      yylval->children.push_back(leaf);                        \
                    }
#define TOKEN(t) {                                                             \
                   yylval = new Node(t);                                       \
                   yylval->text = std::string(yytext, yyleng);                 \
                 }
%}

%%

[ \t\n]                 ;
int|float               TOKEN(TTYPE) ADD_LEAF(TTYPE) return TTYPE;
if                      TOKEN(TIF) return TIF;
then                    TOKEN(TTHEN) return TTHEN;
else                    TOKEN(TELSE) return TELSE;
while                   TOKEN(TWHILE) return TWHILE;
do                      TOKEN(TDO) return TDO;
[a-zA-Z_][a-zA-Z0-9_]*  TOKEN(TIDENTIFIER) ADD_LEAF(TIDENTIFIER) return TIDENTIFIER;
[0-9]+                  TOKEN(TINTEGER) ADD_LEAF(TINTEGER) return TINTEGER;
"="                     TOKEN(TEQUAL) return TEQUAL;
"=="                    TOKEN(TCEQ) return TCEQ;
"!="                    TOKEN(TCNE) return TCNE;
"<"                     TOKEN(TCLT) return TCLT;
"<="                    TOKEN(TCLE) return TCLE;
">"                     TOKEN(TCGT) return TCGT;
">="                    TOKEN(TCGE) return TCGE;
"("                     TOKEN(TLPAREN) return TLPAREN;
")"                     TOKEN(TRPAREN) return TRPAREN;
"."                     TOKEN(TDOT) return TDOT;
"'"                     TOKEN(TSQUOTE) return TSQUOTE;
"+"                     TOKEN(TPLUS) return TPLUS;
"-"                     TOKEN(TMINUS) return TMINUS;
"*"                     TOKEN(TMUL) return TMUL;
"/"                     TOKEN(TDIV) return TDIV;
";"                     TOKEN(TSEMI) return TSEMI;
.                       std::cout<< "Unknown token!" << std::endl; yyterminate();

%%