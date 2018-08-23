# Cpp学习

# 180816

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

# 180820

## share_ptr

https://www.cnblogs.com/diysoul/p/5930361.html

　　shared_ptr 是一个标准的共享所有权的智能指针, 允许多个指针指向同一个对象. 定义在 memory 文件中(非memory.h), 命名空间为 std.

　　shared_ptr 是为了解决 auto_ptr 在对象所有权上的局限性(auto_ptr 是独占的), 在使用引用计数的机制上提供了可以共享所有权的智能指针, 当然这需要额外的开销:
　　(1) shared_ptr 对象除了包括一个所拥有对象的指针外, 还必须包括一个引用计数代理对象的指针.
　　(2) 时间上的开销主要在初始化和拷贝操作上, *和->操作符重载的开销跟auto_ptr是一样.
　　(3) 开销并不是我们不使用shared_ptr的理由, 永远不要进行不成熟的优化, 直到性能分析器告诉你这一点.

　　使用方法:

可以使用模板函数 make_shared 创建对象, make_shared 需指定类型('<>'中)及参数('()'内), 传递的参数必须与指定的类型的构造函数匹配. 如:

```c++
std::shared_ptr<int> sp1 = std::make_shared<int>(10);
std::shared_ptrstd::string sp2 = std::make_sharedstd::string("Hello c++");
//也可以定义 auto 类型的变量来保存 make_shared 的结果.
auto sp3 = std::make_shared<int>(11);
printf("sp3=%d\n", sp3);
auto sp4 = std::make_sharedstd::string("C++11");
printf("sp4=%s\n", (sp4).c_str());
```

### 成员函数

use_count 返回引用计数的个数
unique 返回是否是独占所有权( use_count 为 1)
swap 交换两个 shared_ptr 对象(即交换所拥有的对象)
reset 放弃内部对象的所有权或拥有对象的变更, 会引起原有对象的引用计数的减少
get 返回内部对象(指针), 由于已经重载了()方法, 因此和直接使用对象是一样的.如 shared_ptr<int> sp(new int(1)); sp 与 sp.get()是等价的

以下代码演示各个函数的用法与特点:

```
            std::shared_ptr<int> sp0(new int(2));
            std::shared_ptr<int> sp1(new int(11));
            std::shared_ptr<int> sp2 = sp1;
            printf("%d\n", *sp0);               // 2
            printf("%d\n", *sp1);               // 11
            printf("%d\n", *sp2);               // 11
            sp1.swap(sp0);
            printf("%d\n", *sp0);               // 11
            printf("%d\n", *sp1);               // 2
            printf("%d\n", *sp2);               // 11

            std::shared_ptr<int> sp3(new int(22));
            std::shared_ptr<int> sp4 = sp3;
            printf("%d\n", *sp3);               // 22
            printf("%d\n", *sp4);               // 22
            sp3.reset();                        
            printf("%d\n", sp3.use_count());    // 0
            printf("%d\n", sp4.use_count());    // 1
            printf("%d\n", sp3);                // 0
            printf("%d\n", sp4);                // 指向所拥有对象的地址
            
            std::shared_ptr<int> sp5(new int(22));
            std::shared_ptr<int> sp6 = sp5;
            std::shared_ptr<int> sp7 = sp5;
            printf("%d\n", *sp5);               // 22
            printf("%d\n", *sp6);               // 22
            printf("%d\n", *sp7);               // 22
            printf("%d\n", sp5.use_count());    // 3
            printf("%d\n", sp6.use_count());    // 3
            printf("%d\n", sp7.use_count());    // 3
            sp5.reset(new int(33));                        
            printf("%d\n", sp5.use_count());    // 1
            printf("%d\n", sp6.use_count());    // 2
            printf("%d\n", sp7.use_count());    // 2
            printf("%d\n", *sp5);               // 33
            printf("%d\n", *sp6);               // 22
            printf("%d\n", *sp7);               // 22
```

shared_ptr 的赋值构造函数和拷贝构造函数:







