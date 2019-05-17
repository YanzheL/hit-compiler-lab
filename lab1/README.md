# 实验一 词法分析器设计

#### 系统环境要求

Ubuntu 16.04 及以上

#### 辅助工具

安装CMake

```shell
sudo apt install cmake
```

#### 编译项目

在当前项目目录`lab1/`下创建子目录并进入

```shell
mkdir build
cd build
```

编译

```shell
cmake ..
make
```

此时会在当前目录下产生可执行文件`lab1`

#### 运行

`examples/` 目录下是一些示例的简单类C语言文件，可以用来作为测试用例

例如

```shell
./lab1 ../examples/2.c
```

即可看到运行结果