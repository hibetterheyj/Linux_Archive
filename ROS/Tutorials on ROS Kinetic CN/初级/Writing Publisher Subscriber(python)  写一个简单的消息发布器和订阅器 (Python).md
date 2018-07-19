## Writing Publisher Subscriber(python) | 写一个简单的消息发布器和订阅器 (Python)

### Writing the Publisher Node

```python
# make sure script is executed as a Python script.
#!/usr/bin/env python

# the first import for python in ROS
import rospy
# reuse the std_msgs/String message type
# (a simple string container) for publishing.
from std_msgs.msg import String

def talker():
    pub = rospy.Publisher('chatter', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        hello_str = "hello world %s" % rospy.get_time()
        rospy.loginfo(hello_str)
        pub.publish(hello_str)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
```

