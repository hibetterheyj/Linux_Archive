/************************************************************
 *File		:	main.c
  *Author	:  @YangTianhao ,490999282@qq.com,@TangJiaxin ,tjx1024@126.com
 *Version	: V1.0
 *Update	: 2017.12.11
 *Description: 	
                RM2018_INFANTRY project. 
							
							- Control the Chassis motors , Gimbal motors , Shoot motor BY Remote controller.
							- Using CAN bus to connect all 7 motors(Yaw,pitch,motorA,motorB,motorC,motorD,ShootMotor) made by DJI.
							- Manage the power of chassis by electricity module.
							- Control the friction wheel motors by electronic governors.
								
				Instruction:
								
                            - Turn on the controller,and switch on the power,you will hear the buzzer ring a few,that means the mechine is initializing.						
							- When the buzzer is silent again,which means the mechine is ready to move,you have the permission to control it.
							- Channel 0 1 2 3 corresponds to Translation crosswise,Translation lengthways,Pitching and Rotate respectively.
							- Switching s1 from middle position to up position then switch back will turn on the friction wheels,and do that again will 
							  turn off them.When switch to down position,the gun shoots.
							- Three positions of s2 corresponds to Remote pattern,Key pattern and Standby pattern respectively from up to down.
                							
								
						                                                            
 					     ___	______                             		          ______    ___ 
					    ||_||  | __   |______                               _____|   __ |  ||_||
					     |_|___|______|------          *********            -----|______|___| |   
                        _|_|_  TongJi  _\_ _				                _ _/_  TongJi  _|_|_	
				       / \ / \___RM___/ \ / \                              / \ / \___RM___/ \ / \
				      ||- + -||      ||- + -||                            ||- + -||      ||- + -|| 
				       \_/_\_/	      \_/_\_/                              \_/_\_/	      \_/_\_/ 
					   
						 
        
  --- All rights reserved by TongJi RoboMaster Club(TJRM).
	
	School of Mechanical Engineering Tongji University,
	No.4800,CaoYang Road,JiaDing District,
	Shanghai City,P.R.China,201804
 ************************************************************/
 
#include "main.h" 

int main(void)
{  	
	BSP_Init();	
    while(1)
	  {	
			//test
//			printf("123");
//			printf("%s",USART_RX_BUF3);
		//	printf("yaw_set:%f\r\n",Gimbal_control.angle_yaw_set);
			
//			printf("view_ch2:%f    ",view_ch2);
//			printf("view_ch3:%f\r\n",view_ch3);
//			printf("current_position_205:%d    ",current_position_205);
//			printf("current_position_206:%d\r\n",current_position_206);
	  }
}
