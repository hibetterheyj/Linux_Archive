## Defining Custom Messages自定义消息

### I. 自定义消息

自定义一个消息类型很简单，只要将.msg文件放到一个package的msg文件夹下即可。请参考[创建.msg 文件](http://wiki.ros.org/cn/ROS/Tutorials/CreatingMsgAndSrv#Creating_a_msg) (不要忘记选择相应的编译构建系统)。

### II. 引用和输出消息类型

消息类型都被归属到与package相对应的域名空间下，例如：

#### 2.1 C++

```
#include <std_msgs/String.h>
std_msgs::String msg;
```

#### 2.2 Python

```
from std_msgs.msg import String
msg = String()
```

### III. 依赖项

如果你要**使用在其他package里定义的消息类型**，不要忘记添加以下语句：

```
<build_depend>name_of_package_containing_custom_msg</build_depend>
<run_depend>name_of_package_containing_custom_msg</run_depend>
```

到 [package.xml](http://wiki.ros.org/catkin/package.xml)。

你需要把这个加到你的 CMakeList.txt:

```
add_dependencies(your_program ${catkin_EXPORTED_TARGETS})
```

如果您正在构建使用新消息的 c + + 节点，您还需要声明您的节点和消息之间的依赖关系，如 [catkin msg / srv buile doc](http://docs.ros.org/kinetic/api/catkin/html/howto/format2/cpp_msg_dependencies.html) 中所述。

 [ROSNodeTutorialPython](http://wiki.ros.org/ROSNodeTutorialPython) 教程展示了一个使用自定义消息的talker和listener的范例，其中使用了 c + + 和 Python 进行实现。