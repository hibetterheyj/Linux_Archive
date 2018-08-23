#ifndef _SHOOTCONTROL_H_
#define _SHOOTCONTROL_H_

/*
*********************************************************************************************************
*                                           PERIPH BUF SIZES 
*********************************************************************************************************
*/
#include "main.h"

#define PIDVAL_SHOOT_POS_p 0
#define PIDVAL_SHOOT_POS_i 0
#define PIDVAL_SHOOT_POS_d 0
#define PIDVAL_SHOOT_SPEED_p 2.5
#define PIDVAL_SHOOT_SPEED_i 2.5    
#define PIDVAL_SHOOT_SPEED_d 0

#define Shoot_UP 160      //Ħ���ֿ�  
#define Shoot_DOWN 100     //Ħ���ֹ�	

#define ShootInterval 12   //25
#define ShootTime 10     //���̵��ת��ʱ��   //23
#define ShootSpeedOffset 15000  //���̵��ת��    //4230

	
void ShootControlLoop(void);
void FrictionControl(void);
void FrictionJudge(void);
void ShootStop(void);
void GunControl(void);								//�����������
void GunShootAction(void);
void ShootControlMove(float SetPosition);      //�������
float ShootSpeedControl(float SetPosition,float NowPosition,PID_Struct* pid);
void ShootControlInit(void);
void ShootHeatControl(void);

extern float PIDOut_Speed_Shoot,PIDOut_Whole_Shoot;					//Pit,Yaw PID�����
extern float shoot_speed_set ;
#endif
