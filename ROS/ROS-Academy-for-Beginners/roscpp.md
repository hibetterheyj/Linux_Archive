## 6.1 Client Library与roscpp

> https://sychaichangkun.gitbooks.io/ros-tutorial-icourse163/chapter6/

### 6.1.1 Client Library简介

ROS为机器人开发者们提供了不同语言的编程接口，比如C++接口叫做roscpp，Python接口叫做rospy，Java接口叫做rosjava。尽管语言不通，但这些接口都可以用来创建topic、service、param，实现ROS的通信功能。Clinet Lirary有点类似开发中的Helper Class，把一些常用的基本功能做了封装。

目前ROS支持的Clinet Library包括：

| Client Library | 介绍                                                         |
| -------------- | ------------------------------------------------------------ |
| roscpp         | ROS的C++库，是目前最广泛应用的ROS客户端库，执行效率高        |
| rospy          | ROS的Python库，开发效率高，通常用在对运行时间没有太大要求的场合，例如配置、初始化等操作 |

目前最常用的只有roscpp和rospy，而其余的语言版本基本都还是测试版。

### 6.2 节点初始、关闭以及NodeHandle

C++写的ROS程序，区别于普通C++程序，代码中做了两层工作：

1. 调用ros::init()`函数，从而初始化节点的名称和其他信息，一般ROS程序一开始都会以这种方式开始。
2. 创建`ros::NodeHandle`对象，也是节点的句柄，可以用来创建Publisher、Subscriber以及做其他事情。

NodeHandle就是对节点资源的描述，有了它你就可以操作这个节点了，比如为程序提供服务、监听某个topic上的消息、访问和修改param等等。

---

ROS程序的执行步骤，通常要启动节点，获取句柄，而关闭的工作系统自动完成。

```c++
#include<ros/ros.h>
int main(int argc, char** argv)
{
    ros::init(argc, argv, "your_node_name"); 
    ros::NodeHandle nh;
    //....节点功能
    //....
    ros::spin();//用于触发topic、service的响应队列
    return 0;
}
```

**NodeHandle常用成员函数**包括：

### 6.3 topic_demo

### 6.4 service_demo

### 6.5 param_demo

我们来看看在C++中如何进行param_demo的操作，`param_demo/param.cpp`文件，内容包括：

```c++
//创建话题的publisher 
ros::Publisher advertise(const string &topic, uint32_t queue_size, bool latch=false); 
//第一个参数为发布话题的名称
//第二个是消息队列的最大长度，如果发布的消息超过这个长度而没有被接收，那么就的消息就会出队。通常设为一个较小的数即可。
//第三个参数是是否锁存。某些话题并不是会以某个频率发布，比如/map这个topic，只有在初次订阅或者地图更新这两种情况下，/map才会发布消息。这里就用到了锁存。

//创建话题的subscriber
ros::Subscriber subscribe(const string &topic, uint32_t queue_size, void(*)(M));
//第一个参数是订阅话题的名称
//第二个参数是订阅队列的长度，如果受到的消息都没来得及处理，那么新消息入队，就消息就会出队
//第三个参数是回调函数指针，指向回调函数来处理接收到的消息

//创建服务的server，提供服务
ros::ServiceServer advertiseService(const string &service, bool(*srv_func)(Mreq &, Mres &)); 
//第一个参数是service名称
//第二个参数是服务函数的指针，指向服务函数。指向的函数应该有两个参数，分别接受请求和响应。

//创建服务的client
ros::ServiceClient serviceClient(const string &service_name, bool persistent=false); 
//第一个函数式service名称
//第二个参数用于设置服务的连接是否持续，如果为true，client将会保持与远程主机的连接，这样后续的请求会快一些。通常我们设为flase

//查询某个参数的值
bool getParam(const string &key, std::string &s); 
bool getParam (const std::string &key, double &d) const；
bool getParam (const std::string &key, int &i) const；
//从参数服务器上获取key对应的值，已重载了多个类型

//给参数赋值
void setParam (const std::string &key, const std::string &s) const；
void setParam (const std::string &key, const char *s) const;
void setParam (const std::string &key, int i) const;
//给key对应的val赋值，重载了多个类型的val
```

`const` 常数变量

实际项目中我们对参数进行设置，尤其是添加参数，一般都不是在程序中，而是在launch文件中。因为launch文件可以方便的修改参数，而写成代码之后，修改参数必须重新编译。 因此我们会在launch文件中将param都定义好，比如这个demo正确的打开方式应该是`roslaunch param_demo param_demo_cpp.launch`



