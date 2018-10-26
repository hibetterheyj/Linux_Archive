### Cpp on Linux

## 180724

- 开篇

现在被广泛使用的知名的自由软件有： 
Emacs、GCC（GNU Compiler Collection C程序编译器）、G++(C++编译器) 、Bash Shell

g++是GNU的C++编译器(GNU C++ Compiler)，也是GNU Compiler Collection的一部分；GDB是GNU Project的一个调试程序(GNU Debugger)，Makefile是程序编译的规则，makefile记录着整个工程的编译规则(如源文件的编译顺序、依赖关系等)，通过make工具进行编译。

---

- 开发环境搭建与第一个程序

命令行,单文件

```
g++ -std=c++11
```

命令行,带`CMakelist.txt`

可以使用KDevelop