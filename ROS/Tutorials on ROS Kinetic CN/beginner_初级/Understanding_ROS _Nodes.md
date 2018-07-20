## Understanding ROS Nodes |理解ROS节点

### Prerequisites

For this tutorial we'll use a lighweight simulator, to install it run the following command:

```bash
$ sudo apt-get install ros-<distro>-ros-tutorials
$ sudo apt-get install ros-kinetic-ros-tutorials
```

Replace '<distro>' with the name of your ROS distribution (e.g. indigo, jade, kinetic)

### Quick Overview of Graph Concepts

- [Nodes](http://wiki.ros.org/Nodes): A node is an executable that uses ROS to communicate with other nodes.
- [Messages](http://wiki.ros.org/Messages): ROS data type used when subscribing or publishing to a topic.
- [Topics](http://wiki.ros.org/Topics): Nodes can *publish* messages to a topic as well as *subscribe* to a topic to receive messages.
- [Master](http://wiki.ros.org/Master): Name service for ROS (i.e. helps nodes find each other)
- [rosout](http://wiki.ros.org/rosout): ROS equivalent of stdout/stderr
- [roscore](http://wiki.ros.org/roscore): Master + rosout + parameter server (parameter server will be introduced later)

### Nodes

A node really isn't much more than an executable file within a ROS package. ROS nodes use a ROS client library to communicate with other nodes. Nodes can publish or subscribe to a Topic. Nodes can also provide or use a Service.

### Client Libraries

ROS client libraries allow nodes written in different programming languages to communicate:

- rospy = python client library
- roscpp = c++ client library

### roscore

`roscore` is the first thing you should run when using ROS.

Please run:

```
$ roscore
```

You will see something similar to:

If `roscore` does not initialize, you probably have a network configuration issue. See [Network Setup - Single Machine Configuration](http://www.ros.org/wiki/ROS/NetworkSetup#Single_machine_configuration)

If `roscore` does not initialize and sends a message about lack of permissions, probably the `~/.ros` folder is owned by `root`, change recursively the ownership of that folder with:

```
$ sudo chown -R <your_username> ~/.ros
```

### Using rosnode

Open up a **new terminal**, and let's use **rosnode** to see what running `roscore` did... Bare in mind to keep the previous terminal open either by opening a new tab or simply minimizing it.

**Note:** When opening a new terminal your environment is reset and your `~/.bashrc` file is sourced. If you have trouble running commands like `rosnode` then you might need to add some environment setup files to your `~/.bashrc` or manually re-source them.

`rosnode` displays information about the ROS nodes that are currently running. The `rosnode list` command lists these active nodes:

```
$ rosnode list
```

- You will see:

  ```
  /rosout
  ```

This showed us that there is only one node running: [rosout](http://wiki.ros.org/rosout). This is always running as it collects and logs nodes' debugging output.


The `rosnode info` command returns information about a specific node.

```
$ rosnode info /rosout
```

This gave us some more information about `rosout`, such as the fact that it publishes `/rosout_agg`.

Now, let's see some more nodes. For this, we're going to use `rosrun` to bring up another node.

### Using rosrun

`rosrun` allows you to use the package name to directly run a node within a package (without having to know the package path).

Usage:

```
$ rosrun [package_name] [node_name]
```

So now we can run the turtlesim_node in the turtlesim package.

Then, in a **new terminal**:

```
$ rosrun turtlesim turtlesim_node
```

You will see the turtlesim window:

- ![turtlesim.png](http://wiki.ros.org/ROS/Tutorials/UnderstandingNodes?action=AttachFile&do=get&target=turtlesim.png)

**NOTE:** The turtle may look different in your turtlesim window. Don't worry about it - there are [many types of turtle](http://wiki.ros.org/Distributions#Current_Distribution_Releases) and yours is a surprise!

In a **new terminal**:

```
$ rosnode list
```

You will see something similar to:

```
/rosout
/turtlesim
```

One powerful feature of ROS is that you can reassign Names from the command-line.

Close the turtlesim window to stop the node (or go back to the `rosrun turtlesim` terminal and use `ctrl-C`). Now let's re-run it, but this time use a [Remapping Argument](http://wiki.ros.org/Remapping%20Arguments) to change the node's name:

```
$ rosrun turtlesim turtlesim_node __name:=my_turtle
```

Now, if we go back and use `rosnode list`:

```
$ rosnode list
```

- You will see something similar to:

  ```
  /my_turtle
  /rosout
  ```



Note: If you still see /turtlesim in the list, it might mean that you stopped the node in the terminal using `ctrl-C` instead of closing the window, or that you don't have the $ROS_HOSTNAME environment variable defined as described in [Network Setup - Single Machine Configuration](http://www.ros.org/wiki/ROS/NetworkSetup#Single_machine_configuration). You can try cleaning the rosnode list with: $ rosnode cleanup

We see our new `/my_turtle` node. Let's use another `rosnode` command, `ping`, to test that it's up:

```
$ rosnode ping my_turtle

  rosnode: node is [/my_turtle]
  pinging /my_turtle with a timeout of 3.0s
  xmlrpc reply from http://aqy:42235/     time=1.152992ms
  xmlrpc reply from http://aqy:42235/     time=1.120090ms
  xmlrpc reply from http://aqy:42235/     time=1.700878ms
  xmlrpc reply from http://aqy:42235/     time=1.127958ms
```

### Review

What was covered:

| command   | makeup   | function                                                     |
| --------- | -------- | ------------------------------------------------------------ |
| `roscore` | ros+core | **master** (provides name service for ROS) + **rosout** (stdout/stderr) + **parameter server** (parameter server will be introduced later) |
| `rosnode` | ros+node | ROS tool to **get information** about a node.                |
| `rosrun`  | ros+run  | **runs a node** from a given package.enp0s31f6 Link encap:Ethernet  HWaddr d8:9e:f3:0e:06:e7 |