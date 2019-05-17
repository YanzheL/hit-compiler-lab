// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 5/15/19.
// =======================================================================
#ifndef LAB1_MATCHER_H
#define LAB1_MATCHER_H
#include <cstring>
#include <array>
#include "sym_table.h"
class TokenMatcher {

 public:

  virtual TokenType Scan(const char *buf, int end, int &match_end) = 0;

 protected:
  inline static bool InArray(char c, const char *arr) {
    for (int i = 0; i < strlen(arr); ++i)
      if (arr[i] == c)
        return true;
    return false;
  }

};

class IntegerMatcher : public TokenMatcher {

 public:

  TokenType Scan(const char *buf, int end, int &match_end) override {
    if (end == 0) return TK_UNKNOWN;
    int i = 0;
    int state = 0;
    TokenType result = TK_CONST;
    while (i < end) {
      switch (state) {
        case 0:
          if (IsDigit(buf[i])) {
            state = 1;
            ++i;
            match_end = i;
          } else
            state = 2;
          break;
        case 1:
          if (IsDigit(buf[i])) {
            state = 1;
            ++i;
            match_end = i;
          } else
            state = 2;
          break;
        case 2:
          if (match_end == 0) {
            result = TK_UNKNOWN;
          }
          goto finish;
      }
    }
    finish:
    return result;
  }

 private:
  inline static bool IsDigit(char c) { return c >= '0' && c <= '9'; }

};

class OpMatcher : public TokenMatcher {

 public:

  TokenType Scan(const char *buf, int end, int &match_end) override {
    if (end == 0) return TK_UNKNOWN;
    int i = 0;
    int state = 0;
    TokenType result = TK_OP;
    while (i < end) {
      switch (state) {
        case 0:
          if (InArray(buf[i], type1_)) {
            state = 1;
            ++i;
            match_end = i;
          } else if (InArray(buf[i], type2_)) {
            state = 2;
            ++i;
            match_end = i;
          } else
            state = 3;
          break;
        case 1:state = 3;
          break;
        case 2:
          if (buf[i] == '=') {
            state = 1;
            ++i;
            match_end = i;
          } else
            state = 3;
          break;
        case 3:
          if (match_end == 0) {
            result = TK_UNKNOWN;
          }
          goto finish;
      }
    }
    finish:
    return result;
  }

 private:

  const char *type1_ = "+-*/";

  const char *type2_ = "<>=";

};

class SplitterMatcher : public TokenMatcher {

 public:

  TokenType Scan(const char *buf, int end, int &match_end) override {
    if (end == 0) return TK_UNKNOWN;
    TokenType result = TK_SPLITTER;
    if (!InArray(buf[0], splitters_))
      result = TK_UNKNOWN;
    else
      match_end = 1;
    return result;
  }

 private:

  const char *splitters_ = "();'";

};

class IdentMatcher : public TokenMatcher {

 public:

  TokenType Scan(const char *buf, int end, int &match_end) override {
    if (end == 0) return TK_UNKNOWN;
    int i = 0;
    int state = 0;
    TokenType result = TK_ID;
    while (i < end) {
      switch (state) {
        case 0:
          if (InArray(buf[i], type1_)) {
            state = 1;
            ++i;
            match_end = i;
          } else
            state = 2;
          break;
        case 1:
          if (InArray(buf[i], type2_)) {
            state = 1;
            ++i;
            match_end = i;
          } else
            state = 2;
          break;
        case 2:
          if (match_end == 0) {
            result = TK_UNKNOWN;
          }
          goto finish;
      }
    }
    finish:
    return result;
  }

 private:

  const char *type1_ = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

  const char *type2_ = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

};

class KeyWordMatcher : public TokenMatcher {

 public:

  KeyWordMatcher() : keywords_{"if", "then", "else", "while", "do"}, successType_{TK_KEYWORD} {}
  KeyWordMatcher(std::vector<std::string> keywords, TokenType successType) : keywords_{std::move(keywords)},
                                                                             successType_{successType} {}
  TokenType Scan(const char *buf, int end, int &match_end) override {
    if (end == 0) return TK_UNKNOWN;
    std::string str(buf, buf + end);
    for (const auto &kw:keywords_) {
      if (str == kw) {
        match_end = kw.length();
        return successType_;
      }
    }
    return TK_UNKNOWN;
  }

 private:

  const std::vector<std::string> keywords_;

  TokenType successType_;

};

class VTypeMatcher : public KeyWordMatcher {

 public:

  VTypeMatcher() : KeyWordMatcher({"int", "long", "double", "float"}, TK_VTYPE) {}

};
#endif //LAB1_MATCHER_H
