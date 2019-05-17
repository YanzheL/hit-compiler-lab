// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 5/15/19.
// =======================================================================
#include "lexer.h"

#include "matcher.h"

TokenType Lexer::YYLex() {
  _CleanBuffer();
  TokenType result = TK_UNKNOWN;
  while (bf_end_ <= BUFFER_LEN) {
    // 如果窗口还没有读完整, 或者窗口读完了, 但缓冲区也空了(说明之前的串全部被识别掉了), 则读入下一个字符
    if (!tk_finished_
        || (tk_finished_ && bf_end_ == 0)
        ) {
      tk_finished_ = false;
      char c = in_->get();
      if (_IsDelim(c)) {
        // 发现是个空白符
        if (bf_end_ != 0) {
          // 如果缓冲区非空, 说明这是窗口尾部的空白符, 表示这个窗口读完整了
          tk_finished_ = true;
          break;
        } else // 否则说明还没有读到有效字符, 则跳过
          continue;
      }
      // 此时的c必然是有效字符
      buffer_[bf_end_++] = c;
    } else if (match_end_ != 0) { // 此时说明窗口是完整的, 识别出来的串也结束了, 那么就返回给调用方吧
      break;
    }
    // 对当前缓冲区中的串按照识别器优先级进行扫描
    for (TokenMatcher *scanner:scanners_) {
      int cur_mend = 0; // 用来存储当前识别器对当前缓冲区中的串的最大匹配长度
      TokenType type = scanner->Scan(buffer_, bf_end_, cur_mend);
      if (cur_mend > match_end_) {
        // 如果当前的匹配长度比以前的都长, 说明这次匹配的更合适
        // 则把候选类型设置为当前的结果
        assert(type != TK_UNKNOWN);
        result = type;
        match_end_ = cur_mend;
        // 一旦当前的结果成为新的候选, 则不再调用后续识别器, 否则高优先级结果会被低优先级结果覆盖
        break;
      }
    }
  }
  return result; // 默认返回识别失败
}

