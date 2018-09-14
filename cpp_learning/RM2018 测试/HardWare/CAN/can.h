#ifndef __CAN_H
#define __CAN_H	 
#include "stm32f4xx.h"
//#include "sys.h"    
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//CAN驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/7
//版本：V1.0 
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

u8 CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN初始化
 
void CAN1_Send_Bottom(int16_t candata1,int16_t candata2,int16_t candata3,int16_t candata4);
void CAN1_Cmd_SHOOT(int16_t current_207);
void CAN1_Cmd_standard(void);
void CAN1_Cmd_All(int16_t current_205,int16_t current_206,int16_t current_207);


volatile extern int16_t current_position_206;
volatile extern int16_t current_position_205;
volatile extern int16_t current_electricity_Yaw;
volatile extern int16_t current_cm_201;
volatile extern int16_t current_cm_202;
volatile extern int16_t current_cm_203;
volatile extern int16_t current_cm_204;
volatile extern int16_t current_shoot_pos_207;
volatile extern int16_t current_shoot_speed_207;


#endif

















