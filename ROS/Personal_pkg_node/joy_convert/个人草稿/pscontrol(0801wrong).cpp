
/* FL.FR,RL,RR(前/后 左/右)
订阅自/joy主题
发布/serial_send_mailbox主题，超过20个舍弃

http://docs.ros.org/kinetic/api/sensor_msgs/html/msg/Joy.html
# Reports the state of a joysticks axes and buttons.
Header header           # timestamp in the header is the time the data is received from the joystick
float32[] axes          # the axes measurements from a joystick
int32[] buttons         # the buttons measurements from a joystick 
*/

/****************************************************************************/

//ros需要的头文件
#include "ros/ros.h"
#include <sensor_msgs/Joy.h>
#include <std_msgs/UInt8MultiArray.h>

//以下为串口通讯需要的头文件
#include <string>        
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <cmath>


ros::Publisher send_pub;

// 小车相关参数
float vc; //velocity of center 中心速度 (m/s)
float wc; //angle velocity of center 中心角速度 (rad/s)
//convert from motor to m_output
//speed_motor(rpm) / reduce_ratio = m_outpit(rpm)
float reduce_ratio; //减速比，电机内部参数
//convert from rpm to wheel_speed, wheel_ration = 2 * pi * D(m)] / 60(s/min)
// [m_outpit(rpm) * 2 * pi * D(m)] / 60(s/min) = wheel_speed(m/s)
float wheel_ration; //轮边系数，电机输出转速与轮速关系系数
float half_width; //half width between left and right wheel, 2c = width (m) 半宽度
float a; //length between CoG and rear wheel (m) 质心到后排轮子的距离
float b; //length between CoG and front wheel (m) 质心到前排轮子的距离

float vL, vR, vF, vB; //过渡速度，用于导出各轮速度 transition speed
float speed_motor[4]; //左前FL.右前FR.左后RL.右后RR各电机转速值
//具体数据待确定
half_width = 0.6 //(m)
a = 0.4; //(m)
b = 0.4; //(m)
reduce_ratio = 19.2；
wheel_ratio = 0.02;

//摇杆相关参数
int linear_, angular_;
double l_scale_, a_scale_;

linear_ = 1;
angular_ = 0;
l_scale_ = 0.3;
a_scale_ = 0.9;
/*后续赋值
    n.param("axis_linear", linear_, linear_);
    n.param("axis_angular", angular_, angular_);
    n.param("scale_angular", a_scale_, a_scale_);
    n.param("scale_linear", l_scale_, l_scale_);
*/

//其他参数
int i; //用于循环
int MAX_SPEED = 4000; //电机最高转速

void callback(const sensor_msgs::Joy::ConstPtr& msg){
    //读取摇杆进行解算
    vc = a_scale_*joy->axes[angular_];;
    wc = linear.x = l_scale_*joy->axes[linear_];

    //由v(L/R/F/B)过渡计算
    vL = vc - half_width * wc;
    vR = vc + half_width * wc;
    vF = b * wc;
    vB = -1 * a * wc;

    // 导出左前FL.右前FR.左后RL.右后RR对应速度
    //FL
    speed_motor[0] = sqrt(vF * vF + vL * vL) * reduce_ratio / wheel_ratio; // (rpm)
    //FR
    speed_motor[1] = sqrt(vF * vF + vR * vR) * reduce_ratio / wheel_ratio; // (rpm)
    //RL
    speed_motor[2] = sqrt(vB * vB + vL * vL) * reduce_ratio / wheel_ratio; // (rpm)
    //RR
    speed_motor[3] = sqrt(vB * vB + vR * vR) * reduce_ratio / wheel_ratio; // (rpm) 
    //to be continued

    //极值
    for(i = 0;i < 4;i++){
        if(speed_motor[i] >= MAX_SPEED) speed_motor = MAX_SPEED;
    }
}

//其他功能函数——处理电机转速以及串口
void process_send_data(uint8_t* send_buffer){
    float speed_motor[4]

    memcpy(speed_motor, rec_buffer, 4);
    memcpy(speed_motor+1, rec_buffer+4, 4);
    memcpy(speed_motor+2, rec_buffer+8, 4);
    memcpy(speed_motor+3, rec_buffer+12, 4);
    
   // ROS_INFO_STREAM("Motors are running now");
}

int main(int argc, char **argv)
{   
    vc = 0;
    wc = 0;
    ros::init(argc, argv, "pscontrol");//初始化节点
    ros::NodeHandle n;  //定义节点进程句柄
    n.param("axis_linear", linear_, linear_);
    n.param("axis_angular", angular_, angular_);
    n.param("scale_angular", a_scale_, a_scale_);
    n.param("scale_linear", l_scale_, l_scale_);

    //订阅自/joy主题
    ros::Subscriber sub = n.subscribe("joy", 20, callback); 
    //发布/serial_send_mailbox主题，超过20个舍弃
    ros::Publisher send_pub = n.advertise<std_msgs::UInt8MultiArray>("serial_send_mailbox", 20);       
    ros::Rate loop_rate(50); //50Hz

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