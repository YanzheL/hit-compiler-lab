// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 4/14/19.
// =======================================================================
#include <iostream>
#include <fstream>
#include "node.h"
#include "sym_table.h"
#include "codegen.h"

using namespace std;

extern int yyparse();
extern SymTable *table;
extern Generator context;
extern NProgram *program;
extern std::vector<CodeLine> codelines;

int main(int argc, char *argv[]) {
  string src_file(argv[1]);
  freopen(src_file.c_str(), "r", stdin);
  yyparse();
//  std::cout << program->execStmts.size() << std::endl;
//  for (const auto &entry: table) {
//    cout << entry.toString() << endl;
//  }
//  ofstream of(src_file + ".dot");

//  for (auto &i :program->declStmts) {
//    cout<<i->type.name<<endl;
//  }
  cout << context.ToString();
  cout << table->ToString();
  return 0;
}