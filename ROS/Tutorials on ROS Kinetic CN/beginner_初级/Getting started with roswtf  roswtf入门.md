## Getting started with roswtf | roswtf入门

> http://wiki.ros.org/cn/ROS/Tutorials/Getting%20started%20with%20roswtf
>
> http://wiki.ros.org/ROS/Tutorials/Getting%20started%20with%20roswtf
>
> 中文包过于老旧，输出.bag文件信息与以往不同了

### I 安装检查

[roswtf](http://wiki.ros.org/roswtf) 可以检查你的ROS系统并尝试发现问题，我们来试看：

```
$ roscd
$ roswtf
```

你应该会看到（各种详细的输出信息）：

```
Stack: ros
================================================================================
Static checks summary:

No errors or warnings
================================================================================

Cannot communicate with master, ignoring graph checks
```

如果你的ROS安装没问题，你应该会看到类似上面的输出信息，它的含义是： 

- "Stack: ros": [roswtf](http://wiki.ros.org/roswtf)根据你当前目录来确定需要做的检查，这里表示你是在`ros`stack中启动`roswtf`。 
- "Static checks summary": 这是有关文件系统问题的检查报告，现在的检查结果表示文件系统没问题。 
- "Cannot communicate with master, ignoring graph checks（无法与master连接，忽略图（graph）检查）": `roscore`没有运行，所以`roswtf`没有做运行时检查。

### II. 运行时检查（在有ROS节点运行时）

在这一步中，我们需要让[Master](http://wiki.ros.org/Master)运行起来，所以得先启动`roscore`。

现在按照相同的顺序再次运行以下命令：

```
$ roscd
$ roswtf
```

你应该会看到：

```
Stack: ros
================================================================================
Static checks summary:

No errors or warnings
================================================================================
Beginning tests of your ROS graph. These may take awhile...
analyzing graph...
... done analyzing graph
running graph rules...
... done running graph rules

Online checks summary:

Found 1 warning(s).
Warnings are things that may be just fine, but are sometimes at fault

WARNING The following node subscriptions are unconnected:
 * /rosout:
   * /rosout
```

既然`roscore`已经运行了所以`roswtf`做了一些运行时检查。检查过程的长短取决于正在运行的ROS节点数量，可能会花费很长时间才能完成。正如你看到的，这一次出现了警告：

```
WARNING The following node subscriptions are unconnected:
 * /rosout:
   * /rosout
```

`roswtf`发出警告说[rosout](http://wiki.ros.org/rosout)节点订阅了一个没有节点向其发布的话题。在本例中，这正是所期望看到的，因为除了`roscore`没有任何其它节点在运行，所以我们可以忽略这些警告。

### III. 错误报告

`roswtf`会对一些系统中看起来异常但可能是正常的运行情况发出警告。也会对确实有问题的情况报告错误。

接下来我们在`ROS_PACKAGE_PATH` 环境变量中设置一个 *bad*值，并退出`roscore`以简化检查输出信息。

```
$ roscd
$ ROS_PACKAGE_PATH=bad:$ROS_PACKAGE_PATH roswtf
```

这次我们会看到：

```
Stack: ros
================================================================================
Static checks summary:

Found 1 error(s).

ERROR Not all paths in ROS_PACKAGE_PATH [bad] point to an existing directory: 
 * bad

================================================================================

Cannot communicate with master, ignoring graph checks
```

正如你看到的，`roswtf`发现了一个有关`ROS_PACKAGE_PATH`设置的错误。

`roswtf`还可以发现很多其它类型的问题。如果你发现自己被一个编译或者通信之类的问题困扰的时候，可以尝试运行`roswtf`看能否帮你解决。