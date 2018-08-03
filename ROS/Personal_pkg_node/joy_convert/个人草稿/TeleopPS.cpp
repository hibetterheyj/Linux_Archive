
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

//HEAD
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

//VARIABLE
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

//CLASS
//class TeleopPS
{
    public:
    TeleopPS();

    private:
    void callback(const sensor_msgs::Joy::ConstPtr& joy);
    
    ros::NodeHandle n;//定义节点进程句柄

    int linear_, angular_;
    double l_scale_, a_scale_;
    int linear_x_axis, angular_z_axis;
    double linear_x_scale, angular_z_scale
    ros::Publisher send_pub;
    ros::Subscriber sub;
};

//INI
//参数初始化
TeleopPS::TeleopPS():
    //ps3转轴设置
    linear_(1), //设置速度控制为left-axis-upward，编号1
    angular_(3) //角度控制为right-axis-leftward.编号3
{
    n.param"linear_x_scale", linear_x_scale, 0.1); //scaling from integer 10 (1g in m/s/s); 0.1 -> 1m/s
    n.param("angular_z_scale", angular_z_scale, 0.2);

    n.param("linear_x_axis", linear_x_axis, -1);
    n.param("angular_z_axis", angular_z_axis, -1);

    send_pub = n.advertise<std_msgs::UInt8MultiArray>("serial_send_mailbox", 20); //发布/serial_send_mailbox主题，超过20个舍弃
    sub = n.subscribe("joy", 20, callback); //订阅自/joy主题
}

void TeleopPS::callback(const sensor_msgs::Joy::ConstPtr& joy)
{   
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
}

//FUNCTION
//其他功能函数
void process_send_data(uint8_t* send_buffer){
    float speed_motor[4]

    memcpy(speed_motor, rec_buffer, 4);
    memcpy(speed_motor+1, rec_buffer+4, 4);
    memcpy(speed_motor+2, rec_buffer+8, 4);
    memcpy(speed_motor+3, rec_buffer+12, 4);
    
    ROS_INFO_STREAM("Motors are running now") 
} 

//MAIN
//初始化节点并运行
int main(int argc, char** argv)
{   
    vc = 0;
    wc = 0;
    ros::init(argc, argv, "TeleopPS");
    TeleopPS TeleopPS;
    ros::Rate loop_rate(50); //50Hz

    while(ros::ok())
    {      
        //获取串口发送来的数据
        //数据与处理与判定
        vc = vc - 0.1;
        wc = wc - 0.1;

        if (vc < 0)
            vc = 0.5 * vc;//后退速度减半

        if (wc  < 0)
            wc = 0;

        ros::spinOnce();//周期执行
        loop_rate.sleep();//周期休眠
    }
    return 0;
}