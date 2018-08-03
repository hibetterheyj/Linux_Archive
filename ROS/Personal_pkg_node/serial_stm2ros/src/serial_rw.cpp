//20180731 本节点用于接受、发布来自串口的数据，需要配合serial进行使用
//串口订阅读取信息,订阅主题自listener
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
//串口发布写入信息，发布主题自talker
//uint8_t TxData[8];
/****************************************************************************/
//ros需要的头文件
#include "ros/ros.h"
#include <std_msgs/UInt8MultiArray.h>

//以下为串口通讯需要的头文件
#include <string>        
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <cmath>
#include "serial/serial.h"

/****************************************************************************/
#define PWM_CONTROL true

#if PWM_CONTROL
    #define BUFFER_LENGTH (31)
#else
    #define BUFFER_LENGTH (59)
#endif

#define ERROR_OUT_THRESHOLD (500)
/****************************************************************************/

//各数据定义
int motor_position[4];
int motor_speed[4];
int motor_current[4];
char motor_temperature[4];
float theta, omiga, vx, vy, vz; 
int ax, ay, az;
//识别位
unsigned char data_terminal[3] = {0xA1, 0xA2, 0xA3};
//创建判定字符数组 data_ok[3]

/*****************************************************************************/
//创建串口接受对象
serial::Serial ros_ser;

//judge proto
inline uint32_t judgement(){
    uint8_t byte;
    uint32_t judge = 0;

    if (ros_ser.read(&byte, 1) && byte == data_terminal[1]){
        judge ++;
    }

    if (ros_ser.read(&byte, 1) && byte == data_terminal[2]){
        judge ++;
    }

    return (judge == 2);
}

//receive proto
uint32_t read_proto(uint8_t* buffer){
    uint32_t count = 0;
    uint8_t byte;

    while(count < ERROR_OUT_THRESHOLD){
        if (ros_ser.read(&byte, 1)){
            if (byte ==  data_terminal[0]){
                if (judgement()){
                    if (count == BUFFER_LENGTH - 3){
                        break;
                    }
                    count = 0;
                    continue;
                }
            }
            buffer[count] = byte;
            count ++;

        }else{
            ROS_ERROR_STREAM("Can not read byte");
        }
    }
    if (count == BUFFER_LENGTH - 3){
        return 1;
    }
    else{
        ROS_ERROR_STREAM("Can not receive satisfied data");
        return 0;
    }
} 

//回调函数
void callback(const std_msgs::UInt8MultiArray::ConstPtr& msg){
     uint32_t length = msg->layout.dim[0].size;
     if (length == 8){
        ROS_INFO_STREAM("Write to serial port");
        ros_ser.write(msg->data, length);
     }
 }

 //process received data
void process_received_data(uint8_t* rec_buffer){
    float yaw, wz, vx, vy, vz; 
    uint16_t ax, ay, az;

    memcpy(&yaw, rec_buffer, 4);
    memcpy(&wz, rec_buffer+4, 4);
    memcpy(&vx, rec_buffer+8, 4);
    memcpy(&vy, rec_buffer+12, 4);
    memcpy(&vz, rec_buffer+16, 4);

    memcpy(&ax, rec_buffer + 20, 2);
    memcpy(&ay, rec_buffer + 22, 2);
    memcpy(&az, rec_buffer + 24, 2);

    ROS_INFO_STREAM(std::setw(10) << "Yaw :" << yaw);
} 

//主函数
int main(int argc, char **argv)
{
    ros::init(argc, argv, "serial_rw");//初始化串口节点
    ros::NodeHandle n;  //定义节点进程句柄

    ros::Subscriber sub = n.subscribe("serial_send_mailbox", 20, callback); //订阅自/listener主题
    //定义要发布/talker主题，超过20个舍弃
    //ros::Publisher talker_pub= n.advertise<nav_msgs::Odometry>("talker", 20);       

    try
    {
        ros_ser.setPort("/dev/ttyACM0");//小车串口号
        ros_ser.setBaudrate(115200);//小车串口波特率
        serial::Timeout to = serial::Timeout::simpleTimeout(500);
        ros_ser.setTimeout(to);
        ros_ser.open();//配置串口
    }
    catch (serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port ");
        return -1;
    }
    if(ros_ser.isOpen()){
        ROS_INFO_STREAM("Serial Port opened");
    }
    else{
        return -1;
    }
    //循环周期是100Hz，设置周期休眠时间
    ros::Rate loop_rate(2000); //1100Hz

    uint8_t rec_buffer[BUFFER_LENGTH];
    while(ros::ok())
    {      
        //获取串口发送来的数据
        //数据与处理与判定
    
        if(read_proto(rec_buffer)) //串口接收的数据长度正确就处理
        {
            process_received_data(rec_buffer);
            //开始进行数据处理s
            ros::spinOnce();//周期执行
            loop_rate.sleep();//周期休眠
        }else{
            ROS_INFO_STREAM("Msg Receive Fail!");
        }
        //ros::spin();
        //ROS_INFO_STREAM("Serial Running...");
        //程序周期性调用
        //ros::spinOnce();  //callback函数必须处理所有问题时，才可以用到
    }
    return 0;
}