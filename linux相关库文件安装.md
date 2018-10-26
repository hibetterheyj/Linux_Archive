# linux相关库文件安装

---

## g2o

https://github.com/RainerKuemmerle/g2o 



[双视图bundle adjustment案例](https://github.com/gaoxiang12/g2o_ba_example)

[深入理解图优化与g2o：g2o篇-半闲居士](https://www.cnblogs.com/gaoxiang12/p/5304272.html)

[在Ubuntu 16.04下安装g2o](https://blog.csdn.net/jz1570551401/article/details/78208605)

```
sudo apt-get install qtdeclarative5-dev qt5-qmake libqglviewer-dev libsuitesparse-dev
sudo apt-get install libcholmod(敲Tab键即可)

cd <usr_path>/g2o
mkdir build
cd build
cmake ..
make -j4
sudo make install
```

安装完成后在目录/usr/local/includ 下能找到g2o目录，在/usr/local/lib 下能找到libg2o_**.so的文件。



## opencv

### cv2



### cv3



## iSAM



## GTSAM



## PCL



`<TO BE CONTINUED>`