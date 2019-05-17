// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 4/14/19.
// =======================================================================
%{
#include "node.h"
#include "sym_table.h"
#include "codegen.h"

#define YYDEBUG 1

extern int yylex();
void yyerror(const char *s) { printf("ERROR: %s\n", s); }

SymTable* table = new SimpleSymTable;
Generator context;
NProgram *program;
%}

%union {
    NProgram *program;
    NExpr *expr;
    NIdentifier *ident;
    NConstInteger *num;
    NBinaryArithOpExpr *arithexpr;
    NBinaryLogicExpr *logicexpr;
    NDeclStmt *declstmt;
    NExecStmt *execstmt;
    NAssignStmt *assignstmt;
    NIfStmt *ifstmt;
    NWhileStmt *whilestmt;

    std::vector<NDeclStmt*> *decls;
    std::vector<NExecStmt*> *stmts;
    std::vector<NExpr*> *exprvec;

    std::string *text;
    int token;
    int instr;
    std::vector<int> *labellist;
}

%token <text> TIDENTIFIER TINTEGER
%token <text> TIF TTHEN TELSE TWHILE TDO
%token <text> TCEQ TCNE TCLT TCLE TCGT TCGE TEQUAL
%token <text> TLPAREN TRPAREN TSQUOTE TDOT
%token <text> TPLUS TMINUS TMUL TDIV TSEMI


%type <text> comparison arith_op1 arith_op2
%type <expr> expr
%type <logicexpr> logicexpr
%type <arithexpr> arithexpr
%type <ident> ident
%type <declstmt> decl
%type <execstmt> stmt
%type <ifstmt> if_stmt if_else_stmt
%type <whilestmt> while_stmt
%type <assignstmt> assign_stmt
%type <stmts> stmts
%type <decls> decls
%type <num> const_int
%type <program> program
%type <instr> M
%type <labellist> N

%start program

%%

program : decls stmts { program = new NProgram(*$1, *$2); $$ = program; }
  ;

decls : decl { $$ = new std::vector<NDeclStmt *>(); $$->push_back($1); }
  | decls decl { $$ = $1; $$->push_back($2); }
  ;

stmts : stmt { $$ = new std::vector<NExecStmt *>(); $$->push_back($1); }
  | stmts stmt { $$ = $1; $$->push_back($2); }
  ;

ident : TIDENTIFIER { $$ = new NIdentifier(*$1); delete $1; }
  ;

const_int : TINTEGER { $$ = new NConstInteger(std::stoi(*$1)); delete $1; }
  ;

comparison : TCGT | TCLT | TCEQ
  ;

arith_op1 : TPLUS | TMINUS
  ;

arith_op2 : TMUL | TDIV
  ;

decl : ident ident TSEMI {
    $$ = new NDeclStmt(*$1, *$2);
    table->insert($2->name, $1->name);
  }
  ;

if_stmt : TIF TLPAREN logicexpr TRPAREN M stmt {
    $$ = new NIfStmt(*$3, *$6);
    context.BackPatch($3->truelist, $5);
    context.Merge($$->nextlist, $3->falselist);
    context.Merge($$->nextlist, $6->nextlist);
  }
  ;

if_else_stmt : if_stmt N TELSE M stmt {
    $$ = $1; $$->s2 = $5;
    context.BackPatch($1->condition.falselist, $4);
    $$->nextlist.clear();
    context.Merge($$->nextlist, *$2);
    context.Merge($$->nextlist, $5->nextlist);
    context.Merge($$->nextlist, $$->s1.nextlist);
  }
  ;

M : { $$ = context.nextinstr; }
  ;

N : { $$ = new std::vector<int>{context.nextinstr}; context.Gen(new CodeLine({"goto","_"}, 1)); }
  ;

while_stmt : TWHILE M TLPAREN logicexpr TRPAREN M stmt {
    $$ = new NWhileStmt(*$4, *$7);
    context.BackPatch($7->nextlist, $2);
    context.BackPatch($4->truelist, $6);
    $$->nextlist = $4->falselist;
    context.Gen(new CodeLine({"goto",std::to_string($2)}));
  }
  ;

assign_stmt : ident TEQUAL expr TSEMI {
    $$ = new NAssignStmt(*$1, *$3);
    context.Gen(new CodeLine({"t", "=", $3->ToString()}));
    context.Gen(new CodeLine({$1->ToString(), "=", "t"}));
  }
  ;

stmt : assign_stmt
  | if_stmt
  | if_else_stmt
  | while_stmt
  ;

logicexpr : expr comparison expr {
    $$ = new NBinaryLogicExpr(*$1, *$2, *$3);
    $$->truelist.push_back(context.nextinstr);
    context.Gen(new CodeLine({"if", $1->ToString(), *$2, $3->ToString(), "goto", "_"}, 5));
    $$->falselist.push_back(context.nextinstr);
    context.Gen(new CodeLine({"goto", "_"}, 1));
  }
  ;

arithexpr : expr arith_op2 expr { $$ = new NBinaryArithOpExpr(*$1, *$2, *$3); }
  | expr arith_op1 expr { $$ = new NBinaryArithOpExpr(*$1, *$2, *$3); }
  ;

expr :  ident { $<ident>$ = $1; }
  | const_int
  | arithexpr
  | logicexpr
  | TLPAREN expr TRPAREN { $$ = $2; }
  ;

%%