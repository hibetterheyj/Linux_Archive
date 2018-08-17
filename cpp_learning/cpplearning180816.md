# Cpp学习180816

## Vector

https://www.codesdope.com/cpp-stdvector/

https://www.codeguru.com/cpp/cpp/cpp_mfc/stl/article.php/c4027/C-Tutorial-A-Beginners-Guide-to-stdvector-Part-1.htm

**Vectors** are sequence containers which represent arrays which can change in size. Thus, we need not specify its length at the time of declaration and can change it later in the program.

向量是代表可以改变大小的数组的序列容器。 因此，我们不需要在声明时指定它的长度，可以在程序的后面更改它。

## namespace

https://www.cnblogs.com/ChYQ/p/6263932.html 

```cpp
#include <iostream>
using namespace std;
    
// first name space
namespace first_space{
    void func(){
    cout << "Inside first_space" << endl;
    }
}
    
// second name space
namespace second_space{
//此处func与第一处命名空间内函数名相同
    void func(){
        cout << "Inside second_space" << endl;
    }
}
    
// 使用第一个namespace
using namespace first_space;
int main () {
     
// This calls function from first name space.
    func();
       
    return 0;
}
```

输出`Inside first_space`

## #ifdef #else # endif相关

https://www.cnblogs.com/wanqieddy/p/4377937.html

一般情况下，源程序中所有的行都参加[编译](http://baike.baidu.com/view/69568.htm)。但是有时希望当满足某条件时对一组语句进行[编译](http://baike.baidu.com/view/69568.htm)，而当条件不满足时则编译另一组语句，这就是“条件编译”。为了满足条件编译可以使用#ifdef、#ifndef、#endif等宏指令。

## 奇妙小函数

- isnan()

判断类型是否为NaN

- atan(angle)

反正切





