//ros头文件
#include "ros/ros.h"
//joy节点
#include <sensor_msgs/Joy.h>
//串口通讯头文件
#include <std_msgs/UInt8MultiArray.h>
#include <std_msgs/MultiArrayLayout.h>
//其他头文件
#include <string>        
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <cmath>
#include <cstring>

ros::Publisher send_pub;

// !小车相关参数
//speed_motor(rpm) / reduce_ratio = m_outpit(rpm)
float reduce_ratio = 19.2; //减速比，电机内部参数
//convert from rpm to wheel_speed, wheel_ration = 2 * pi * D(m)] / 60(s/min)
// [m_outpit(rpm) * 2 * pi * D(m)] / 60(s/min) = wheel_speed(m/s)
float wheel_ratio = 0.0225; //轮边系数，电机输出转速与轮速关系系数
float half_width = 0.6; //(m)half width between left and right wheel, 2c = width (m) 半宽度
float a = 0.4; //(m) length between CoG and rear wheel (m) 质心到后排轮子的距离
float b = 0.4; //(m) length between CoG and front wheel (m) 质心到前排轮子的距离
int MAX_SPEED = 4000; //电机最高转速

struct center
{
    float v; //velocity of center 中心（加）速度 
    float w; //angle velocity of center 中心角（加）速度 
}ctr_vel,ctr_accl;

float vL, vR; //左右排纵向速度
float rpm[2]; //左右排电机转速，先左后右
short int rpm_conv[2]; //电机转速导出值

int linear_ = 1;
int angular_ = 2; //joy对应摇杆3,ps3joy对应摇杆2
double l_scale_ = 2.0; //0.8
double a_scale_ = 1.0; //摇杆比例 1.0

//控制参数
float trap_width = 0.02; //1.0对应0.02
float v_downrate = 0.95; //速度衰减
float w_downrate = 0.75; //速度衰减

//占空比与电机转速转换
int rpm_convert(float rpm)
{
    float y1; //负极限占空比
    float y2; //静止对应占空比下限
    float y3; //静止对应占空比上限
    float y4; //正极限占空比
    float k1, k2; //斜率
    y1 = 1000.0;
    y2 = 1480.0;
    y3 = 1520.0;
    y4 = 2000.0;
    float rpm_conv;
    if(rpm > 0) {
        rpm_conv = (y4 - y3) * rpm/MAX_SPEED + y3;
    }
    else if(rpm < 0) {
        rpm_conv = (y2 - y1) * rpm/MAX_SPEED + y2;
    }
    else rpm_conv = (y2 + y3)/2;

    return static_cast<short int>(rpm_conv);
}

void callback(const sensor_msgs::Joy::ConstPtr& msg)
{
    //读取摇杆进行解算
    ctr_accl.v = l_scale_*msg->axes[linear_];
    ctr_accl.w = a_scale_*msg->axes[angular_];
}


int main(int argc, char **argv)
{   
    center ctr_vel = {0.0,0.0};

    // !控制相关参数
    float dt = 0.02;//更新频率50Hz对应的时间

    ros::init(argc, argv, "pscontrol");//初始化节点
    ros::NodeHandle n;  //定义节点进程句柄

    n.param("axis_linear", linear_, linear_);
    n.param("axis_angular", angular_, angular_);
    n.param("scale_angular", a_scale_, a_scale_);
    n.param("scale_linear", l_scale_, l_scale_);

    //订阅自/joy主题
    ros::Subscriber sub = n.subscribe("joy", 2, callback); 
    //发布/serial_send_mailbox主题，超过20个舍弃
    ros::Publisher send_pub = n.advertise<std_msgs::UInt8MultiArray>("serial_send_mailbox", 2);       
    ros::Rate loop_rate(10); //执行频率为50Hz

    while(ros::ok())
    {      
        //std_msgs格式
        std_msgs::MultiArrayLayout msg;
        std_msgs::UInt8MultiArray v;
        const unsigned int data_sz = 8;
        v.layout.dim.push_back(std_msgs::MultiArrayDimension());
        v.layout.dim[0].size = data_sz;
        v.layout.dim[0].stride = 1; 
        v.layout.dim[0].label = "dutycycle_char"; 
        v.data.resize(data_sz);
        //向串口发送来的数据        
        //其他功能函数——处理电机转速以及串口FL,FR,RL,RR
        //数据转换 from short int to vector

        //速度控制（保证空摇杆自动回０）
        if(ctr_accl.v == 0)
        {
            ctr_vel.v = 0;
            // ctr_vel.v = ctr_vel.v * v_downrate;
            // // 进入置0陷阱
            // if (std::abs(ctr_vel.v) < trap_width)
            //     ctr_vel.v = 0;
        }
        else
        {
            ctr_vel.v += ctr_accl.v * dt;
        }
        //角速度控制（保证空摇杆自动回０）
        if(ctr_accl.w == 0)
        {
            ctr_vel.w = 0;
            // ctr_vel.w = ctr_vel.w * w_downrate;
        }
        else
        {
            // ctr_vel.w = ctr_accl.w * dt;
            ctr_vel.w = ctr_accl.w * 0.7853 / 2; // o.7853 = pi / 8
        }
        //中心速度输出
        std::cout<<"1.中心角速度："<<ctr_vel.w<<std::endl;
        std::cout<<"2.中心速度："<<ctr_vel.v<<std::endl;

        //轮速转换，得出v(L/R)
        vL = ctr_vel.v - half_width * ctr_vel.w;
        vR = ctr_vel.v + half_width * ctr_vel.w;
        //std::cout<<"3.左速度："<<vL<<std::endl;
        //std::cout<<"4.当前右速度："<<vR<<std::endl;
        rpm[0] = vL * reduce_ratio / wheel_ratio; // (rpm)
        rpm[1] = vR * reduce_ratio / wheel_ratio; // (rpm)
        //电机转速rpm输出
        std::cout<<"3.左RPM："<<rpm[0]<<std::endl;
        std::cout<<"4.右RPM："<<rpm[1]<<std::endl;

        //极值与判定
        for(int i = 0;i < 2;i++)
        {
            if(abs(rpm[i]) >= MAX_SPEED) 
            {
                if(rpm[i] > 0) 
                    rpm[i] = MAX_SPEED;
                else 
                    rpm[i] = - MAX_SPEED;
                //ROS_INFO_STREAM("Reach Maximum Speed!");
            }
            rpm_conv[i] = rpm_convert(rpm[i]);
        }
        //占空比与对应转速输出
        std::cout<<"3.左占空比："<<std::dec<<rpm_conv[0]<< " : "<< std::dec<< (int)rpm[0]<< std::endl;
        std::cout<<"4.右占空比："<<std::dec<<rpm_conv[1]<< " : " << std::dec<< (int)rpm[1] << std::endl;

        //数据转换由rpm_conv转化为vector
        std::vector<unsigned char> output 
            = {
               ((unsigned char*) rpm_conv)[0],
               ((unsigned char*) rpm_conv)[1],
               ((unsigned char*) rpm_conv)[2],
               ((unsigned char*) rpm_conv)[3],
               ((unsigned char*) rpm_conv)[0],
               ((unsigned char*) rpm_conv)[1],
               ((unsigned char*) rpm_conv)[2],
               ((unsigned char*) rpm_conv)[3]
            };
        v.data = output;
        // std::cout<<"5.字符数组："<<std::endl;
        // std::cout<<std::hex<<(int)v.data[0]<<","<<std::hex<<(int)v.data[1]<<std::endl;
        // std::cout<<std::hex<<(int)v.data[2]<<","<<std::hex<<(int)v.data[3]<<std::endl;
        // std::cout<<std::hex<<(int)v.data[4]<<","<<std::hex<<(int)v.data[5]<<std::endl;
        // std::cout<<std::hex<<(int)v.data[6]<<","<<std::hex<<(int)v.data[7]<<std::endl;
        send_pub.publish(v);
        ros::spinOnce();//周期执行
        loop_rate.sleep();//周期休眠
        //ros::spin();
        //ROS_INFO_STREAM("Serial Running...");
        //程序周期性调用
        //ros::spinOnce();  //callback函数必须处理所有问题时，才可以用到
    }
    return 0;
}