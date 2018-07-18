## Understanding ROS Topics | 理解ROS 话题

## Setup

### roscore

Let's start by making sure that we have roscore running, **in a new terminal**:

```
$ roscore
```

If you left roscore running from the last tutorial, you may get the error message:

- 

  

  

  ```
  roscore cannot run as another roscore/master is already running. 
  Please kill other roscore/master processes before relaunching
  ```

  

This is fine. Only one roscore needs to be running.

### turtlesim

For this tutorial we will also use turtlesim. Please run **in a new terminal**:

```
$ rosrun turtlesim turtlesim_node
```

### turtle keyboard teleoperation

We'll also need something to drive the turtle around with. Please run **in a new terminal**:

```
$ rosrun turtlesim turtle_teleop_key
```

- 

  

  

  

  

  ```
  [ INFO] 1254264546.878445000: Started node [/teleop_turtle], pid [5528], bound on [aqy], xmlrpc port [43918], tcpros port [55936], logging to [~/ros/ros/log/teleop_turtle_5528.log], using [real] time
  Reading from keyboard
  ---------------------------
  Use arrow keys to move the turtle.
  ```

  

  

Now you can use the arrow keys of the keyboard to drive the turtle around. If you can not drive the turtle **select the terminal window of the turtle_teleop_key** to make sure that the keys that you type are recorded.

- ![turtle_key.png](http://wiki.ros.org/ROS/Tutorials/UnderstandingTopics?action=AttachFile&do=get&target=turtle_key.png)

Now that you can drive your turtle around, let's look at what's going on behind the scenes.

## ROS Topics

The `turtlesim_node` and the `turtle_teleop_key` node are communicating with each other over a ROS **Topic**. `turtle_teleop_key` is **publishing** the key strokes on a topic, while `turtlesim` **subscribes** to the same topic to receive the key strokes. Let's use [rqt_graph](http://wiki.ros.org/rqt_graph) which shows the nodes and topics currently running.

Note: If you're using `electric` or earlier, `rqt` is not available. Use `rxgraph` instead.

### Using rqt_graph

`rqt_graph` creates a dynamic graph of what's going on in the system. rqt_graph is part of the `rqt` package. Unless you already have it installed, run:

- 

  

  

  ```
  $ sudo apt-get install ros-<distro>-rqt
  $ sudo apt-get install ros-<distro>-rqt-common-plugins
  ```

  

replacing <distro> with the name of your [ROS distribution](http://wiki.ros.org/Distributions) (e.g. indigo, jade, kinetic, lunar ...)

**In a new terminal**:

```
$ rosrun rqt_graph rqt_graph
```

You will see something similar to:

![rqt_graph_turtle_key.png](http://wiki.ros.org/ROS/Tutorials/UnderstandingTopics?action=AttachFile&do=get&target=rqt_graph_turtle_key.png)

If you place your mouse over `/turtle1/command_velocity` it will highlight the ROS nodes (here blue and green) and topics (here red). As you can see, the `turtlesim_node` and the `turtle_teleop_key` nodes are communicating on the topic named `/turtle1/command_velocity`.

![rqt_graph_turtle_key2.png](http://wiki.ros.org/ROS/Tutorials/UnderstandingTopics?action=AttachFile&do=get&target=rqt_graph_turtle_key2.png)

### Introducing rostopic

The `rostopic` tool allows you to get information about ROS **topics**.

You can use the help option to get the available sub-commands for `rostopic`

```
$ rostopic -h
```

- 

  

  

  

  

  

  

  ```
  rostopic bw     display bandwidth used by topic
  rostopic echo   print messages to screen
  rostopic hz     display publishing rate of topic    
  rostopic list   print information about active topics
  rostopic pub    publish data to topic
  rostopic type   print topic type
  ```

  

  

Or pressing `tab` key after `rostopic` prints the possible sub-commands:

```
$ rostopic 
bw    echo  find  hz    info  list  pub   type 
```

Let's use some of these topic sub-commands to examine turtlesim.

### Using rostopic echo

`rostopic echo` shows the data published on a topic.

Usage:

```
rostopic echo [topic]
```

Let's look at the command velocity data published by the `turtle_teleop_key` node.

*For ROS Hydro and later,* this data is published on the `/turtle1/cmd_vel` topic. **In a new terminal, run:**

```
$ rostopic echo /turtle1/cmd_vel
```

*For ROS Groovy and earlier,* this data is published on the `/turtle1/command_velocity` topic. **In a new terminal, run:**

```
$ rostopic echo /turtle1/command_velocity
```

You probably won't see anything happen because no data is being published on the topic. Let's make `turtle_teleop_key` publish data by pressing the arrow keys. **Remember if the turtle isn't moving you need to select the turtle_teleop_key terminal again.**

*For ROS Hydro and later,* you should now see the following when you press the up key:

```
linear: 
  x: 2.0
  y: 0.0
  z: 0.0
angular: 
  x: 0.0
  y: 0.0
  z: 0.0
---
linear: 
  x: 2.0
  y: 0.0
  z: 0.0
angular: 
  x: 0.0
  y: 0.0
  z: 0.0
---
```

*For ROS Groovy and earlier,* you should now see the following when you press the up key:

```
---
linear: 2.0
angular: 0.0
---
linear: 2.0
angular: 0.0
---
linear: 2.0
angular: 0.0
---
linear: 2.0
angular: 0.0
---
linear: 2.0
angular: 0.0
```

Now let's look at `rqt_graph` again. Press the refresh button in the upper-left to show the new node. As you can see `rostopic echo`, shown here in red, is now also **subscribed** to the `turtle1/command_velocity` topic.

![rqt_graph_echo.png](http://wiki.ros.org/ROS/Tutorials/UnderstandingTopics?action=AttachFile&do=get&target=rqt_graph_echo.png)

 

### Using rostopic list

`rostopic list` returns a list of all topics currently subscribed to and published.

Let's figure out what argument the `list` sub-command needs. In a **new terminal** run:

```
$ rostopic list -h
```

```
Usage: rostopic list [/topic]

Options:
  -h, --help            show this help message and exit
  -b BAGFILE, --bag=BAGFILE
                        list topics in .bag file
  -v, --verbose         list full details about each topic
  -p                    list only publishers
  -s                    list only subscribers
```





For `rostopic list` use the **verbose** option:

```
$ rostopic list -v
```

This displays a verbose list of topics to publish to and subscribe to and their type.

*For ROS Hydro and later,*

- 

  

  

  

  

  

  

  

  

  

  

  ```
  Published topics:
   * /turtle1/color_sensor [turtlesim/Color] 1 publisher
   * /turtle1/cmd_vel [geometry_msgs/Twist] 1 publisher
   * /rosout [rosgraph_msgs/Log] 2 publishers
   * /rosout_agg [rosgraph_msgs/Log] 1 publisher
   * /turtle1/pose [turtlesim/Pose] 1 publisher
  
  Subscribed topics:
   * /turtle1/cmd_vel [geometry_msgs/Twist] 1 subscriber
   * /rosout [rosgraph_msgs/Log] 1 subscriber
  ```

  

*For ROS Groovy and earlier,*

- 

  

  

  

  

  

  

  

  

  

  

  

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

  

## ROS Messages

Communication on topics happens by sending ROS **messages** between nodes. For the publisher (`turtle_teleop_key`) and subscriber (`turtlesim_node`) to communicate, the publisher and subscriber must send and receive the same **type** of message. This means that a topic **type** is defined by the message **type** published on it. The **type** of the message sent on a topic can be determined using `rostopic type`.





