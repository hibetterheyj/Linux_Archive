#include "main.h"

frame frame_ex;
frame fram;
int frame_count=0;
double parameter_yaw=2.0;
double parameter_pitch=1.0;
double view_ch2;
double view_ch3;
extern MotorPID_t	MotorPID_view; 
float temp;
void Auto_aim(u8 *rx_buf,int len)
{
	//GimbalPidInitPrepare();
//	PID_Init(&MotorPID_yaw.Position, 12, 0 , 0,-400,400,0);    //7.0 view 10 30 0.03
//	SetPIDCR(&MotorPID_yaw.Position,(1<<PEN)+(1<<IEN)+(1<<PIDEN)+(1<<INTERVAL)+(1<<DEN));
//	PID_Init(&MotorPID_yaw.Speed,	16.0,	3.0,	0,-60,60,0);    //13.55    //view 25 0 0
//	SetPIDCR(&MotorPID_yaw.Speed,(1<<PEN)+(1<<IEN)+(1<<DEN)+(1<<PIDEN)+(1<<INTERVAL));
	

	if(unpackFrame(rx_buf,len,&fram) == 0)//解包成功
	{	
		if(fram.timestamp != frame_ex.timestamp)//如果前一帧数据和当前帧时间戳一样,目标丢失,不作为
			{
				  view_ch2 = parameter_yaw*fram.yaw;//比例系数parameter_yaw待检验
				  view_ch3 = parameter_pitch*fram.pitch;//比例系数parameter_pitch待检验
          temp=PID_Driver(0, view_ch2, &MotorPID_view.View,200);
				  Gimbal_control.angle_yaw_set +=  view_ch2;
				  Gimbal_control.angle_pitch_set +=  view_ch3;
			}
			
			else
			{
				view_ch2 = 0;
				view_ch3 = 0;
			}
				frame_ex.timestamp = fram.timestamp;
		
	}
	else{                            //解包不成功,返回
		     view_ch2 = 0;
			 view_ch3 = 0;
		   return ;
	}
}
