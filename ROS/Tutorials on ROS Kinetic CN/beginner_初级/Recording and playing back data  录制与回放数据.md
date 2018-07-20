## Recording and playing back data | 录制与回放数据

> http://wiki.ros.org/ROS/Tutorials/Recording%20and%20playing%20back%20data
>
> 中文包过于老旧，输出.bag文件信息与以往不同了

### I. 录制数据（通过创建一个bag文件）

本小节将教你如何记录ROS系统运行时的话题数据，记录的话题数据将会累积保存到bag文件中。

首先，执行以下命令：

```
roscore
rosrun turtlesim turtlesim_node 
rosrun turtlesim turtle_teleop_key
```

以上操作将会启动两个节点——一个turtlesim可视化节点和一个turtlesim键盘控制节点。在运行turtlesim键盘控制节点的终端窗口中你应该会看到如下类似信息：

```
Reading from keyboard
---------------------------
Use arrow keys to move the turtle.
```

这时按下键盘上的方向键应该会让turtle运动起来。需要注意的是要想控制turtle运动你必须先选中启动turtlesim键盘控制节点时所在的终端窗口而不是显示虚拟turtle所在的窗口。

#### 1.1 录制所有发布的话题

首先让我们来检查看当前系统中发布的所有话题。要完成此操作请打开一个新终端并执行：

```
rostopic list -v
```

这应该会生成以下输出：

```
Published topics:
 * /turtle1/color_sensor [turtlesim/Color] 1 publisher
 * /turtle1/command_velocity [turtlesim/Velocity] 1 publisher
 * /rosout [roslib/Log] 2 publishers
 * /rosout_agg [roslib/Log] 1 publisher
 * /turtle1/pose [turtlesim/Pose] 1 publisher

Subscribed topics:
 * /turtle1/command_velocity [turtlesim/Velocity] 1 subscriber
 * /rosout [roslib/Log] 1 subscriber
```

上面所发布话题部分列出的话题消息是唯一可以被录制保存到文件中的的话题消息，因为只有消息已经发布了才可以被录制。`/turtle1/command_velocity`话题是`teleop_turtle`节点所发布的命令消息并作为turtlesim节点的输入。而`/turtle1/color_sensor`和`/turtle1/pose`是`turtlesim`节点发布出来的话题消息。

现在我们开始录制。打开一个新的终端窗口，在终端中执行以下命令：

```
mkdir ~/bagfiles
cd ~/bagfiles
rosbag record -a
```

在这里我们先建立一个用于录制的临时目录，然后在该目录下运行**rosbag record**命令，并附加**-a**选项，该选项表示将当前发布的所有话题数据都录制保存到一个bag文件中。

然后回到turtle_teleop节点所在的终端窗口并控制turtle随处移动10秒钟左右。

在运行**rosbag record**命令的窗口中按Chttp://wiki.ros.org/ROS/Tutorials/Recording%20and%20playing%20back%20datatrl-C退出该命令。现在检查看`~/bagfiles`目录中的内容，你应该会看到一个以年份、日期和时间命名并以.bag作为后缀的文件。这个就是bag文件，它包含**rosbag record**运行期间所有节点发布的话题。

### II. 检查并回放bag文件

现在我们已经使用**rosbag record**命令录制了一个bag文件，接下来我们可以使用**rosbag info**检查看它的内容，使用**rosbag play**命令回放出来。接下来我们首先会看到在bag文件中都录制了哪些东西。我们可以使用**info**命令，该命令可以检查看bag文件中的内容而无需回放出来。在bag文件所在的目录下执行以下命令：

```
rosbag info <your bagfile>
```

你应该会看到如下类似信息：

```
path:        2014-12-10-20-08-34.bag
version:     2.0
duration:    1:38s (98s)
start:       Dec 10 2014 20:08:35.83 (1418270915.83)
end:         Dec 10 2014 20:10:14.38 (1418271014.38)
size:        865.0 KB
messages:    12471
compression: none [1/1 chunks]
types:       geometry_msgs/Twist [9f195f881246fdfa2798d1d3eebca84a]
             rosgraph_msgs/Log   [acffd30cd6b6de30f120938c17c593fb]
             turtlesim/Color     [353891e354491c51aabe32df673fb446]
             turtlesim/Pose      [863b248d5016ca62ea2e895ae5265cf9]
topics:      /rosout                    4 msgs    : rosgraph_msgs/Log   (2 connections)
             /turtle1/cmd_vel         169 msgs    : geometry_msgs/Twist
             /turtle1/color_sensor   6149 msgs    : turtlesim/Color    
             /turtle1/pose           6149 msgs    : turtlesim/Pose
```

这些信息告诉你bag文件中所包含话题的名称、类型和消息数量。我们可以看到，在之前使用**rostopic**命令查看到的五个已公告的话题中，其实只有其中的四个在我们录制过程中发布了消息。因为我们带-a参数选项运行**rosbag record**命令时系统会录制下所有节点发布的所有消息。

下一步是回放bag文件以再现系统运行过程。首先在turtle_teleop_key节点运行时所在的终端窗口中按Ctrl+C退出该节点。让turtlesim节点继续运行。在终端中bag文件所在目录下运行以下命令：

```
rosbag play <your bagfile>
```

在这个窗口中你应该会立即看到如下类似信息：

```
Hit space to pause.
[ INFO] 1260210510.566003000: Sleeping 0.200 seconds after advertising /rosout...
[ INFO] 1260210510.766582000: Done sleeping.

[ INFO] 1260210510.872197000: Sleeping 0.200 seconds after advertising /turtle1/pose...
[ INFO] 1260210511.072384000: Done sleeping.

[ INFO] 1260210511.277391000: Sleeping 0.200 seconds after advertising /turtle1/color_sensor...
[ INFO] 1260210511.477525000: Done sleeping.
```

默认模式下，**rosbag play**命令在公告每条消息后会等待一小段时间（0.2秒）后才真正开始发布bag文件中的内容。等待一段时间的过程可以通知消息订阅器消息已经公告了消息数据可能会马上到来。如果**rosbag play**在公告消息后立即发布，订阅器可能会接收不到几条最先发布的消息。等待时间可以通过-d选项来指定。

最终/turtle1/command_velocity话题将会被发布，同时在turtuelsim虚拟画面中turtle应该会像之前你通过turtle_teleop_key节点控制它一样开始移动。从运行**rosbag play**到turtle开始移动时所经历时间应该近似等于之前在本教程开始部分运行**rosbag record**后到开始按下键盘发出控制命令时所经历时间。你可以通过-s参数选项让**rosbag play**命令等待一段时间跳过bag文件初始部分后再真正开始回放。

最后一个可能比较有趣的参数选项是-r选项，它允许你通过设定一个参数来改变消息发布速率。如果你执行：

```
rosbag play -r 2 <your bagfile>
```

你应该会看到turtle的运动轨迹有点不同了，这时的轨迹应该是相当于当你以两倍的速度通过按键发布控制命令时产生的轨迹。

### III. 录制数据子集

当运行一个复杂的系统时，比如PR2软件系统，会有几百个话题被发布，有些话题会发布大量数据（比如包含摄像头图像流的话题）。在这种系统中，要想把所有话题都录制保存到硬盘上的单个bag文件中是不切实际的。**rosbag record**命令支持只录制某些特别指定的话题到单个bag文件中，这样就允许用户只录制他们感兴趣的话题。

如果还有turtlesim节点在运行，先退出他们，然后重新启动（relaunch）键盘控制节点相关的启动文件（launch file)：

```
rosrun turtlesim turtlesim_node 
rosrun turtlesim turtle_teleop_key
```

在bag文件所在目录下执行以下命令：

```
rosbag record -O subset /turtle1/command_velocity /turtle1/pose
```

上述命令中的-O参数告诉**rosbag record**将数据记录保存到名为subset.bag的文件中，同时后面的话题参数告诉**rosbag record**只能录制这两个指定的话题。然后通过键盘控制turtle随处移动几秒钟，最后按Ctrl+C退出**rosbag record**命令。

现在检查看bag文件中的内容（**rosbag info subset.bag**）。你应该会看到如下类似信息，里面只包含录制时指定的话题：

```
path:        subset.bag
version:     2.0
duration:    12.6s
start:       Dec 10 2014 20:20:49.45 (1418271649.45)
end:         Dec 10 2014 20:21:02.07 (1418271662.07)
size:        68.3 KB
messages:    813
compression: none [1/1 chunks]
types:       geometry_msgs/Twist [9f195f881246fdfa2798d1d3eebca84a]
             turtlesim/Pose      [863b248d5016ca62ea2e895ae5265cf9]
topics:      /turtle1/cmd_vel    23 msgs    : geometry_msgs/Twist
             /turtle1/pose      790 msgs    : turtlesim/Pose
```

### IV. rosbag record/play 命令的局限性

在前述部分中你可能已经注意到了turtle的路径可能并没有完全地映射到原先通过键盘控制时产生的路径上——整体形状应该是差不多的，但没有完全一样。造成该问题的原因是turtlesim的移动路径对系统定时精度的变化非常敏感。

rosbag受制于其本身的性能无法完全复制录制时的系统运行行为，rosplay也一样。对于像turtlesim这样的节点，当处理消息的过程中系统定时发生极小变化时也会使其行为发生微妙变化，用户不应该期望能够完美的模仿系统行为。