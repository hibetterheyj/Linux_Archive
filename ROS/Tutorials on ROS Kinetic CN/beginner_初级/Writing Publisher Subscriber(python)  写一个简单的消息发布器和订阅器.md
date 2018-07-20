## Writing Publisher Subscriber(python) | 写一个简单的消息发布器和订阅器

### 代码实现

#### Python

- **Publisher Node**

```python
#!/usr/bin/env python
# the first import for python in ROS

import rospy
# reuse the std_msgs/String message type
# (a simple string container) for publishing.
from std_msgs.msg import String

# define a function talker():
def talker():
    # node is publishing to the **chatter** topic using the message type String. 
    # String here is actually the class std_msgs.msg.String. 
    # The queue_size argument is 10
    pub = rospy.Publisher('chatter', String, queue_size=10)
    # rospy has this information before starting communicating with the ROS Master.
    # In this case, your node will take on the name **talker**. 
    #http://wiki.ros.org/rospy/Overview/Initialization%20and%20Shutdown#Initializing_your_ROS_Node
    rospy.init_node('talker', anonymous=True)


    # the loop 10 times per second
    rate = rospy.Rate(10) # 10hz

    while not rospy.is_shutdown():
        hello_str = "hello world %s" % rospy.get_time()
        rospy.loginfo(hello_str)
        pub.publish(hello_str)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
```

- **Sub Node**

```
#!/usr/bin/env python
# must in first line! 

## Simple talker demo that listens to std_msgs/Strings published 
## to the 'chatter' topic

import rospy
from std_msgs.msg import String

# a callback mechanism
def callback(data):
    rospy.loginfo(rospy.get_caller_id() + 'I heard %s', data.data)

def listener():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('listener', anonymous=True)

    rospy.Subscriber('chatter', String, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()
```

- 出现bug





#### Cpp

> 推荐阅读：http://wiki.ros.org/roscpp/Overview， http://wiki.ros.org/roscpp_tutorials

- talker.cpp

```c++
#include "ros/ros.h"
// 这引用了 std_msgs/String 消息
// 它存放在 std_msgs package 里，是由 String.msg 文件自动生成的头文件。
// 具体格式未 String data
#include "std_msgs/String.h"
#include <sstream>

  /**
   * 初始化 ROS 系统
   * 在 ROS 网络内广播我们将要在 chatter 话题上发布 std_msgs/String 类型的消息
   * 以每秒 10 次的频率在 chatter 上发布消息
   */


int main(int argc, char **argv)
{

  ros::init(argc, argv, "talker");


  // 为这个进程的节点创建一个句柄。
  // 第一个创建的 NodeHandle 会为节点进行初始化，最后一个销毁的 NodeHandle
  // 则会释放该节点所占用的所有资源。
  ros::NodeHandle n;

  // 告诉 master 我们将要在 chatter（话题名） 上发布 std_msgs/String 消息类型的消息。
  // 这样 master 就会告诉所有订阅了 chatter 话题的节点，将要有数据发布。
  // 第二个参数是发布序列的大小。
  // advertise() 返回一个 ros::Publisher 对象,它有两个作用： 
  // 1) 它有一个 publish() 成员函数可以让你在topic上发布消息； 2) 如果消息类型不对,它会拒绝发布。
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

  // ros::Rate 对象可以允许你指定自循环的频率。它会追踪记录自上一次调用 Rate::sleep() 后时间的流逝，
  // 并休眠直到一个频率周期的时间。在这个例子中，我们让它以 10Hz 的频率运行。
  ros::Rate loop_rate(100);


  int count = 0;
  while (ros::ok())
  {编写简单的服务器和客户端 (C++)编写简单的服务器和客户端 (C++)

    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world " << count;
    // std_msgs/String data
    msg.data = ss.str();

    // ROS_INFO 和其他类似的函数可以用来代替 printf/cout 等函数。
    // 具体可以参考 rosconsole documentation，以获得更多信息。
    ROS_INFO("%s", msg.data.c_str());

    // 向所有订阅 chatter 话题的节点发送消息。
    chatter_pub.publish(msg);

    // 并不是一定要调用 ros::spinOnce()，因为我们不接受回调。然而，如果你的程序里包含其他回调函数
    // 最好在这里加上 ros::spinOnce()这一语句，否则你的回调函数就永远也不会被调用了。
    ros::spinOnce();

    // 调用 ros::Rate 对象来休眠一段时间以使得发布频率为 10Hz。
    loop_rate.sleep();
    ++count;
  }


  return 0;
}
```

- listener.cpp

```c++
#include "ros/ros.h"
#include "std_msgs/String.h"

/**
初始化ROS系统
订阅 chatter 话题

进入自循环，等待消息的到达
当消息到达，调用 chatterCallback() 函数
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

- 相关操作

编译

```bash
# In your catkin workspace
$ catkin_make  
```

ROS内Cpp输出

```
ROS::INFO("I heard: [%s]", msg->A)
print("I heard: [%s]")
```



### 最终操作

确保roscore可用，并运行：

```
$ roscore
```

catkin specific 如果使用catkin，确保你在调用`cat编写简单的服务器和客户端 (C++)kin_make`后，在运行你自己的程序前，已经source了catkin工作空间下的setup.sh文件：

```
# In your catkin workspace
$ cd ~/catkin_ws
$ source ./devel/setup.bash
```

In the last tutorial we made a publisher called "talker". Let's run it:

```
$ rosrun beginner_tutorials talker      (C++)
$ rosrun beginner_tutorials talker.py   (Python) 
```

你将看到publisher的输出信息。

现在运行它：

```
$ source ./devel/setup.bash

$ rosrun beginner_tutorials listener     (C++)
$ rosrun beginner_tutorials listener.py  (Python) 
```

你将会看到如下的输出信息

