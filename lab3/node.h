// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 5/16/19.
// =======================================================================
#ifndef LAB2_NODE_H
#define LAB2_NODE_H

#include <string>
#include <vector>
#include <sstream>
#include "util.h"

/**
 * 表达式类型
 */
class NExpr : public Serializable {

 public:

  std::string ToString() override { return {}; };
};

/**
 * 标识符类型
 */
class NIdentifier : public NExpr {

 public:

  explicit NIdentifier(std::string &name) : name(std::move(name)) {}

 public:

  std::string name;

  std::string ToString() override { return name; }
};

/**
 * 常整数类型
 */
class NConstInteger : public NExpr {

 public:

  long long value;

  explicit NConstInteger(long long value) : value(value) {}

  std::string ToString() override { return std::to_string(value); }
};

/**
 * 二元算术运算语句类型
 */
class NBinaryArithOpExpr : public NExpr {

 public:

  std::string op;

  NExpr &lhs;

  NExpr &rhs;

  NBinaryArithOpExpr(NExpr &lhs, std::string op, NExpr &rhs) : lhs(lhs), rhs(rhs), op(op) {}

  std::string ToString() override {
    std::stringstream ss;
    ss << lhs.ToString()
       << " "
       << op
       << " "
       << rhs.ToString();
    return ss.str();
  }
};

/**
 * 可执行语句类型
 */
class NExecStmt : public Serializable {

 public:

  std::vector<int> nextlist;

  std::string ToString() override { return {}; };
};

/**
 * 二元逻辑表达式
 */
class NBinaryLogicExpr : public NExpr {

 public:

  std::vector<int> truelist;

  std::vector<int> falselist;

  std::string op;

  NExpr &lhs;

  NExpr &rhs;

  NBinaryLogicExpr(NExpr &lhs, std::string op, NExpr &rhs) : lhs(lhs), rhs(rhs), op(op) {}

  std::string ToString() override {
    std::stringstream ss;
    ss << lhs.ToString()
       << " "
       << op
       << " "
       << rhs.ToString();
    return ss.str();
  }
};

/**
 * 赋值语句类型
 */
class NAssignStmt : public NExecStmt {

 public:

  NIdentifier &lhs;

  NExpr &rhs;

  NAssignStmt(NIdentifier &lhs, NExpr &rhs) : lhs(lhs), rhs(rhs) {}
};

/**
 * 声明语句类型
 */
class NDeclStmt : public Serializable {

 public:

  NDeclStmt(const NIdentifier &type, NIdentifier &id) : type(type), id(id) {}

  std::string ToString() override { return {}; };

 public:

  const NIdentifier &type;

  NIdentifier &id;
};

/**
 * IF语句类型
 */
class NIfStmt : public NExecStmt {

 public:

  explicit NIfStmt(NBinaryLogicExpr &condition, NExecStmt &s1) : condition(condition), s1(s1), s2(nullptr) {}

 public:

  NExecStmt &s1;

  NExecStmt *s2;

  NBinaryLogicExpr &condition;
};

/**
 * WHILE语句类型
 */
class NWhileStmt : public NExecStmt {

 public:

  explicit NWhileStmt(NBinaryLogicExpr &condition, NExecStmt &s) : condition(condition), s(s) {}

 public:

  NBinaryLogicExpr &condition;

  NExecStmt &s;
};

/**
 * 代表整个程序
 */
class NProgram {

 public:

  NProgram(std::vector<NDeclStmt *> &declStmts, std::vector<NExecStmt *> &execStmts)
      : declStmts(declStmts), execStmts(execStmts) {}

 public:

  std::vector<NDeclStmt *> &declStmts;

  std::vector<NExecStmt *> &execStmts;
};

#endif //LAB2_NODE_H
