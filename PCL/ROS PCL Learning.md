# ROS PCL Learning

> <http://wiki.ros.org/pcl/Overview>
>
> [pcl](http://wiki.ros.org/pcl)/[Tutorials](http://wiki.ros.org/action/fullsearch/pcl/Tutorials?action=fullsearch&context=180&value=linkto%3A%22pcl%2FTutorials%22)
>
> <https://blog.csdn.net/u013019296>

## I. Overview

### 1.1 Data types

- [sensor_msgs::PointCloud2](http://docs.ros.org/api/sensor_msgs/html/msg/PointCloud2.html)

  - The newly revised ROS point cloud message (and currently the *de facto* standard in **PCL**), now representing arbitrary n-D (n dimensional) data. Point values can now be of any primitive data types (int, float, double, etc), and the message can be specified as 'dense', with height and width values, giving the data a 2D structure, e.g. to correspond to an image of the same region in space. For more information on the rationale behind the new structure, see: [PCL_March_2010.pdf](http://www.ros.org/wiki/pcl?action=AttachFile&do=get&target=PCL_March_2010.pdf) and [pcl_icra2010.pdf](http://rbrusu.com/wp-content/uploads/2010/05/pcl_icra2010.pdf)

  ```cpp
  # The point cloud data may be organized 2d (image-like) or 1d
  # (unordered). Point clouds organized as 2d images may be produced by
  # camera depth sensors such as stereo or time-of-flight.
  
  # Time of sensor data acquisition, and the coordinate frame ID (for 3d
  # points).
  Header header
  
  # 2D structure of the point cloud. If the cloud is unordered, height is
  # 1 and width is the length of the point cloud.
  uint32 height
  uint32 width
  
  # Describes the channels and their layout in the binary data blob.
  PointField[] fields
  
  bool    is_bigendian # Is this data bigendian?
  uint32  point_step   # Length of a point in bytes
  uint32  row_step     # Length of a row in bytes
  uint8[] data         # Actual point data, size is (row_step*height)
  
  bool is_dense        # True if there are no invalid points
  ```
相关`PointField.msg`

```
# PointCloud2 message format.
uint8 INT8    = 1
uint8 UINT8   = 2
uint8 INT16   = 3
uint8 UINT16  = 4
uint8 INT32   = 5
uint8 UINT32  = 6
uint8 FLOAT32 = 7
uint8 FLOAT64 = 8

string name      # Name of field
uint32 offset    # Offset from start of point struct
uint8  datatype  # Datatype enumeration, see above
uint32 count     # How many elements in the field
```

- [pcl::PointCloud](http://docs.pointclouds.org/trunk/classpcl_1_1_point_cloud.html)

  - The core point cloud class in the PCL library; can be templated on any of the Point types listed in [point_types.h](http://docs.pointclouds.org/trunk/point__types_8h_source.html) or a user-defined type. This class has a similar structure to the PointCloud2 message type, including a header. Converting between the message class and the point cloud template class is straightforward (see below), and most methods in the PCL library accept objects of both types. Still, it's better to work with this template class in your point cloud processing node, rather than with the message object, among other reasons because you can work with the individual points as objects rather than having to work with their raw data.

### 1.2 Determining the point type for a given point cloud message

Each point cloud object type gives you information about the field names in a different way.

If you have a `sensor_msgs::PointCloud2` object, look at the elements of the fields() vector; each one has a `name` field and a `datatype` field. PCL has methods for extracting this information, see [io.h](http://docs.pointclouds.org/1.5.1/common_2include_2pcl_2common_2io_8h.html).

If you have a `pcl::PointCloud<T>` object, you probably already know what type the fields are because you know what T is. If it's a topic published by another node that you didn't write, you'll have to look at the source for that node. PCL has methods for extracting this information, see [io.h](http://docs.pointclouds.org/1.5.1/common_2include_2pcl_2common_2io_8h.html).

It has been suggested that it would be helpful if rostopic info could tell you what T is for a given [PointCloud2](http://wiki.ros.org/PointCloud2) topic, but this hasn't been implemented yet.

## II.Point Cloud conversion

### 2.1 Converting between `sensor_msgs::PointCloud2` and `pcl::PointCloud<T>` objects

Use [pcl::fromROSMsg](http://docs.ros.org/hydro/api/pcl_conversions/html/namespacepcl.html#af662c7d46db4cf6f7cfdc2aaf4439760) and [pcl::toROSMsg](http://docs.ros.org/hydro/api/pcl_conversions/html/namespacepcl.html#af2c39730f92ade1603c55d45265e386d) from [pcl_conversions](http://wiki.ros.org/pcl_conversions). The versions of these methods provided by PCL ([pcl::fromROSMsg](http://docs.pointclouds.org/1.5.1/namespacepcl.html#a2829cb35031f3c5ad0403de70f779915) and [pcl::toROSMsg](http://docs.pointclouds.org/1.5.1/namespacepcl.html#a7a849048e91cfc75f30ed30619a74d5d)) are deprecated. The point_cloud::fromMsg() and `point_cloud::toMsg()` methods are deprecated and will be removed in an imminent release. 

## III.Publishing and subscribing to point cloud messages

Note: Use of the old [PointCloud](http://wiki.ros.org/PointCloud) message type should be discontinued. Just for completeness, we'll summarize the subscription and publication operations for all three point cloud types below anyway.

### 3.1 Subscribing to different point cloud message types

### 3.2 Publishing different point cloud types	