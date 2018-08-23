#ifndef _GIMBALCONTROL_H_
#define _GIMBALCONTROL_H_

#include "main.h"

/*
*********************************************************************************************************
*                                         PID参数设置
*********************************************************************************************************
*/


#define PIDVAL_YAW_POS_p_Prepare				12.0
#define PIDVAL_YAW_POS_i_Prepare				10.0
#define PIDVAL_YAW_POS_d_Prepare				0.0
#define PIDVAL_YAW_SPEED_p_Prepare			16.0
#define PIDVAL_YAW_SPEED_i_Prepare			3.0
#define PIDVAL_YAW_SPEED_d_Prepare			0.0


#define PIDVAL_PITCH_POS_p_Prepare			5.5
#define PIDVAL_PITCH_POS_i_Prepare			2
#define PIDVAL_PITCH_POS_d_Prepare			0.0
#define PIDVAL_PITCH_SPEED_p_Prepare		14.0
#define PIDVAL_PITCH_SPEED_i_Prepare		2.0
#define PIDVAL_PITCH_SPEED_d_Prepare		0.0


#define PIDVAL_YAW_POS_p				50.0
#define PIDVAL_YAW_POS_i				20.0
#define PIDVAL_YAW_POS_d				10.0
#define PIDVAL_YAW_SPEED_p			45.0
#define PIDVAL_YAW_SPEED_i			2.0
#define PIDVAL_YAW_SPEED_d			0


#define PIDVAL_PITCH_POS_p			28.0
#define PIDVAL_PITCH_POS_i			10
#define PIDVAL_PITCH_POS_d			1.3
//#define PIDVAL_PITCH_SPEED_p		20.0
#define PIDVAL_PITCH_SPEED_p		10.0  //测试用
#define PIDVAL_PITCH_SPEED_i		2.0
#define PIDVAL_PITCH_SPEED_d		0.0

#define PIDVAL_VIEW_p		1.0  //测试用
#define PIDVAL_VIEW_i		0.1
#define PIDVAL_VIEW_d		0.05


typedef struct 
{
	PID_Struct Position;
	PID_Struct Speed;
	PID_Struct View;
}MotorPID_t;

extern MotorPID_t	MotorPID_pitch;	
extern MotorPID_t	MotorPID_yaw;
extern float PIDOut_Position_Pit,PIDOut_Speed_Pit,PIDOut_Whole_Pit;					//Pit,Yaw PID总输出
extern float PIDOut_Position_Yaw,PIDOut_Speed_Yaw,PIDOut_Whole_Yaw;
extern int16_t position_yaw_relative ,current_position_pitch;

/**********************************************************************************************************
																					云台电机参数
**********************************************************************************************************/

#define YawMax 1000 			
#define YawMin -1000					
#define PitMax 30	
#define PitMin -30 		



typedef struct 
{
	float angle_yaw_set;
	float angle_yaw_current;
	float angle_pitch_set;
	float angle_pitch_current;
}Gimbal_Control_t;

extern Gimbal_Control_t Gimbal_control;
float MotorCurrentLegalize(float MotorCurrent , float limit);
void GimbalControlInit(void);
void GimbalControlLoop(void);
void GimbalMove(void);
void GimbalStop(void);
void GimbalControlValSet(void);
void GimbalPidInit(void);
void GimbalPidInitPrepare(void);
void GimbalControl_Yaw(float SetPosition);
void GimbalControl_YawAngel(float SetPosition);
void GimbalControl_PitchAngel(float SetPosition);
void GimbalControl_Pitch(float SetPosition);
float MotorPositionLegalize(float PositionPara , float MAX , float MIN);
int16_t GimbalValLigal(int raw_gimbal_data,int middle_data);
void ViewModeChange(uint16_t keyboardvalue);
void HandShoot(uint16_t keyboardvalue);



#endif
