// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 4/14/19.
// =======================================================================
#ifndef LAB2_SYM_ENTRY_H
#define LAB2_SYM_ENTRY_H

#include <string>
#include <vector>

// 符号表的一条记录
class SymEntry {

 public:

  std::string name;

  std::string type;

 public:

  SymEntry(std::string &name, std::string &type) : name(name), type(type) {}

  const std::string toString() const;

};

// 符号表类型
using SymTable = std::vector<SymEntry>;

int lookup_symbol(SymTable &table, std::string &&name);

int push_symbol(SymTable &table, SymEntry &&entry);

#endif //LAB2_SYM_ENTRY_H
