## ros amcl解读初步

Summarized by PhilHE on July 2018

### I. 概览

> 主要参照，详见[ROS wiki - amcl](http://wiki.ros.org/amcl)

#### 1.1 算法

amcl is a probabilistic localization system for a robot moving in 2D. It implements the adaptive (or KLD-sampling) Monte Carlo localization approach (as described by Dieter Fox), which uses a particle filter to track the pose of a robot against a known map.

Amcl 是一种二维移动机器人的概率定位系统。 它实现了**自适应(或 KLD-sampling)蒙特卡罗定位方法**，该方法使用一个粒子滤波器来跟踪一个机器人对着已知地图的姿势。

**蒙卡罗自适应算法：**

amcl takes in a **laser-based map, laser scans, and transform messages, and outputs pose estimates**. On startup, amcl initializes its particle filter according to the parameters provided. 

Note that, because of the defaults, if <u>no parameters are set, the initial filter state will be a moderately sized particle cloud centered about (0,0,0).</u> 

amcl使用激光地图，激光扫描，坐标变换信息，输出位姿估计。开始运行阶段，amcl根据所提供的参数，初始化它的粒子滤波器。 

请注意，由于缺省，如果没有设置参数，<u>最初的滤波器状态将是一个中等大小的粒子云，以(0,0,0)为中心</u>

#### 1.2 节点分析

- **Subscribed Topics | 订阅话题**

| 话题与消息                                            | 作用                                                         |
| ----------------------------------------------------- | ------------------------------------------------------------ |
| scan (sensor_msgs/LaserScan)                          | Laser scans. 激光扫描信息                                    |
| tf (tf/tfMessage)                                     | Transforms. 坐标变换信息                                     |
| initialpose (geometry_msgs/PoseWithCovarianceStamped) | **Mean and covariance** with which to (re-)initialize the particle filter. 用于(重新)初始化粒子滤波器的均值和协方差 |
| map (nav_msgs/OccupancyGrid)                          | When the use_map_topic parameter is set, AMCL subscribes to this topic to retrieve the map used for laser-based localization. New in navigation 1.4.2. |

对于最后一个。当`use_map_topic `参数已被设置，amcl订阅此主题，以检索用于激光定位的地图

- **Published Topics | 发布话题**

| 话题与消息                                          | 作用                                                         |
| --------------------------------------------------- | ------------------------------------------------------------ |
| amcl_pose (geometry_msgs/PoseWithCovarianceStamped) | Robot's estimated pose in the map, with covariance.在地图中带有协方差的估计位姿 |
| particlecloud (geometry_msgs/PoseArray)             | The set of pose estimates being maintained by the filter.点云数据，该组位姿由滤波器估计得出 |
| tf (tf/tfMessage)                                   | Publishes the transform from odom (which can be remapped via the ~odom_frame_id parameter) to map.发布从位置里程计到地图中间的位姿变换 |

- **Services | 服务**

| 服务                                     | 作用                                                         |
| ---------------------------------------- | ------------------------------------------------------------ |
| global_localization (std_srvs/Empty)     | Initiate global localization, wherein all particles are dispersed randomly through the free space in the map.初始化全局坐标。 其中所有粒子在地图中的自由空间中随机分布 |
| request_nomotion_update (std_srvs/Empty) | Service to manually perform update and publish updated particles.用于手动更新与发布更新点（云）的服务 |

- **Services Called | 调用服务**

`static_map 静态地图 (nav_msgs/GetMap 导航 / GetMap)`

amcl calls this service to retrieve the map that is used for laser-based localization; startup blocks on getting the map from this service. amcl 调用这个服务来检索用于激光定位的地图; 启动模块从服务中获得地图

- Parameters | 参数

There are three categories of ROS Parameters that can be used to configure the amcl node: overall filter, laser model, and odometery model.

有三类ROS参数可用于配置 amcl 节点: 整体滤波器、激光模型和 odometery 模型。

- 整体滤波器变量

> 对于点云、位姿、地图、数据发布等进行配置

**关键参数：**

`to be continued`

- 激光模型变量

> Note that whichever mixture weights are in use should sum to 1. The beam model uses all 4: z_hit, z_short, z_max, and z_rand. The likelihood_field model uses only 2: z_hit and z_rand.

**关键参数：**

`to be continued`

- odometery（里程计）模型参数

If ~odom_model_type is "diff" then we use the sample_motion_model_odometry algorithm from Probabilistic Robotics, p136; this model uses the noise parameters odom_alpha_1 through odom_alpha4, as defined in the book.

If ~odom_model_type is "omni" then we use a custom model for an omni-directional base, which uses odom_alpha_1 through odom_alpha_5. The meaning of the first four parameters is similar to that for the "diff" model. The fifth parameter capture the tendency of the robot to translate (without rotating) perpendicular to the observed direction of travel.

A bug was found and fixed. But fixing the old models would have changed or broken the localisation of already tuned robot systems, so the new fixed odometry models were added as new types "diff-corrected" and "omni-corrected". The default settings of the odom_alpha parameters only fit the old models, for the new model these values probably need to be a lot smaller, see http://answers.ros.org/question/227811/tuning-amcls-diff-corrected-and-omni-corrected-odom-models/.

**关键参数：**

`to be continued`

#### 1.3 TF变换 | Transferoms（待分析）

`amcl` transforms incoming laser scans to the odometry frame (`~odom_frame_id`). So there must exist a path through the [tf](http://wiki.ros.org/tf)tree from the frame in which the laser scans are published to the odometry frame.

An implementation detail: on receipt of the first laser scan, `amcl` looks up the transform between the laser's frame and the base frame (~base_frame_id), and latches it forever. So `amcl` cannot handle a laser that moves with respect to the base.

The drawing below shows the difference between localization using odometry and `amcl`. During operation `amcl` estimates the transformation of the base frame (~base_frame_id) in respect to the global frame (`~global_frame_id`) but it only publishes the transform between the global frame and the odometry frame (`~odom_frame_id`). Essentially, this transform accounts for the drift that occurs using Dead Reckoning. The published transforms are [future dated](http://wiki.ros.org/tf/FAQ#Why_do_I_see_negative_average_delay_in_tf_monitor.3F).

![amcl_localization.png](http://wiki.ros.org/amcl?action=AttachFile&do=get&target=amcl_localization.png)



### II. 代码分析





### III. 使用方法





### 参考资料

#### github repo

> A 2D navigation stack that takes in information from odometry, sensor streams, and a goal pose and outputs safe velocity commands that are sent to a mobile base.

- AMD64 Debian Job Status: [![Build Status](https://camo.githubusercontent.com/f305979d8f2300388a4cc1708873d434dfda02c1/687474703a2f2f6275696c642e726f732e6f72672f6275696c645374617475732f69636f6e3f6a6f623d4c62696e5f755836345f5f6e617669676174696f6e5f5f7562756e74755f78656e69616c5f616d6436345f5f62696e617279)](http://build.ros.org/job/Lbin_uX64__navigation__ubuntu_xenial_amd64__binary)

Related stacks:

- <http://github.com/ros-planning/navigation_msgs> (new in Jade+)
- <http://github.com/ros-planning/navigation_tutorials>
- <http://github.com/ros-planning/navigation_experimental>

For discussion, please check out the <https://groups.google.com/group/ros-sig-navigation> mailing list.

#### 英语书籍

- Thrun S. Probabilistic robotics[M]// **Probabilistic robotics** /. MIT Press, 2006:52-57.
- Fernandez E, Crespo L S, Mahtani A, et al. **Learning ROS for Robotics Programming** - Second Edition[M]. Packt Publishing, 2013. P357

#### 网上链接

我的**[amcl解读 - One Tab Share Page](https://www.one-tab.com/page/gx-tqU0HTJqq-ZIPJg-Gsw)**，包含了以下内容：

- [机器人定位（amcl）与导航 - CSDN博客](https://blog.csdn.net/shuimiaofeng/article/details/73186693)
- [navigation stack 中amcl 源码解读 - CSDN博客](http://chrome-extension//klbibkeccnjlkjkiokjodocebajanakg/suspended.html#ttl=navigation%20stack%20%E4%B8%ADamcl%20%E6%BA%90%E7%A0%81%E8%A7%A3%E8%AF%BB%20-%20CSDN%E5%8D%9A%E5%AE%A2&uri=https://blog.csdn.net/xyz599/article/details/52942485)
- [ROS探索总结（十五）——amcl（导航与定位） - 古月居](http://www.guyuehome.com/273)
- [ROS导航之参数配置和自适应蒙特卡罗定位 - jason来自星星 - 博客园](http://chrome-extension//klbibkeccnjlkjkiokjodocebajanakg/suspended.html#ttl=ROS%E5%AF%BC%E8%88%AA%E4%B9%8B%E5%8F%82%E6%95%B0%E9%85%8D%E7%BD%AE%E5%92%8C%E8%87%AA%E9%80%82%E5%BA%94%E8%92%99%E7%89%B9%E5%8D%A1%E7%BD%97%E5%AE%9A%E4%BD%8D%20-%20jason%E6%9D%A5%E8%87%AA%E6%98%9F%E6%98%9F%20-%20%E5%8D%9A%E5%AE%A2%E5%9B%AD&uri=https://www.cnblogs.com/zjiaxing/p/5559382.html)
- [amcl - 古月居](http://www.guyuehome.com/tag/amcl)
- [amcl - ROS Wiki](http://wiki.ros.org/amcl)
- [ros的navigation之———amcl（localization）应用详解 - CSDN博客](https://blog.csdn.net/chenxingwangzi/article/details/50038413)
- [ros-planning/navigation: ROS Navigation stack. Code for finding where the robot is and how it can get somewhere else.](https://github.com/ros-planning/navigation)

