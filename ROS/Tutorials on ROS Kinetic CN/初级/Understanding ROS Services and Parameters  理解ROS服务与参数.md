## Understanding ROS Services and Parameters | 理解ROS服务与参数

### Using rosservice

#### rosservice list

`list` 命令显示turtlesim节点提供了9个服务：`重置（reset）`, `清除（clear）`, `再生（spawn）`, `终止（kill）`, `turtle1/set_pen`, `/turtle1/teleport_absolute`, `/turtle1/teleport_relative`, `turtlesim/get_loggers`, and `turtlesim/set_logger_level`. 同时还有另外两个`rosout`节点提供的服务: `/rosout/get_loggers` and `/rosout/set_logger_level`.

```
/clear
/kill
```

#### rosservice type

使用方法:

```
rosservice type [service]
```

我们来看看clear服务的类型:

```
$ rosservice type clear
std_srvs/Empty
```

#### rosservice call





### Using rosparam

rosparam使得我们能够**存储并操作ROS 参数服务器（Parameter Server）上的数据**。参数服务器能够存储整型、浮点、布尔、字符串、字典和列表等数据类型。rosparam使用YAML标记语言的语法。一般而言，YAML的表述很自然：1 是整型, 1.0 是浮点型, one是字符串, true是布尔, [1, 2, 3]是整型列表, {a: b, c: d}是字典. rosparam有很多指令可以用来操作参数，如下所示:

使用方法:

```
rosparam set            设置参数
rosparam get            获取参数
rosparam load           从文件读取参数
rosparam dump           向文件中写入参数
rosparam delete         删除参数
rosparam list           列出参数名
```

我们来看看现在参数服务器上都有哪些参数：

#### rosparam list

```
$ rosparam list
```

我们可以看到turtlesim节点在参数服务器上有3个参数用于设定背景颜色：

```
/background_b
/background_g
/background_r
/roslaunch/uris/aqy:51932
/run_id
```

Let's change one of the parameter values using `rosparam set`:

#### rosparam set & rosparam get

Usage:

```
rosparam set [param_name]
rosparam get [param_name]
```

现在我们修改背景颜色的红色通道：

```
$ rosparam set background_r 150
```

上述指令修改了参数的值，现在我们调用清除服务使得修改后的参数生效：

```
$ rosservice call clear
```



我们可以使用`rosparam get /`来显示参数服务器上的所有内容：

```
$ rosparam get /
```

反馈：

```
background_b: 255
background_g: 86
background_r: 150
```