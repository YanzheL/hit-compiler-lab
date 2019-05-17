#include <iostream>
#include <fstream>
#include <memory>
#include <iomanip>
#include "lexer.h"
#include "matcher.h"

using namespace std;
int main(int argc, const char *argv[]) {
  ifstream f(argv[1]);
  if (!f) {
    std::cerr << "Open file error" << endl;
    return -1;
  }
  Lexer lexer(&f);
  // 从上到下按照优先级加入每种TOKEN的识别器
  lexer.RegisterScanner(new SplitterMatcher);
  lexer.RegisterScanner(new OpMatcher);
  lexer.RegisterScanner(new VTypeMatcher);
  lexer.RegisterScanner(new KeyWordMatcher);
  lexer.RegisterScanner(new IntegerMatcher);
  lexer.RegisterScanner(new IdentMatcher);
  // 创建符号表
  unique_ptr<SymTable> table(new SimpleSymTable);
  // 存放各变量在符号表的入口ID
  std::vector<int> entry_ids;
  std::cout << "---------- 词法分析结果 ----------" << endl;
  while (true) {
    TokenType type = lexer.YYLex();
    if (type == TK_UNKNOWN) // 表示识别结束
      break;
    string text = lexer.YYText();
    std::cout << "(\t"
              << TokenTypeNames[type]
              << "\t,\t"
              << std::setw(5)
              << text
              << "\t)"
              << std::endl;
    if (type == TK_ID)
      entry_ids.push_back(table->insert(text, UNKNOWN, nullptr));
  }
  std::cout << "---------- 符号表 ----------" << endl;
  std::cout << "<\tTYPE\t,\tNAME\t,\tVAL\t\t>" << endl;
  for (int id:entry_ids) {
    if (id != -1)
      std::cout << table->lookup(id)->ToString() << endl;
  }
  return 0;
}