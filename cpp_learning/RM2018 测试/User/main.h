#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f4xx.h"
#include "led.h"

#include "math.h"
#include "adc.h"
#include "delay.h"
#include "ControlTask.h"
#include "sys.h"
#include "bsp.h"
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include "buzzer.h"
#include "MonitorControl.h"
#include "mpu6500.h"
#include "spi.h"
#include "iic.h"
#include "euler.h"
#include "usart6.h"	
#include "usart3.h"
#include "rc.h"
#include "frame.h"
#include "define.h"
#include "can.h"
#include "laser.h"
#include "pid.h"
#include "CMControl.h"
#include "RemoteControl.h"
#include "GimbalControl.h"
#include "Auto_aim.h"
#include "ShootControl.h"
#include "mpu6050_interrupt.h"
#include "mpu6050_driver.h"
#include "mpu6050_i2c.h"
#include "mpu6050_process.h"
#include "RefereeInfo.h"

//Õ”¬›“« ¡„∆Ø ˝æ›
#define GYRO_X_OFFSET 0.00750f  //1∫≈∞Â¡„∆Æ0.07500f
#define GYRO_Y_OFFSET 0.005012f
#define GYRO_Z_OFFSET -0.022880f


/************≤‚ ‘”√************/
//#define MIDDLE_YAW 	7465
//#define MIDDLE_PITCH  4060

/*************0∫≈≥µ************/
//#define MIDDLE_YAW 	3365
//#define MIDDLE_PITCH  6480

/*************1∫≈≥µ************/
//#define MIDDLE_YAW 	3220
//#define MIDDLE_PITCH  6250


/*************2∫≈≥µ************/
//#define MIDDLE_YAW 	5500
//#define MIDDLE_PITCH  8044

/*************3∫≈≥µ************/
#define MIDDLE_YAW 	2700
#define MIDDLE_PITCH  7577

//#define ROLL_BORDER			//÷˜øÿ∞Â ˙∑≈
#define PITCH_BORDER			//÷˜øÿ∞Â∫·∑≈

	
#endif
