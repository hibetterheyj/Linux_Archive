[TOC]

# PCL tutorials Learning

> http://pointclouds.org/documentation/tutorials/
>
> http://www.pointclouds.org/documentation/advanced/pcl_style_guide.php

## Basic Usage

### [PCL Walkthrough](http://pointclouds.org/documentation/tutorials/walkthrough.php)

- [Common](http://pointclouds.org/documentation/tutorials/walkthrough.php#common)

The common library contains the common data structures and methods used by the majority of PCL libraries. The core data structures include the PointCloud class and a multitude of point types that are used to represent points, surface normals, RGB color values, feature descriptors, etc. It also contains numerous functions for computing distances/norms, means and covariances, angular conversions, geometric transformations, and more.

- Segmentation

The segmentation library contains algorithms for segmenting a point cloud into distinct clusters. These algorithms are best suited for processing a point cloud that is composed of a number of spatially isolated regions. In such cases, clustering is often used to break the cloud down into its constituent parts, which can then be processed independently.

A theoretical primer explaining how clustering methods work can be found in the cluster extraction tutorial. The two figures illustrate the results of plane model segmentation (left) and cylinder model segmentation (right).

tutorial: http://pointclouds.org/documentation/tutorials/#segmentation-tutorial

- Search

### [Getting Started / Basic Structures](http://pointclouds.org/documentation/tutorials/basic_structures.php)

- unorganized point cloud/ organized point cloud
- cloud.width/ cloud.height (int)
- cloud.points (std::vector<PointT>)

Contains the data array where all the points of type **PointT** are stored. For example, for a cloud containing XYZ data, **points** contains a vector of *pcl::PointXYZ* elements:

```c++
pcl::PointCloud<pcl::PointXYZ> cloud;
std::vector<pcl::PointXYZ> data = cloud.points;
```

- is_dense (bool)

all the data in points is finite (true) or XYZ values of certain points might contain Inf/NaN values(false)

- sensor_origin (Eigen::Vector4f)

optional

- sensor_orientation (Eigen::Quaternionf)
- isOrganized()

To simplify development, the [:pcl:`PointCloud`](http://pointclouds.org/documentation/tutorials/basic_structures.php#id15) class contains a number of helper member functions. For example, users don’t have to check if **height** equals 1 or not in their code in order to see if a dataset is organized or not, but instead use [:pcl:`PointCloud`](http://pointclouds.org/documentation/tutorials/basic_structures.php#id17):

```
if (!cloud.isOrganized ())
  ...
```

### [Using PCL in your own project](http://pointclouds.org/documentation/tutorials/using_pcl_pcl_config.php)

### [Writing a new PCL class](http://pointclouds.org/documentation/tutorials/writing_new_classes.php)

- Example: a bilateral filter

    - an I/O component: lines 21-27 (reading data from disk), and 64 (writing data to disk)
    - an initialization component: lines 29-35 (setting up a search method for nearest neighbors using a KdTree)
    - the actual algorithmic component: lines 7-11 and 37-61

The presented code snippet contains upper:

```c++
 #include <pcl/point_types.h>
 #include <pcl/io/pcd_io.h>
 #include <pcl/kdtree/kdtree_flann.h>

 typedef pcl::PointXYZI PointT;

 float
 G (float x, float sigma)
 {
     // exp()指数
     return exp (- (x*x)/(2*sigma*sigma));
 }

 int
 main (int argc, char *argv[])
 {
   std::string incloudfile = argv[1];
   std::string outcloudfile = argv[2];
   // atof()字符串变为浮点数组
   float sigma_s = atof (argv[3]);
   float sigma_r = atof (argv[4]);

   // Load cloud
   pcl::PointCloud<PointT>::Ptr cloud (new pcl::PointCloud<PointT>);
   // c_str() 一个将string转换为 const* char的函数。
   pcl::io::loadPCDFile (incloudfile.c_str (), *cloud);
   int pnumber = (int)cloud->size ();

   // Output Cloud = Input Cloud
   pcl::PointCloud<PointT> outcloud = *cloud;

   // Set up KDTree
   pcl::KdTreeFLANN<PointT>::Ptr tree (new pcl::KdTreeFLANN<PointT>);
   tree->setInputCloud (cloud);

   // Neighbors containers
   //std::vector https://www.codesdope.com/cpp-stdvector/
   std::vector<int> k_indices;
   std::vector<float> k_distances;

   // Main Loop
   for (int point_id = 0; point_id < pnumber; ++point_id)
   {
     float BF = 0;
     float W = 0;

     tree->radiusSearch (point_id, 2 * sigma_s, k_indices, k_distances);

     // For each neighbor
     for (size_t n_id = 0; n_id < k_indices.size (); ++n_id)
     {
       // vector.at()与数组类型相同，只不过会检查是否越界
       float id = k_indices.at (n_id);
       float dist = sqrt (k_distances.at (n_id));
       float intensity_dist = abs (cloud->points[point_id].intensity - cloud->points[id].intensity);

       float w_a = G (dist, sigma_s);
       float w_b = G (intensity_dist, sigma_r);
       float weight = w_a * w_b;

       BF += weight * cloud->points[id].intensity;
       W += weight;
     }

     outcloud.points[point_id].intensity = BF / W;
   }

   // Save filtered output
   pcl::io::savePCDFile (outcloudfile.c_str (), outcloud);
   return (0);
 }
```

