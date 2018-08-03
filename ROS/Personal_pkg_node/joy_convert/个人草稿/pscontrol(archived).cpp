// 串口订阅读取信息,订阅主题自listener
/* 以下为读取信息 FL.FR,RL,RR(前/后 左/右)
57字节
motor_position[4] int
motor_speed[4] int
motor_current[4] int 
motor_temperature[4] char
theta/omiga/vx/vy/vz float
ax/ay/az int
flag:3bytees 用于校正
*/
// 串口发布写入信息，发布主题自talker
// uint8_t TxData[8];
/****************************************************************************/

/*
http://docs.ros.org/kinetic/api/sensor_msgs/html/msg/Joy.html
# Reports the state of a joysticks axes and buttons.
Header header           # timestamp in the header is the time the data is received from the joystick
float32[] axes          # the axes measurements from a joystick
int32[] buttons         # the buttons measurements from a joystick 
*/


//ros需要的头文件
#include "ros/ros.h"
#include <sensor_msgs/Joy.h>
#include <std_msgs/UInt8MultiArray.h>

//以下为串口通讯需要的头文件
#include <string>        
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <math.h>

#define ZERO_DUTY (1455)
)
ros::Publisher send_pub;
float vc; // velocity of centor
float wc; // angle velocity of centor

void callback(const sensor_msgs::Joy::ConstPtr& msg){
    //实现将手柄转化为四轮分别的输出
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "pscontrol");//初始化节点
    ros::NodeHandle n;  //定义节点进程句柄

    ros::Subscriber sub = n.subscribe("joy", 20, callback); //订阅自/listener主题
    //定义要发布/talker主题，超过20个舍弃
    ros::Publisher send_pub = n.advertise<std_msgs::UInt8MultiArray>("serial_send_mailbox", 20);       
    ros::Rate loop_rate(50); //50Hz

    float vc = 0;

    while(ros::ok())
    {      
        //获取串口发送来的数据
        // 数据与处理与判定
        vc = vc - 0.1;
        wc = wc - 0.1;

        if (vc < 0)
            vc = 0;

        if (wc  < 0)
            wc = 0;

        ros::spinOnce();//周期执行
        loop_rate.sleep();//周期休眠
        //ros::spin();
        //ROS_INFO_STREAM("Serial Running...");
        //程序周期性调用
        //ros::spinOnce();  //callback函数必须处理所有问题时，才可以用到
    }
    return 0;
}
