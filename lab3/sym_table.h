// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 4/14/19.
// =======================================================================
#ifndef LAB2_SYM_TABLE_H
#define LAB2_SYM_TABLE_H

#include <string>
#include <vector>
#include <iomanip>
#include "util.h"

class SymInfo : public Serializable {

 public:

  std::string name;

  std::string type;

  int width;

  SymInfo(std::string name, std::string type) : name{name}, type{type} {
    if (type == "int" || type == "float" || type == "long")
      width = 4;
    else if (type == "double")
      width = 8;
  }

  std::string ToString() override {
    std::stringstream ss;
    ss << "(\t"
       << std::setw(5)
       << type
       << "\t"
       << std::setw(5)
       << name
       << "\t"
       << std::setw(5)
       << width
       << "\t)";
    return ss.str();
  }
};

class SymTable : public Serializable {

 public:

  SymTable() = default;

  virtual ~SymTable() = default;

  virtual int insert(std::string name, std::string type) = 0;

  virtual SymInfo *lookup(int id) = 0;
};

class SimpleSymTable : public SymTable {

 public:

  SimpleSymTable() = default;

  int insert(std::string name, std::string type) override {
    for (const auto &entry:sym_table_)
      if (entry.name == name)
        return -1; // 说明有重复符号
    sym_table_.emplace_back(name, type);
    return sym_table_.size() - 1;
  }

  SymInfo *lookup(int id) override {
    if (id >= sym_table_.size())
      return nullptr;
    return &sym_table_[id];
  }

  std::string ToString() override {
    std::stringstream ss;
    ss << "---------- 符号表 ----------" << std::endl;
    ss << "<\tTYPE\tNAME\tWIDTH\t>" << std::endl;
    for (auto &info: sym_table_)
      ss << info.ToString() << std::endl;
    return ss.str();
  }

 private:
  std::vector<SymInfo> sym_table_;
};

#endif //LAB2_SYM_TABLE_H
