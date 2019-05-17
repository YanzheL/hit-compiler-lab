// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 4/14/19.
// =======================================================================
%{
#include "node.h"
#include "sym_entry.h"

extern int yylex();
void yyerror(const char *s) { printf("ERROR: %s\n", s); }
#define YYDEBUG 1

SymTable table;
Node* root;
%}

%define api.value.type {Node*}

%token TTYPE TIDENTIFIER TINTEGER
%token TIF TTHEN TELSE TWHILE TDO
%token TCEQ TCNE TCLT TCLE TCGT TCGE TEQUAL
%token TLPAREN TRPAREN TSQUOTE TDOT
%token TPLUS TMINUS TMUL TDIV TSEMI

%start p

%%

p : d s { root = new Node(P); $$ = root; $$->children.push_back($1); $$->children.push_back($2); }
  ;

d : { $$ = nullptr; }
  | TTYPE TIDENTIFIER TSEMI d {
		                $$ = new Node(D);
		                $2->idx = push_symbol(table,{$2->text, $1->text});
		                $$->children.push_back($1); $$->children.push_back($2); $$->children.push_back($3);
				if ($4) $$->children.push_back($4);
		              }
  ;


s : TIDENTIFIER TEQUAL e TSEMI {
		                 $$ = new Node(S);
		                 $$->children.push_back($1); $$->children.push_back($2);
		                 $$->children.push_back($3); $$->children.push_back($4);
		               }
  | TIF TLPAREN c TRPAREN s {
			      $$ = new Node(S);
			      $$->children.push_back($1); $$->children.push_back($2);
			      $$->children.push_back($3); $$->children.push_back($4); $$->children.push_back($5);
		            }
  | TIF TLPAREN c TRPAREN s TELSE s {
			              $$ = new Node(S); $$->children.push_back($1);
			              $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($4);
			              $$->children.push_back($5); $$->children.push_back($6); $$->children.push_back($7);
			            }
  | TWHILE TLPAREN c TRPAREN s {
  		                 $$ = new Node(S);
  		                 $$->children.push_back($1); $$->children.push_back($2);
  		                 $$->children.push_back($3); $$->children.push_back($4); $$->children.push_back($5);
  		               }
  | s s { $$ = $1; $$->children.push_back($2); }
  ;

c : e TCGT e { $$ = new Node(C); $$->children.push_back($1); $$->children.push_back($2); $$->children.push_back($3); }
  | e TCLT e { $$ = new Node(C); $$->children.push_back($1); $$->children.push_back($2); $$->children.push_back($3); }
  | e TCEQ e { $$ = new Node(C); $$->children.push_back($1); $$->children.push_back($2); $$->children.push_back($3); }
  ;

e : e TPLUS t { $$ = new Node(E); $$->children.push_back($1); $$->children.push_back($2); $$->children.push_back($3); }
  | e TMINUS t { $$ = new Node(E); $$->children.push_back($1); $$->children.push_back($2); $$->children.push_back($3); }
  | t { $$ = new Node(E); $$->children.push_back($1); }
  ;

t : f { $$ = new Node(T); $$->children.push_back($1); }
  | t TMUL f { $$ = new Node(T); $$->children.push_back($1); $$->children.push_back($2); $$->children.push_back($3); }
  | t TDIV f { $$ = new Node(T); $$->children.push_back($1); $$->children.push_back($2); $$->children.push_back($3); }
  ;

f : TLPAREN e TRPAREN {
                        $$ = new Node(F);
                        $$->children.push_back($1); $$->children.push_back($2); $$->children.push_back($3);
                      }
  | TIDENTIFIER { $$ = new Node(F); $$->children.push_back($1); }
  | TINTEGER { $$ = new Node(F); $$->children.push_back($1); }
  ;

%%