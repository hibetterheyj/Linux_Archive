## 安装并配置ROS环境——创建ROS工作空间

---

下面我们开始创建一个[catkin 工作空间](http://wiki.ros.org/catkin/workspaces)： 

```bash
$ mkdir -p ~/catkin_ws/src
% 建立路径产生的所有文件夹
$ cd ~/catkin_ws/src
```

即使这个工作空间是空的（在'src'目录中没有任何软件包，只有一个`CMakeLists.txt`链接文件），你依然可以编译它： 

```bash
$ cd ~/catkin_ws/
% cd ..也是可以
$ catkin_make
```

[catkin_make](http://wiki.ros.org/catkin/commands/catkin_make)命令在[catkin 工作空间](http://wiki.ros.org/catkin/workspaces)中是一个非常方便的工具。如果你查看一下当前目录应该能看到'build'和'devel'这两个文件夹。在'devel'文件夹里面你可以看到几个`setup.*sh`文件。`source`这些文件中的任何一个都可以将当前工作空间设置在ROS工作环境的最顶层，想了解更多请参考[catkin](http://wiki.ros.org/catkin)文档。接下来首先`source`一下新生成的`setup.*sh`文件： 

```bash
$ source devel/setup.bash
```

要想保证工作空间已配置正确需确保`ROS_PACKAGE_PATH`环境变量包含你的工作空间目录，采用以下命令查看： 

```bash
$ echo $ROS_PACKAGE_PATH
/home/<youruser>/catkin_ws/src:/opt/ros/indigo/share:/opt/ros/indigo/stacks
%%%
$ echo $ROS_PACKAGE_PATH
/home/philhe/catkin_ws/ src:/opt/ros/kinetic/ share:/opt/ros/kinetic/share
% 首先这条命令<youruser>/要替换，indigo应该为kinetic，share地址注意catkin_make的反馈
```

到此你的工作环境已经搭建完成，接下来可以继续学习 [ROS文件系统教程](http://wiki.ros.org/cn/ROS/Tutorials/NavigatingTheFilesystem). 