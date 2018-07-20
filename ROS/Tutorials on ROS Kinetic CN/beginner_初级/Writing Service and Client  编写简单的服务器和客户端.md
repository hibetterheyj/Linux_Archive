## Writing Service and Client | 编写简单的服务器和客户端

> 前提条件：http://wiki.ros.org/cn/ROS/Tutorials/CreatingMsgAndSrv#Creating_a_srv

### 出现问题

- 找不到srv格式文件！使用`rossrv show AddTwoInts`会有发生结果

```
[beginner_tutorials/AddTwoInts]:
int64 a
int64 b
---
int64 sum
```

- `tutorials/AddTwoInts.h: No such file or directory compilation terminated.`

https://answers.ros.org/question/213544/fatal-error-beginner_tutorialsaddtwointsh-no-such-file-or-directory-include-beginner_tutorialsaddtwointsh/

最后一个回答，在CMakeList.txt增加相关内容

```
 generate_messages(
   DEPENDENCIES
   std_msgs
 )
```

又进行编译时产生：

```
-- BUILD_SHARED_LIBS is on
-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-- ~~  traversing 4 packages in topological order:
-- ~~  - serial
-- ~~  - beginner_tutorials
-- ~~  - hyjtest
-- ~~  - amcl
-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-- +++ processing catkin package: 'serial'
-- ==> add_subdirectory(serial)
-- +++ processing catkin package: 'beginner_tutorials'
-- ==> add_subdirectory(beginner_tutorials)
-- Using these message generators: gencpp;geneus;genlisp;gennodejs;genpy
CMake Warning at /home/philhe/catkin_ws/build/beginner_tutorials/cmake/beginner_tutorials-genmsg.cmake:3 (message):
  Invoking generate_messages() without having added any message or service
  file before.
```



### 实现

#### cpp

- server

```c++
#include "ros/ros.h"
#include "std_msgs/String.h"

/**
初始化ROS系统
订阅 chatter 话题

进入自循环，等待消息的到达
当消息到达，调用 chatterCallback() 函数
*/

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
// 这是一个回调函数，当接收到 chatter 话题的时候就会被调用。
// 消息是以 boost shared_ptr 指针的形式传输
// 这就意味着你可以存储它而又不需要复制数据。
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
  // ROS话题消息格式("I heard: [%d] [%d]", msg->A, msg->B);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");

  ros::NodeHandle n;

  // NodeHandle::subscribe() 返回 ros::Subscriber 对象,你必须让它处于活动状态直到你不再想订阅该消息。
  // 当这个对象销毁时，它将自动退订 chatter 话题的消息。
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
  
  ros::spin();

  return 0;
}
```

- client

```CPP
#include "ros/ros.h"
#include "beginner_tutorials/AddTwoInts.h"
// 在c++文件声明中既有#include <stdlib.h>也有#include <cstdlib.h>
// 一般更推荐使用C++风格的头文件，即 #include <cstdlib>。
// cstdlib实现了stdlib.h中的所有功能
// 不过是按照C++的方式写的，所以与C++语言可以更好的配合。
//包含了以下函数： 
//1 字符串转换为数字的函数，包括atoi, atof, strtol等。 
//2 随机数函数，包括srand, rand等。 
//3 内存分配释放函数，如malloc,calloc,realloc,free等。 
//4 程序运行控制函数，如exit, abort等。 
//5 系统访问相关函数，如printenv, setenv，system等。 
//6 常用算法函数，如qsort, bsearch, abs,div等。
#include <cstdlib>

// 输入超过3个数异常处理
int main(int argc, char **argv)
{
  ros::init(argc, argv, "add_two_ints_client");
  if (argc != 3)
  {
    ROS_INFO("usage: add_two_ints_client X Y");
    // return 非零 是异常退出
    return 1;
  }

  ros::NodeHandle n;
  // 为add_two_ints service创建一个client。ros::ServiceClient 对象待会用来调用service。
  ros::ServiceClient client = n.serviceClient<beginner_tutorials::AddTwoInts>("add_two_ints");
  // 实例化一个由ROS编译系统自动生成的service类，并给其request成员赋值。
  // 一个service类包含两个成员request和response。同时也包括两个类定义Request和Response。
  beginner_tutorials::AddTwoInts srv;
  srv.request.a = atoll(argv[1]);
  srv.request.b = atoll(argv[2]);

  // 调用service，成功调用返回true
  if (client.call(srv))
  {
    ROS_INFO("Sum: %ld", (long int)srv.response.sum);
  }
  else
  {
    ROS_ERROR("Failed to call service add_two_ints");
    return 1;
  }

  return 0;
}
```

### 测试

- 第一步，启动

`roscore`

- 运行Service

```
rosrun beginner_tutorials add_two_ints_server
```

你将会看到如下类似的信息：

```
Ready to add two ints.
```

- 运行Client

现在，运行Client并附带一些参数：

```
$ rosrun beginner_tutorials add_two_ints_client 1 3     (C++)
$ rosrun beginner_tutorials add_two_ints_client.py 1 3  (Python)
```

你将会看到如下类似的信息：

```
request: x=1, y=3
sending back response: [4]
```

结果如下图：

![cpp_server_client](./cpp_server_client)



现在，你已经成功地运行了你的第一个Service和Client程序

更多功能，可以考虑从这个链接找到[here](https://github.com/fairlight1337/ros_service_examples/)更多的例子～









