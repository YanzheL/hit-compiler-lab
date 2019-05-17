cmake_minimum_required(VERSION 3.5)
project(lab1)

set(CMAKE_CXX_STANDARD 11)

add_executable(lab1 main.cc sym_table.h lexer.h matcher.h lexer.cc)