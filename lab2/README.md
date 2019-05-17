# 实验二 LR语法分析器设计

#### 系统环境要求

Ubuntu 16.04 及以上

#### 依赖库安装

安装Flex和Bison

```shell
sudo apt install flex bison
```

安装CMake

```shell
sudo apt install cmake
```

安装GraphViz， 用来以图片形式显示生成的AST树

```shell
sudo apt install graphviz
```

#### 编译项目

在当前项目目录`lab2/`下创建子目录并进入

```shell
mkdir build
cd build
```

编译

```shell
cmake ..
make
```

此时会在当前目录下产生可执行文件`lab2`

#### 运行

`examples/` 目录下是一些示例的简单类C语言文件，可以用来作为测试用例

例如

```shell
./lab2 ../examples/2.c
```

此时会在原文件旁边生成一个同名的.dot文件

于是使用graphviz工具将此DOT图文件显示出来

```shell
dot -Tpng ../examples/2.c.dot > ../examples/2.c.png
```

即可生成AST语法分析树的图片 `../examples/2.c.png` 
