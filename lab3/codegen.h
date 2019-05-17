// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 5/16/19.
// =======================================================================
#ifndef LAB2_CODEGEN_H
#define LAB2_CODEGEN_H

#include <string>
#include <vector>
#include <assert.h>
#include <sstream>
#include "util.h"

class CodeLine {

 public:

  explicit CodeLine(std::vector<std::string> vars) : vars(std::move(vars)), unknown_idx(-1) {}

  CodeLine(std::vector<std::string> vars, int unknownIdx) : vars(std::move(vars)), unknown_idx(unknownIdx) {}

  std::string ToString() {
    std::stringstream ss;
    for (const auto &var:vars)
      ss << var << " ";
    return ss.str();
  }

 public:

  std::vector<std::string> vars;

  int unknown_idx;
};

class Generator : public Serializable {

 public:

  const int START_ADDR = 100;

  int nextinstr = START_ADDR;

  std::vector<CodeLine *> codes;

  Generator() = default;

  int Gen(CodeLine *expr) {
    codes.push_back(expr);
    return ++nextinstr;
  }

  void BackPatch(std::vector<int> &list, int label) {
    for (int line:list) {
      assert(line < nextinstr);
      CodeLine *expr = codes[line - START_ADDR];
      assert(expr->unknown_idx != -1);
      expr->vars[expr->unknown_idx] = std::to_string(label);
    }
  }

  static void Merge(std::vector<int> &dst, const std::vector<int> &src) {
    dst.insert(dst.end(), src.begin(), src.end());
  }

  std::string ToString() override {
    std::stringstream ss;
    for (int i = 0; i < codes.size(); ++i) {
      ss << i + START_ADDR
         << ":\t"
         << codes[i]->ToString()
         << std::endl;
    }
    return ss.str();
  }
};

#endif //LAB2_CODEGEN_H
