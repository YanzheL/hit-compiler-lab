// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 4/14/19.
// =======================================================================
#include <iostream>
#include <fstream>
#include "node.h"
#include "sym_entry.h"

using namespace std;

extern int yyparse();
extern SymTable table;
extern Node *root;

int main(int argc, char *argv[]) {
  string src_file(argv[1]);
  freopen(src_file.c_str(), "r", stdin);
  yyparse();
  // 显示符号表
  for (const auto &entry: table)
    cout << entry.toString() << endl;
  // 输出dot文件, 方便后续图形化显示
  ofstream of(src_file + ".dot");
  of << root->ToDot();
  return 0;
}