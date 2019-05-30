```
#打印调试信息
set(CMAKE_PREFIX_PATH "/usr/local/opencv2")
set(CMAKE_PREFIX_PATH "/usr/local")
MESSAGE(STATUS "Project: ${PROJECT_NAME}")
MESSAGE(STATUS "OpenCV library status:")
MESSAGE(STATUS "    version: ${OpenCV_VERSION}")
MESSAGE(STATUS "    libraries: ${OpenCV_LIBS}")
MESSAGE(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
```



### NeueUbuntu

---

仅限何宇杰自己的电脑

https://blog.csdn.net/qq_36982160/article/details/78393328 used for installation logo cut (edited)
division /boot 200M swap area 8g / 40960M /home rest

---

[Ubuntu下安装nvidia显卡驱动（安装方式简单）](https://blog.csdn.net/linhai1028/article/details/79445722) used for resolution error
[Ubuntu下安装cuda+cudnn](https://blog.csdn.net/linhai1028/article/details/79451648)
https://blog.csdn.net/zuanjue1207/article/details/80696823 cuda+matlab
after install download the ggfwzs
install Typora

---

#### [Chrome](https://github.com/FZUG/repo/wiki/%E5%AE%89%E8%A3%85-Chrome)

```
下载 google-chrome.list 并保存
$ wget https://repo.fdzh.org/chrome/google-chrome.list -P /etc/apt/sources.list.d/

sudo apt-get update

安装 Chrome
$ apt-get install google-chrome-{stable,beta,unstable}
```

#### qt5-ss

<https://github.com/shadowsocks/shadowsocks-qt5/wiki/安装指南>

如果您在使用Debian Wheezy或者任何比其更新的64位Linux发行版，下载Releases页面的AppImage文件，终端下`chmod a+x`或者用文件管理器给予可执行权限，以后即可随时双击运行。

```
wget https://github.com/shadowsocks/shadowsocks-qt5/releases/download/v3.0.1/Shadowsocks-Qt5-3.0.1-x86_64.AppImage
```

or download from last-release: https://github.com/shadowsocks/shadowsocks-qt5/releases

右键文件 –> 属性 –> 权限 –> 允许作为程序执行文件

wiki: [AppImage](https://zh.wikipedia.org/wiki/AppImage)

Configuration for SwitchOmega: https://www.switchyomega.com/settings/

---

#### Matlab

[ubuntu16.04安装MATLAB R2017b步骤详解（附完整破解文件包）](https://blog.csdn.net/qq_32892383/article/details/79670871) matlab installation

```
mkdir /home/v4rhyj/temp
sudo mount -t auto -o loop R2017b_glnxa64.iso /home/v4rhyj/temp
cd /home/v4rhyj/temp
sudo /home/v4rhyj/temp/install

sudo cp license_standalone.lic /usr/local/MATLAB/R2017b/licenses/ 
sudo cp libmwservices.so /usr/local/MATLAB/R2017b/bin/glnxa64/

sudo umount /home/v4rhyj/temp

cd /usr/local/MATLAB/R2017b/bin
./matlab

#set matlab evvironment 
export PATH=$PATH:/usr/local/matlab/bin

sudo apt-get install matlab-support
input /usr/local/
```

```
# error
/local/MATLAB/R2017b/bin/glnxa64/../../sys/os/glnxa64/libstdc++.so.6: version `GLIBCXX_3.4.21' not found (required by /usr/lib/x86_64-linux-gnu/libproxy.so.1)
Failed to load module: /usr/lib/x86_64-linux-gnu/gio/modules/libgiolibproxy.so

locate libstdc++.so.6

sudo ln -sf /usr/lib/x86_64-linux-gnu/libstdc++.so.6 /usr/local/MATLAB/R2017b/sys/os/glnxa64

```

https://blog.csdn.net/lnyy510/article/details/81628063

https://blog.csdn.net/weixin_28949825/article/details/79433925



---

#### CUDA

https://www.cnblogs.com/bovenson/p/5752213.html

[**Ubuntu下安装cuda+cudnn**](https://blog.csdn.net/linhai1028/article/details/79451648)

```
sudo apt-get install libprotobuf-dev libsnappy-dev  libhdf5-serial-dev protobuf-compiler
sudo apt-get install --no-install-recommends libboost-all-dev
sudo apt-get install libopenblas-dev liblapack-dev libatlas-base-dev
sudo apt-get install libgflags-dev libgoogle-glog-dev liblmdb-dev
sudo apt-get install git cmake build-essential
% error, update `geidt /etc/apt/sources.list`
sudo apt-get install libleveldb-dev libopencv-dev
sudo apt-get install freeglut3-dev build-essential libx11-dev libxmu-dev libxi-dev libgl1-mesa-glx libglu1-mesa libglu1-mesa-dev
```

    wget http://172.21.0.162/files/316000000002F31A/cdn.packages.deepin.com/deepin/pool/main/libx/libxext/libxext-dev_1.3.3-1_amd64.deb
    dpkg --force-depends -i libxext-dev_1.3.3-1_amd64.deb
    apt --fix-broken install

- nvidia cuda toolkit: https://developer.nvidia.com/cuda-80-ga2-download-archive

```
sudo dpkg -i cuda-repo-ubuntu1604-8-0-local-ga2_8.0.61-1_amd64.deb
sudo apt-get update
sudo apt-get install cuda
```

- environment setup

```
echo 'export PATH=/usr/local/cuda-8.0/bin:$PATH' >> ~/.bashrc
echo 'export LD_LIBRARY_PATH=/usr/local/cuda-8.0/lib64:$LD_LIBRARY_PATH' >> ~/.bashrc
source ~/.bashrc
```

- verify

```bash
cd /usr/local/cuda-8.0/samples/1_Utilities/deviceQuery
sudo make
./deviceQuery

cd ../bandwithTest
sudo make
./bandwithTest
```

#### Cudnn

https://blog.csdn.net/zuanjue1207/article/details/80696823

recommend cudnn_v5.1


original: update https://blog.csdn.net/u011557212/article/details/53233944

China source: https://www.linuxidc.com/Linux/2017-11/148627.htm

```
sudo chmod a+r /usr/local/cuda/include/cudnn.h /usr/local/cuda/lib64/libcudnn*
```

environment variable

```
export CUDA_HOME=/usr/local/cuda-8.0
export CUDAHOME=$CUDA_HOME
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda-8.0/cudnn-5/lib64:/usr/local/cuda-8.0/cudnn-6/lib64
```

#### Matconvnet

recommend - version24

download from official web, unpack and compile

a.解压下载的文件至任意你喜欢的位置

b.打开Matlab，切换目录到matconvnet/matlab下

#### gcc - 4.9

```
sudo apt-get install gcc-4.9 gcc-4.9-multilib g++-4.9 g++-4.9-multilib

sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 100
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 50

sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-5 50 
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.9 100
```

[Ubuntu下gcc多版本共存和版本切换](https://blog.csdn.net/ykr168age/article/details/61615212)

ubuntu's matlab support old-version gcc/g++, so we need to do sth.

```
mex -setup
mex -setup C++
sudo apt-get install build-essential libjpeg-turbo8-dev

    # cpu
    vl_compilenn()
    # for debugging
    vl_compilenn('verbose', 1)

    # gpu
    vl_compilenn('enableGpu',true,...
                 'cudaRoot','/usr/local/cuda-8.0',...
                 'cudaMethod','nvcc')
	# cudnn
	vl_compilenn('enableGpu', true, ...
               'cudaRoot', '/usr/local/cuda-8.0', ...
               'cudaMethod', 'nvcc', ...
               'enableCudnn', true, ...
               'cudnnRoot', '/usr/local/cuda-8.0/cudnn-6') ;
     
# TEST
	# cpu
	vl_setupnn
	gpuDevice
	vl_testnn
	# gpu
	vl_testnn('gpu',true)
	
```

test result 

```
# 启动时用到
LD_LIBRARY_PATH/usr/local/cuda-8.0/lib64 matlab


An unexpected error occurred during CUDA execution. The CUDA error was:
    all CUDA-capable devices are busy or unavailable
    
    --------
    错误 ID:
    --------
    'MATLAB:badsubscript'

    -----------
    错误详细信息:
    -----------
    索引超出矩阵维度。
    
找不到gpuDevice: 重启加上sudo
相关链接：https://www.one-tab.com/page/4sUssZnLR8mO6Tk6gh1WVw

--------------------------------------------------------

result = 

  1×3366 TestResult array with properties:

    Name
    Passed
    Failed
    Incomplete
    Duration
    Details

Totals:
   3366 Passed, 0 Failed, 0 Incomplete.
   589.7824 seconds testing time.
```

https://blog.csdn.net/anysky___/article/details/51356158



https://zhuanlan.zhihu.com/p/31976550

```
# some errors
`sudo apt-get install build-essential libjpeg-turbo8-dev` no worked

make ARCH=glnxa64 MATLABROOT=/usr/local/MATLAB/R2017b/ VERB=yes DEBUG=yes >> ~/Desktop/output-matconvnet.txt 
```

switch to 5.4



#### Opencv3.4

安装：https://blog.csdn.net/ksws0292756/article/details/79511170

关键还是看这个：https://github.com/kyamagu/mexopencv/wiki/Installation-%28Linux%2C-MATLAB%2C-OpenCV-3%29

```
mkdir /usr/local/opencv3.3

$ cmake -G "Unix Makefiles" \
    -DBUILD_DOCS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_PERF_TESTS=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_JAVA=OFF \
    -DWITH_CUDA=OFF \
    -DWITH_CUBLAS=OFF \
    -DWITH_CUFFT=OFF \
    -DWITH_NVCUVID=OFF \
    -DWITH_MATLAB=OFF \
    -DBUILD_opencv_cudaarithm=OFF \
    -DBUILD_opencv_cudabgsegm=OFF \
    -DBUILD_opencv_cudacodec=OFF \
    -DBUILD_opencv_cudafeatures2d=OFF \
    -DBUILD_opencv_cudafilters=OFF \
    -DBUILD_opencv_cudaimgproc=OFF \
    -DBUILD_opencv_cudalegacy=OFF \
    -DBUILD_opencv_cudaobjdetect=OFF \
    -DBUILD_opencv_cudaoptflow=OFF \
    -DBUILD_opencv_cudastereo=OFF \
    -DBUILD_opencv_cudawarping=OFF \
    -DBUILD_opencv_cudev=OFF \
    -DBUILD_opencv_java=OFF \
    -DBUILD_opencv_java_bindings_generator=OFF \
    -DBUILD_opencv_js=OFF \
    -DBUILD_opencv_python2=OFF \
    -DBUILD_opencv_python3=OFF \
    -DBUILD_opencv_python_bindings_generator=OFF \
    -DBUILD_opencv_ts=OFF \
    -DBUILD_opencv_world=OFF \
    -DBUILD_opencv_matlab=OFF \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/usr/local/opencv3.3 \
    -DOPENCV_ENABLE_NONFREE=ON \
    -DOPENCV_EXTRA_MODULES_PATH=~/Library/opencv/3.3.0/opencv_contrib-3.3.0/modules ~/Library/opencv/3.3.0/opencv-3.3.0
    
make -j4   # -j$(nproc)

sudo make install

$ sudo sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv3.conf'
# update cache
$ sudo ldconfig

# setup pkg-config search path
$ export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH
```

[源码编译opencv卡在IPPICV](https://blog.csdn.net/u010739369/article/details/79966263)

```
自己下载随便放，更改cmake
```

[查看安装位置版本](https://blog.csdn.net/zhenguo26/article/details/79627232)

```
pkg-config opencv --libs
pkg-config opencv --modversion
sudo find / -iname "*opencv*"
sudo find / -iname "*opencv*" > /home/ubuntu/Desktop/opencv_find.txt
```

- 2.4.13

白巧克力：https://blog.csdn.net/heyijia0327/article/details/54575245

[Ubuntu14.04下OpenCV3.4+contrib modules和OpenCV2.4.13的多版本共存](https://blog.csdn.net/poulang5786/article/details/79027444)

[ubuntu16同时安装opencv2.4和opencv3.3](https://blog.csdn.net/MD2017/article/details/81235066)

```
mkdir release
cd release
sudo mkdir /usr/local/opencv2

CMAKE_BUILD_TYPE=RELEASE -DWITH_FFMPEG=OFF -DWITH_TBB=ON -DBUILD_NEW_PYTHON_SUPPORT=ON -DWITH_V4L=ON -DINSTALL_C_EXAMPLES=ON -DINSTALL_PYTHON_EXAMPLES=ON -DBUILD_EXAMPLES=ON -DWITH_QT=ON -DWITH_OPENGL=ON -DBUILD_FAT_JAVA_LIB=ON -DINSTALL_TO_MANGLED_PATHS=ON -DINSTALL_CREATE_DISTRIB=ON -DINSTALL_TESTS=ON -DENABLE_FAST_MATH=ON -DWITH_IMAGEIO=ON -DBUILD_SHARED_LIBS=OFF -DWITH_GSTREAMER=ON -DWITH_CUDA=OFF -DWITH_OPENCL=OFF -DWITH_OPENCL_SVM=OFF -DWITH_OPENCLAMDFFT=OFF -DWITH_OPENCLAMDBLAS=OFF -DCMAKE_INSTALL_PREFIX=/usr/local/opencv2 ..

make -j4
make install

# 使用opencv2

sudo gedit ~/.bashrc 
在文件末尾加上

export PKG_CONFIG_PATH=/usr/local/opencv2/lib/pkgconfig 
export LD_LIBRARY_PATH=/usr/local/opencv2/lib

保存,source ~/.bashrc  

sudo ldconfig  生效

# 在自己程序里使用opencv2.4.13
#  在要使用opencv的项目的CMakeLists.txt里面添加一行 
# 在project(...)之前添加：
set(OpenCV_DIR "/usr/local/opencv2/share/OpenCV")

OK ...

切换回opencv3.3 把上面改成(不知道有没有简单的方法 不用每次设置的？)

export PKG_CONFIG_PATH=/usr/local/opencv3/lib/pkgconfig 
export LD_LIBRARY_PATH=/usr/local/opencv3/lib

#  No module named cv2

sudo apt-get install python-opencv
```



#### mexopencv

```
make MATLABDIR=/usr/local/MATLAB/R2017b WITH_CONTRIB=true all contrib

打开到对应文件夹后添加所有文件到路径
>> cv.getBuildInformation()

>> UnitTest('ContribModules',true)
```

#### Caffe

https://github.com/BVLC/caffe/wiki/Ubuntu-16.04-or-15.10-Installation-Guide



#### ROS

详见：http://wiki.ros.org/kinetic/Installation/Ubuntu

ros自带安装opencv3.1.0

#### Others

卸载libreOffice：

```
sudo apt-get remove libreoffice-common
sudo apt autoremove
```

