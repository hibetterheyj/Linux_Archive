## Managing System dependencies | 管理系统依赖项

> http://wiki.ros.org/ROS/Tutorials/rosdep
>
> http://wiki.ros.org/cn/ROS/Tutorials/rosdep

### I. 系统依赖项 System Dependencies

ROS packages有时会需要操作系统提供一些外部函数库，这些函数库就是所谓的“系统依赖项”。在一些情况下，这些依赖项并没有被系统默认安装，因此，ROS提供了一个工具`rosdep`来下载并安装所需系统依赖项。

ROS packages必须在配置文件中声明他们需要哪些系统依赖项。下面我们来看看turtlesim package的配置文件：

```
$ roscd turtlesim
```

然后，输入下述命令：

```
$ cat package.xml
```

```
<package>

...
...
  <build_depend>message_generation</build_depend>
  <build_depend>libqt4-dev</build_depend>
  <build_depend>qt4-qmake</build_depend>
  <build_depend>rosconsole</build_depend>
  <build_depend>roscpp</build_depend>
  <build_depend>roscpp_serialization</build_depend>
  <build_depend>roslib</build_depend>
  <build_depend>rostime</build_depend>
  <build_depend>std_msgs</build_depend>
  <build_depend>std_srvs</build_depend>
</package>
```

#### 1.1 rosdep

`rosdep` 是一个能够下载并安装ROS packages所需要的系统依赖项的小工具 使用方法:

```
rosdep install [package]
```

为turtlesim下载并安装系统依赖项:

```
$ rosdep install turtlesim
```

如果是按照教程的顺序学习，那么这很可能是你第一次使用`rosdep`工具，因此，当执行这条指令，你会看到如下的报错消息：

```
ERROR: your rosdep installation has not been initialized yet.  Please run:
        
    sudo rosdep init
    rosdep update
```

按照提示执行上边两条指令，并再次安装turtlesim的系统依赖项。

如果你安装的是二进制文件，那么会看到如下信息：

```
All required rosdeps installed successfully
```

#### 1.2 rosdistro/rosdep

While [rosdep](http://wiki.ros.org/ROS/Tutorials/rosdep#rosdep) is the client tool, the reference is provided by rosdep rules, stored online in [ros/rosdistro/rosdep on github](https://github.com/ros/rosdistro/tree/master/rosdep).

When doing

```
$ rosdep update
```

rosdep actually retrieves the rules from the rosdistro github repository.

These rules are used when a dependency is listed that doesn't match the name of a ROS package built on the buildfarm. Then rosdep checks if there exists a rule to resolve it for the proper platform and package manager you are using.

当列出不符合在 buildfarm 上构建的 ROS 包名称的依赖项时，使用这些规则。 然后 rosdep 检查是否有一个规则来解决它，以便适当的平台和包管理器您使用。

When creating a new package, you might need to declare new system dependencies to the [rosdep rules](https://github.com/ros/rosdistro/tree/master/rosdep) if there are not there yet. Just edit the file, add the dependency needed (following a strict alphabetical order and a similar structure as the other dependencies already registered) and send a pull request.

创建一个新的包时，如果还没有新的系统依赖于 rosdep 的规则，你可能需要声明新的系统依赖。 只需编辑文件，添加所需的依赖项(遵循严格的字母顺序和与已注册的其他依赖项相似的结构) ，并发送一个pull request。

After that pull request has been merged, you need to run :

```
$ rosdep update
```

and now that dependency will be resolved by rosdep.

You can test it with :

可以用以下方法测试:

```
$ rosdep resolve my_dependency_name
```

输出应该与下文类似

```
#apt
my-dependency-name
```

where the first line is the package manager chosen for installing this dependency, and the second line is the actual name for that dependency on your current platform.

第一行是安装这个依赖项的包管理器，第二行是依赖于当前平台的实际名称。