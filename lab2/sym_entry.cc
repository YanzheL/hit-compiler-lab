// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 4/14/19.
// =======================================================================
#include "sym_entry.h"
#include <sstream>

using namespace std;

const std::string SymEntry::toString() const {
  stringstream ss;
  ss << "("
     << name
     << ","
     << type
     << ")";
  const string s = ss.str();
  return ss.str();
}

int lookup_symbol(SymTable &table, std::string &name) {
  int idx = -1;
  for (int i = 0; i < table.size(); ++i) {
    if (table[i].name == name)
      idx = i;
  }
  return idx;
}

int push_symbol(SymTable &table, SymEntry &&entry) {
  if (lookup_symbol(table, entry.name) != -1)
    return -1;
  table.push_back(entry);
  return table.size() - 1;
}