## roslaunch tips for large projects | roslaunch在大型项目中的使用技巧

> http://wiki.ros.org/ROS/Tutorials/Roslaunch%20tips%20for%20larger%20projects
>
> http://wiki.ros.org/cn/ROS/Tutorials/Roslaunch%20tips%20for%20larger%20projects
>
> 本节没看懂

### I. 介绍

机器人上的应用经常涉及到[nodes](http://wiki.ros.org/Nodes)间的交互，每个node都有很多的[parameters](http://wiki.ros.org/Parameter%20Server)。在二维平面上的导航就是一个很好的例子。[2dnav_pr2](http://wiki.ros.org/2dnav_pr2) 包含了基本的**运动节点、定位、地面识别、底层控制器和地图服务器**。 同时, 还有几百个 ROS parameters 影响着这些node的行为模式。此外，也还存在着一些额外的约束。例如为了提高效率，地面识别节点应该跟倾斜的激光节点运行在同一台机器上。

一个roslaunch文件能够让你一次性将这些都配置好。在一个机器人上，roslaunch一下*2dnav_pr2* package里的*2dnav_pr2.launch*文件就可以启动机器人导航时所需的所有东西。在本教程中，我们将仔细研究launch文件和它所具有的功能。

我们希望launch文件能够尽可能的重用，这样在不同的机器人平台上就不需要修改这些launch文件就能使用。即使是从真实的环境转到模拟环境中也只要稍微修改即可。接下来，我们将要研究如何构建launch文件才能实现其最大化的重用。

### II. 顶级结构 Top-level organization

> 涉及package: http://wiki.ros.org/pr2_2dnav

出现报错：

```
~/catkin_ws$ source devel/setup.bash
~/catkin_ws$ rospack find 2dnav_pr2/move_base/2dnav_pr2.launch
[rospack] Error: package '2dnav_pr2/move_base/2dnav_pr2.launch' not found
```

解决方案：https://answers.ros.org/question/198132/rospack-2dnav_pr2/

wiki没有提到一件事：需要实现下载pr2_navigation_apps

`git clone https://github.com/PR2/pr2_navigation_apps.git`

下面进入正题：

---

这里是顶级启动文件 (利用指令 `rospack find 2dnav_pr2/move_base/2dnav_pr2.launch`可以找到).

`rospack find pr2_2dnav/pr2_2dnav.launch`修改地址依旧难以解决

```
<launch>
  <group name="wg">
    <include file="$(find pr2_alpha)/$(env ROBOT).machine" />
    <include file="$(find 2dnav_pr2)/config/new_amcl_node.xml" />
    <include file="$(find 2dnav_pr2)/config/base_odom_teleop.xml" />
    <include file="$(find 2dnav_pr2)/config/lasers_and_filters.xml" />
    <include file="$(find 2dnav_pr2)/config/map_server.xml" />
    <include file="$(find 2dnav_pr2)/config/ground_plane.xml" />

    <!-- The navigation stack and associated parameters -->
    <include file="$(find 2dnav_pr2)/move_base/move_base.xml" />
  </group>
</launch>
```

这个文件引用了其他的文件。在这些被引用的文件中都包含有与系统有关的node和parameter（甚至是嵌套引用），比如定位、传感器处理和路径规划。

**编写技巧: 高层级的launch文件应该简短，利用<u>include指令将系统的组成部分</u>和ROS parameter引用过来即可。**

接下来我们将会看到，这种技巧使得我们可以很容易的替换掉系统的某个部分。

想要在PR2运行这个应用，我们需要启动[core](http://wiki.ros.org/roscore)，接着roslaunch一个具体机器人的launch文件，例如在 *pr2_alpha* package里的*pre.launch*文件，最后roslaunch一下*2dnav_pr2.launch*。与其分开roslaunch这么多的文件，我们可以一次性将它们roslaunch起来。这会有一些利弊权衡：

- 优点: 我们可以少做几个 "打开新终端, roslaunch" 的步骤。
- 缺陷1: roslaunch一个launch文件会有一个持续一段时间的校准过程。如果2dnav_pr2 launch文件引用了机器人的launch文件，当我们用control-c终止这个roslaunch进程，然后又再次开启这个进程，校准过程还得再来一遍。
- 缺陷2: 一些导航node要求校准过程必须在它启动之前完成。roslaunch目前还没有对节点的启动时间和顺序进行控制。最完美的方案当然是让导航节点等到校准过程完成后再启动，但就目前的情况来看，把他们分别放在两个launch文件里，直到校准过程结束再启动导航节点是个可行的方案。

因此，对于是否应该把多个启动项放到一个launch文件里并没有一个统一的标准。就本教程的案例而言，我们把他们放到两个launch文件里。

**编写技巧:在决定应用需要多少个高层级的launch文件时，你要考虑利弊的权衡。**

### III. 机器标签和环境变量s

为了平衡负载和管理带宽，我们需要控制哪些节点在哪个机器上运行。比如，我们希望[amcl](http://wiki.ros.org/amcl)跟base laser在同一台机器上运行。同时，考虑到重用性，我们不希望把具体的机器名写入launch文件。roslaunch使用**machine tags**来解决这个问题。

第一个引用如下：

```
<include file="$(find pr2_alpha)/$(env ROBOT).machine" />
```

首先应该注意到这个文件使用 *env* 置换符来使用ROBOT变量的值。例如，在roslaunch指令前执行：

```
export ROBOT=pre
```

将会使得*pre.machine* 被引用。

**编写技巧: 使用 env 置换符可以使得launch文件的一部分依赖于环境变量的值。**

接下来，我们来看看*pr2_alpha* package里的 *pre.machine* 文件。

```
<launch>
  <machine name="c1" address="pre1" ros-root="$(env ROS_ROOT)" ros-package-path="$(env ROS_PACKAGE_PATH)" default="true" />
  <machine name="c2" address="pre2" ros-root="$(env ROS_ROOT)" ros-package-path="$(env ROS_PACKAGE_PATH)" />
</launch>
```

这个文件对本地机器名进行了一个映射，例如"c1" 和 "c2"分别对应于机器名"pre1"和"pre2"。甚至可以控制你登录的用户名。（前提是你有ssh证书）

一旦这个映射建立好了之后，就可以用于控制节点的启动。比如，*2dnav_pr2* package里所引用的*config/new_amcl_node.xml*文件包含这样的语句：

```
<node pkg="amcl" type="amcl" name="amcl" machine="c1">
```

这可以控制 *amcl*节点在机器名为*c1*的机器上运行。（查看其他的launch文件，你可以看到大多数激光传感器处理节点都在这个机器上运行）

当我们要在另一个机器人上运行程序，比如说机器人*prf*，我们只要修改ROBOT环境变量的值就可以了。相应的机器配置文件（*pr2_alpha* package里的*prf.machine*文件）就会被加载。我们甚至可以通过设置ROBOT为*sim*从而是得程序可以在一个模拟机器人上运行。查看*pr2_alpha* package里的*sim.machine*文件，它只是将所有的机器名映射到了本地主机名

**编写技巧: 使用machine tags来平衡负载并控制节点在机器上的启动，同时也因考虑将机器配置文件（.machine)跟系统变量关联起来以便于重复利用。**

### IV. 参数，命名空间与yaml文件

我们来看一下被引用的 *move_base.xml*文件。文件的一部分如下：

```
<node pkg="move_base" type="move_base" name="move_base" machine="c2">
  <remap from="odom" to="pr2_base_odometry/odom" />
  <param name="controller_frequency" value="10.0" />
  <param name="footprint_padding" value="0.015" />
  <param name="controller_patience" value="15.0" />
  <param name="clearing_radius" value="0.59" />
  <rosparam file="$(find 2dnav_pr2)/config/costmap_common_params.yaml" command="load" ns="global_costmap" />
  <rosparam file="$(find 2dnav_pr2)/config/costmap_common_params.yaml" command="load" ns="local_costmap" />
  <rosparam file="$(find 2dnav_pr2)/move_base/local_costmap_params.yaml" command="load" />
  <rosparam file="$(find 2dnav_pr2)/move_base/global_costmap_params.yaml" command="load" />
  <rosparam file="$(find 2dnav_pr2)/move_base/navfn_params.yaml" command="load" />
  <rosparam file="$(find 2dnav_pr2)/move_base/base_local_planner_params.yaml" command="load" />
</node>
```

这一小段代码负责启动*move_base*节点。 第一个引用元素是 **remapping**. 设计Move_base时是希望它从 "odom" topic 接收里程计信息的。在这个pr2案例里，里程计信息是发布在*pr2_base_odometry* topic上,所以我们要重新映射一下。

**编写技巧: 当一个给定类型的信息在不同的情况下发布在不同的topic上，我们可以使用topic remapping**

这个文件有好几个<param>标签。这些参数是节点的内部元素（因为它们都写在</node>之前），因此它们是节点的私有参数[私有参数](http://wiki.ros.org/Parameter%20Server#Private_Parameters)。比如，第一个参数将*move_base/controller_frequency*设置为10.0。

在<param>元素之后,还有一些<rosparam>元素，它们将从yaml文件中读取参数。yaml是一种易于人类读取的文件格式，支持复杂数据的结构。这是第一个<rosparam>所加载的*costmap_common_params.yaml*文件一部分:

```
raytrace_range: 3.0
footprint: [[-0.325, -0.325], [-0.325, 0.325], [0.325, 0.325], [0.46, 0.0], [0.325, -0.325]]
inflation_radius: 0.55

# BEGIN VOXEL STUFF
observation_sources: base_scan_marking base_scan tilt_scan ground_object_cloud

base_scan_marking: {sensor_frame: base_laser, topic: /base_scan_marking, data_type: PointCloud, expected_update_rate: 0.2,
  observation_persistence: 0.0, marking: true, clearing: false, min_obstacle_height: 0.08, max_obstacle_height: 2.0}
```

我们看到yaml支持向量等数据结构（如上边的*footprint*就是向量）。它同样支持将嵌套的[域名空间](http://wiki.ros.org/Names)，比如*base_laser*被归属到了*base_scan_marking/sensor_frame*这样的嵌套域名下。注意这些域名都是归属于yaml文件自身域名*global_costmap*之下，而yaml文件的域名是由*ns*变量来控制的。 同样的, 由于 *rosparam* 都被包含在节点里, 所以参数的完整名称就是*/move_base/global_costmap/base_scan_marking/sensor_frame*.

接着一行是:

```
<rosparam file="$(find 2dnav_pr2)/config/costmap_common_params.yaml" command="load" ns="local_costmap" />
```

这跟上一行引用的是完全一样的yaml文件，只不过他们的域名空间不一样（local_costmap域名只影响运动路径控制器，而global_costmap影响到全局的导航规划）。这样可以避免重新给同样的变量再次赋值。

再下一行是:

```
<rosparam file="$(find 2dnav_pr2)/move_base/local_costmap_params.yaml" command="load"/>
```

跟上一行不同，这一行没有*ns*属性。因此这个yaml文件的域名就是*/move_base*。但是再仔细查看一下这个yaml文件的前几行：

```
local_costmap:
  #Independent settings for the local costmap
  publish_voxel_map: true
  global_frame: odom_combined
  robot_base_frame: base_link
```

最终我们可以确定参数都是归属于*/move_base/local_costmap*域名之下。

**编写技巧: Yaml文件允许复杂的嵌套域名的参数，相同的参数值可以在多个地方重复使用。**

### V. launch文件的重用

上述的编写技巧都是为了使得launch文件能再不同的环境下更易于重用。从上边的一个例子我们已经知道，使用*env*子变量可以在不改动launch文件的情况下就改变其行为模式。但是仍然在某些情况下，重用launch文件还是很麻烦甚至不肯能。我们来看一下[pr2_2dnav_gazebo](http://wiki.ros.org/pr2_2dnav_gazebo) package。它有2d导航功能，但是只是为[Gazebo模拟器](http://wiki.ros.org/simulator_gazebo)而设计的。 对于导航来说，唯一改变了的就是我们所使用的Gazebo环境是一张静态地图，因此map_server节点必须重载其参数。当然这里我们可以使用另外一个env变量，但这会使得用户还得设置一大堆变量才能够roslaunch。 因此，2dnav gazebo有它自己的高层级launch文件，叫'2dnav-stack-amcl.launch'，如下所示：

```
<launch>
  <include file="$(find pr2_alpha)/sim.machine" />
  <include file="$(find 2dnav_pr2)/config/new_amcl_node.xml" />
  <include file="$(find 2dnav_pr2)/config/base_odom_teleop.xml" />
  <include file="$(find 2dnav_pr2)/config/lasers_and_filters.xml" />
  <node name="map_server" pkg="map_server" type="map_server" args="$(find gazebo_worlds)/Media/materials/textures/map3.png 0.1" respawn="true" machine="c1" />
  <include file="$(find 2dnav_pr2)/config/ground_plane.xml" />
  <!-- The naviagtion stack and associated parameters -->
  <include file="$(find 2dnav_pr2)/move_base/move_base.xml" />
</launch>
```

首先，因为我们知道这是一个模拟器，所以直接使用sim.machine文件，而不必再使用$(env ROBOT)变量来选择。其次，原来的

```
<include file="$(find 2dnav_pr2)/config/map_server.xml" />
```

已经被

```
<node name="map_server" pkg="map_server" type="map_server" args="$(find gazebo_worlds)/Media/materials/textures/map3.png 0.1" respawn="true" machine="c1" />
```

所替换。两者都包含了节点的声明，但他们来自不同的文件。

**编写技巧: 想要改变应用的高层级功能，只要修改launch文件的相应部分即可。**

### VI. 参数重载

在某些情况下，上述技巧会很不方便。比如，使用*2dnav_pr2*但希望修改local costmap的分辨率为0.5。我们只需要修改*local_costmap_params.yaml*文件即可。我们本来只是想临时的修改，但这种方法却意味着它被永久修改了。也许我们可以将*local_costmap_params.yaml*文件拷贝一份并做修改，但这样我们还需要修改*move_base.xml*文件去引用修改后的yaml文件。 接着我们还得修改 *2dnav_pr2.launch*文件去引用被修改后的xml文件。这是很花时间的工作，而且假如我们使用了版本控制，我却看不到版本间有任何的改变。另外一种方法是新建立一个launch文件，这样就可以在*2dnav_pr2.launch*文件中定义*move_base/local_costmap/resolution*参数，修改这个参数就可以满足我们都要求。如果我们能够提前知道哪些参数有可能被修改，这会是一个很好的办法。

更好的方法是利用roslaunch的重载特性：参数按顺序赋值(在引用被执行之后)。这样，我们可以构建另外一个可以重载参数的高层级文件：

```
<launch>
<include file="$(find 2dnav_pr2)/move_base/2dnav_pr2.launch" />
<param name="move_base/local_costmap/resolution" value="0.5"/>
</launch>
```

这个方法的主要缺点在于它使得文件难以理解：想要知道一个参数的值需要追溯launch的引用。但它确实避免了多次拷贝文件然后修改它们。

**编写技巧: 利用roslaunch重载功能来修改一个深深嵌套在launch文件分支中的参数。**

### VII. Roslaunch 参数

在CTurtle版本中，roslaunch还有一个和标签(tags)类似的参数替换特性，它允许依据变量的值来有条件启动某个launch文件。这比上述的参数重载和launch文件重用来得更简洁，适用性更强。但它需要一些额外操作来完成这个功能：修改原始launch文件来指定哪些变量是可变的。请参考[roslaunch XML documentation](http://wiki.ros.org/roslaunch/XML).