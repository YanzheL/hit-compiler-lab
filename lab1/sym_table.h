// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 5/15/19.
// =======================================================================
#ifndef LAB1_SYM_TABLE_H
#define LAB1_SYM_TABLE_H

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
enum TokenType {
  TK_KEYWORD,
  TK_ID,
  TK_CONST,
  TK_OP,
  TK_SPLITTER,
  TK_VTYPE,
  TK_UNKNOWN
};

static std::string TokenTypeNames[] = {
    [TK_KEYWORD]  =  "关键字",
    [TK_ID]  =  "标识符",
    [TK_CONST]  =  "常整数",
    [TK_OP]  =  "运算符",
    [TK_SPLITTER]  =  "分隔符",
    [TK_VTYPE] = "类型符",
    [TK_UNKNOWN]  =  "未知符",
};

enum ValTypeEnum {
  INT,
  LONG,
  DOUBLE,
  FLOAT,
  STRING,
  UNKNOWN
};

static std::string ValTypeNames[] = {
    [INT]  =  "INT",
    [LONG]  =  "LONG",
    [DOUBLE]  =  "DOUBLE",
    [FLOAT]  =  "FLOAT",
    [STRING]  =  "STRING",
    [UNKNOWN] = "UNKNOWN",
};

struct SymInfo {
  std::string name;
  ValTypeEnum type;
  void *value;
  SymInfo(std::string name, ValTypeEnum type, void *value) : name{name}, type{type}, value{value} {}
  std::string ToString() const {
    std::stringstream ss;
    ss << "(\t"
       << ValTypeNames[type]
       << "\t,\t"
       << std::setw(5)
       << name
       << "\t,\t";
    if (value)
      ss<<*(int*)value;
    else
      ss<<"NULL";
    ss<< "\t)";
    return ss.str();
  }
};

/**
 * 符号表接口
 * 本来是想用多个子类对符号表结构进行多种实现, 比如用搜索树实现
 */
class SymTable {

 public:

  SymTable() = default;

  virtual ~SymTable() = default;

  virtual int insert(std::string name, ValTypeEnum type, void *val) = 0;

  virtual SymInfo *lookup(int id) = 0;

};

/**
 * 暂时只用了最简单的方式
 */
class SimpleSymTable : public SymTable {

 public:

  SimpleSymTable() = default;

  int insert(std::string name, ValTypeEnum type, void *val) override {
    for (const auto &entry:sym_table_)
      if (entry.name == name)
        return -1; // 说明有重复符号
    sym_table_.emplace_back(name, type, val);
    return sym_table_.size() - 1;
  }

  SymInfo *lookup(int id) override {
    if (id >= sym_table_.size())
      return nullptr;
    return &sym_table_[id];
  }

 private:
  std::vector<SymInfo> sym_table_;
};

#endif //LAB1_SYM_TABLE_H
