// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 4/14/19.
// =======================================================================
#ifndef LAB2_NODE_H
#define LAB2_NODE_H

#include <string>
#include <vector>

enum nontermtype {
  P = 1000,
  D,
  S,
  E,
  C,
  T,
  F
};

std::string get_token_name(int id);

class Node {

 public:

  int idx = -1;

  std::string text;

  int token;

  std::vector<Node *> children;

 public:

  explicit Node(int token) : token(token) {}

  // 辅助函数, 把当前的AST树序列化成dot类型的文件字符串, 后续用图形化工具显示这棵树
  std::string ToDot() const;

  // 辅助函数, 取得当前AST的所有边
  void dump_edges(const Node *parent, std::vector<std::pair<const Node *, const Node *>> &res) const;

  std::string name() const;

};

#endif //LAB2_NODE_H
