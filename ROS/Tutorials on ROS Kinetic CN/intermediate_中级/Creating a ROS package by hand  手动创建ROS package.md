## Creating a ROS package by hand | 手动创建ROS package

> http://wiki.ros.org/ROS/Tutorials/Creating%20a%20Package%20by%20Hand

我们可以使用([catkin_create_pkg](http://wiki.ros.org/catkin/commands/catkin_create_pkg))工具来自动创建ROS package，不过，接下来你就会发现，这不是什么难事。 `roscreate-pkg`节省精力避免错误，但package只不过就是一个文件夹外加一个XML文件。

现在，我们要手动创建一个名为foobar的package。请转至你的catkin workspace，并确认你已经刷新了setup文件。

```
catkin_ws_top $ mkdir -p src/foobar
catkin_ws_top $ cd src/foobar
```

我们要做的第一件事就是添加配置文件。 `package.xml` 文件使得像[rospack](http://wiki.ros.org/rospack)这类工具能够检测出我们所创建的package的依赖项.

在 `foobar/package.xml`文件里添加如下语句:

```
<package format="2">
  <name>foobar</name>
  <version>1.2.4</version>
  <description>
  This package provides foo capability.
  </description>
  <maintainer email="foobar@foo.bar.willowgarage.com">PR-foobar</maintainer>
  <license>BSD</license>

  <buildtool_depend>catkin</buildtool_depend>

  <build_depend>roscpp</build_depend>
  <build_depend>std_msgs</build_depend>

  <exec_depend>roscpp</exec_depend>
  <exec_depend>std_msgs</exec_depend>
</package>
```

同样，你可以参考 [this page from catkin tutorial](http://wiki.ros.org/catkin/Tutorials/CreatingPackage#ROS.2BAC8-Tutorials.2BAC8-catkin.2BAC8-CreatingPackage.Customizing_the_package.xml) 以获得更多关于 [catkin/package.xml](http://wiki.ros.org/catkin/package.xml)的信息。

现在，你的package里已经包含配置文件(package.xml)，ROS能够找到它。试一试，执行如下指令：

```
rospack find foobar
```

如果ROS配置正确，你将会看到类似如下的信息： `/home/user/ros/catkin_ws_top/src/foobar`. 这就是ROS如何在后台寻找package的机理。

应该注意到我们刚才所创建的package依赖于 [roscpp](http://wiki.ros.org/roscpp) 和 [std_msgs](http://wiki.ros.org/std_msgs).而[catkin](http://wiki.ros.org/catkin)恰恰是利用这些依赖项来配置所创建的package。

至此，我们还需要一个 [CMakeLists.txt](http://wiki.ros.org/CMakeLists) 文件，这样 [catkin_make](http://wiki.ros.org/catkin_make)才能够利用 CMake 强大的跨平台特性来编译所创建的package。

在 `foobar/CMakeLists.txt`文件里输入：

```
cmake_minimum_required(VERSION 2.8.3)
project(foobar)
find_package(catkin REQUIRED roscpp std_msgs)
catkin_package()
```

这就是你想在ROS下用catkin编译package所要做的全部工作。当然了，如果想要让它正真的编译一些东西，你还需要学习关于CMake宏的一些知识。 请参考 [CMakeLists.txt](http://wiki.ros.org/catkin/CMakeLists.txt) 以获得更多信息。回顾初级教程如 ([CreatingPackage](http://wiki.ros.org/ROS/Tutorials/CreatingPackage) 等) 来修改你的 `package.xml` 和 `CMakeLists.txt`文件