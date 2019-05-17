// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 5/16/19.
// =======================================================================
#ifndef LAB2_UTIL_H
#define LAB2_UTIL_H

/**
 * 公共继承序列化ToString接口, 方便统一转换为string输出
 */
class Serializable {

 public:

  virtual std::string ToString() = 0;
};

#endif //LAB2_UTIL_H
