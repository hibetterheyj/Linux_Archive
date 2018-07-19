## Using rqt_console and roslaunch | 使用 rqt_console 和 roslaunch

### 使用rqt_console和rqt_logger_level

`rqt_console`属于ROS日志框架(logging framework)的一部分，用来显示节点的输出信息。`rqt_logger_level`允许我们修改节点运行时输出信息的日志等级（logger levels）（包括 DEBUG、WARN、INFO和ERROR）。

现在让我们来看一下turtlesim在`rqt_console`中的输出信息，同时在`rqt_logger_level`中修改日志等级。在启动turtlesim之前先在另外两个新终端中运行`rqt_console`和`rqt_logger_level`：

```
$ rosrun rqt_console rqt_console
```

```
$ rosrun rqt_logger_level rqt_logger_level
```

你会看到弹出两个窗口

接着，在一个**新终端**中启动turtlesim：

```
$ rosrun turtlesim turtlesim_node
```

因为默认日志等级是INFO，所以你会看到turtlesim启动后输出的所有信息，现在让我们刷新一下rqt_logger_level窗口并选择Warn将日志等级修改为WARN。

现在我们让turtle动起来并观察rqt_console中的输出：

```
rostopic pub /turtle1/cmd_vel geometry_msgs/Twist -r 1 -- '[2.0, 0.0, 0.0]' '[0.0, 0.0, 0.0]'
```

会出现大量报错！

#### 日志等级说明

日志等级按以下优先顺序排列：

```
Fatal, Error, Warn, Info, Debug
```

`Fatal`是最高优先级，`Debug`是最低优先级。通过设置日志等级你可以获取该等级及其以上优先等级的所有日志消息。比如，将日志等级设为`Warn`时，你会得到`Warn`、`Error`和`Fatal`这三个等级的所有日志消息。

现在让我们按`Ctrl-C`退出turtlesim节点，接下来我们将使用`roslaunch`来启动多个turtlesim节点和一个模仿节点以让一个turtlesim节点来模仿另一个turtlesim节点。

#### 使用roslaunch

`roslaunch`可以用来启动定义在launch文件中的多个节点。

用法：

```
$ roslaunch [package] [filename.launch]
```

先切换到`beginner_tutorials`程序包目录下：

```
$ source ~/catkin_ws/devel/setup.bash
$ roscd beginner_tutorials
```

然后创建一个launch文件夹：

```
$ mkdir launch
$ cd launch
```

#### Launch 文件与解析

现在我们来创建一个名为turtlemimic.launch的launch文件并复制粘贴以下内容到该文件里面：

切换行号显示

```xml
<!--本句说明launch文件的开始-->
<launch>

<!--在这里我们创建了两个节点分组并以'命名空间（namespace)'标签来区分两个组里面都使用相同的turtlesim节点并命名为'sim'。这样可以让我们同时启动两个turtlesim模拟器而不会产生命名冲突。-->
  <group ns="turtlesim1">
    <node pkg="turtlesim" name="sim" type="turtlesim_node"/>
  </group>

  <group ns="turtlesim2">
    <node pkg="turtlesim" name="sim" type="turtlesim_node"/>
  </group>

<!--在这里我们启动模仿节点，并将所有话题的输入和输出分别重命名为turtlesim1和turtlesim2，这样就会使turtlesim2模仿turtlesim1。-->
  <node pkg="turtlesim" name="mimic" type="mimic">
    <remap from="input" to="turtlesim1/turtle1"/>
    <remap from="output" to="turtlesim2/turtle1"/>
  </node>

</launch>
```

现在让我们通过`roslaunch`命令来启动launch文件：

```
$ roslaunch beginner_tutorials turtlemimic.launch
```

现在将会有两个turtlesims被启动，然后我们在一个**新终端**中使用`rostopic`命令发送速度设定消息：

```
$ rostopic pub /turtlesim1/turtle1/cmd_vel geometry_msgs/Twist -r 1 -- '[2.0, 0.0, 0.0]' '[0.0, 0.0, -1.8]'
```

你会看到两个turtlesims会同时开始移动，虽然发布命令只是给turtlesim1发送了速度设定消息。

我们也可以通过[rqt_graph](http://wiki.ros.org/rqt_graph)来更好的理解在launch文件中所做的事情。运行[rqt](http://wiki.ros.org/rqt)并在主窗口中选择[rqt_graph](http://wiki.ros.org/rqt_graph)：

```
$ rqt
```

或者直接运行：

```
$ rqt_graph
```

