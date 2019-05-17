cmake_minimum_required(VERSION 3.5)
project(lab2)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR})
file(MAKE_DIRECTORY generated)

set(FlexInput ${CMAKE_SOURCE_DIR}/lexer.l)
set(FlexOutput ${CMAKE_SOURCE_DIR}/generated/lexer.cc)
set(BisonInput ${CMAKE_SOURCE_DIR}/parser.y)
set(BisonOutput ${CMAKE_SOURCE_DIR}/generated/parser.cc)
set(BisonHeader ${CMAKE_SOURCE_DIR}/generated/parser.h)

find_package(BISON REQUIRED)
BISON_TARGET(MyParser ${BisonInput} ${BisonOutput} DEFINES_FILE ${BisonHeader})

find_package(FLEX REQUIRED)
FLEX_TARGET(MyScanner ${FlexInput} ${FlexOutput})

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

set(CMAKE_CXX_FLAGS -fstandalone-debug)

add_executable(
        lab2 main.cc
        node.cc
        sym_entry.cc
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS}
        ${FlexOutput}
)

#target_link_libraries(lab2 ${FLEX_LIBRARIES})