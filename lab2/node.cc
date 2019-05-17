// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 4/14/19.
// =======================================================================
#include "node.h"
#include "generated/parser.h"
#include <sstream>
#include <utility>
#include <iostream>
#include <set>
using namespace std;

std::string get_token_name(int id) {
  static std::string tokennames[] = {
      "L",
      "id",
      "int10",
      "if",
      "then",
      "else",
      "while",
      "do",
      "==",
      "!=",
      "<",
      "<=",
      ">",
      ">=",
      "=",
      "(",
      ")",
      "{",
      "}",
      "'",
      ".",
      "+",
      "-",
      "*",
      "/",
      ";"
  };
  static std::string nontermnames[] = {
      "P",
      "D",
      "S",
      "E",
      "C",
      "T",
      "F"
  };
  if (id <= TSEMI && id >= TTYPE)
    return tokennames[id - TTYPE];
  if (id >= P)
    return nontermnames[id - P];
  return "unknown";
}

std::string Node::name() const {
  return children.empty() ? text : get_token_name(token);
}

void Node::dump_edges(const Node *parent, std::vector<std::pair<const Node *, const Node *>> &res) const {
  if (parent)
    res.emplace_back(parent, this);
  for (auto &i:children)
    i->dump_edges(this, res);
}

std::string Node::ToDot() const {
  std::vector<std::pair<const Node *, const Node *>> res;
  dump_edges(nullptr, res);
  stringstream ss;
  set<const Node *> seen;
  auto node_def = [&](const Node *node) {
    if (seen.find(node) != seen.end())
      return;
    ss << "\t"
       << (long) node
       << " [label=\"" << node->name() << "\"];"
       << endl;
    seen.insert(node);
  };
  ss << "digraph G{" << endl;
  for (auto &p:res) {
    const Node *parent = get<0>(p);
    const Node *child = get<1>(p);
    ss << "\t"
       << (long) parent
       << "->"
       << (long) child
       << ";"
       << endl;
    node_def(parent);
    node_def(child);
  }
  ss << "}";
  return ss.str();
}
