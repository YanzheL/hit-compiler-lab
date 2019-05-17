// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 5/15/19.
// =======================================================================
#ifndef LAB1_LEXER_H
#define LAB1_LEXER_H

#include <iostream>
#include <cstring>
#include <array>
#include <assert.h>
#include "sym_table.h"

class TokenMatcher;

class Lexer {

 public:

  const static int BUFFER_LEN = 100;

  Lexer() : in_{&std::cin}, match_end_{0}, bf_end_{0} {}

  Lexer(std::istream *in) : in_{in}, match_end_{0}, bf_end_{0} {}

  // 把当前缓冲区中的字符穿作为string返回
  inline std::string YYText() const { return {buffer_, buffer_ + match_end_}; }

  // 返回当前缓冲区中的串长度
  inline int YYLeng() const { return match_end_; }

  // 注册识别器到此分析器中
  inline void RegisterScanner(TokenMatcher *scanner) { scanners_.push_back(scanner); }

  // 主入口
  TokenType YYLex();

 private:

  // 输入流
  std::istream *in_;

  // 当前缓冲区的末尾
  int bf_end_;

  // 当前缓冲区中已经被匹配出来的子串的末尾(长度)
  int match_end_;

  /**
   * 我们把从空白符开始, 开始读有效字符, 然后再读到空白符视为一个完整的识别窗口
   * @param tk_finished_ 表示该窗口是否读完
   */
  bool tk_finished_;

  // 识别缓冲区, 存放当前窗口正在被识别的串
  char buffer_[BUFFER_LEN];

  // 空白符
  const char *delims_ = "\n\t \r";

  // 被注册到此词法分析器中的所有识别器, 按照优先级排列
  std::vector<TokenMatcher *> scanners_;

  // 把缓冲区已经识别出来的串清除, 再把后面剩余的串移动到最前面
  inline void _CleanBuffer() {
    int n = bf_end_ - match_end_;
    std::memcpy(buffer_, buffer_ + match_end_, n);
    bf_end_ = n;
    match_end_ = 0;
  }

  // 判断c是否是空白符
  inline bool _IsDelim(char c) const {
    for (int i = 0; i < strlen(delims_); ++i)
      if (delims_[i] == c)
        return true;
    return false;
  }

};

#endif //LAB1_LEXER_H
