## 180531 ROS Notes

---

### 1.配置确认

```bash
% 小龟操作确认安装正确，分三个终端输入一下命令
% roscore %启动ROS
$ rosrun turtlesim turtlesim_node %打开乌龟节点
$ rosrun turtlesim  turtle_teleop_key %乌龟按键反馈
```

### 2.Lecture: ROS-Academy-for-Beginners

> gitbook: https://sychaichangkun.gitbooks.io/ros-tutorial-icourse163/content/
>
> github: https://github.com/DroidAITech/ROS-Academy-for-Beginners
>
> mooc: https://www.icourse163.org/course/ISCAS-1002580008#/info

### 3.相关操作设置

在章节[1.5 安装ROS-Academy-for-Beginners教学包](https://sychaichangkun.gitbooks.io/ros-tutorial-icourse163/content/chapter1/1.5.html)中，使用相关命令

```bash
% 一个新窗口
$ rospack profile
$ roslaunch robot_sim_demo robot_spawn.launch
% 再一个新窗口
$ rosrun robot_sim_demo robot_keyboard_teleop.py
```

会多次报错，结果发现缺少依赖包，可以进行如下操作

```bash
% 检查package的依赖是否满足
$ rosdep check robot_sim_demo
$ rosdep install robot_sim_demo
% 若报错无法安装，则需使用下面描述的命令
$ sudo apt-get install ros-kinetic-PACAKGE
```

---

### 感想

今天将[《机器人系统操作入门》](https://legacy.gitbook.com/book/sychaichangkun/ros-tutorial-icourse163/details)前两章节过了一遍，对于初始demo进行了尝试，也开始逐渐了解每一个ROS Package的架构，并且开始使用`roscd`之类的命令

















