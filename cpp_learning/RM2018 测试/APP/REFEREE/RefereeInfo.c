/******************
裁判信息解读与透传数据帧封装程序
update: 2017.5.7
        视情况调用最后三个函数
        全局变量说明见RefereeInfo.h
        支持上传3个float数据
******************/
#include "RefereeInfo.h"

#include "laser.h"
#include "usart6.h"
u8 cmdID;  // 数据包ID
// 裁判信息相关结构体
extGameRobotState_t extGameRobotState;   // 比赛进程信息（0x0001）
extRobotHurt_t extRobotHurt;  // 伤害数据(0x0002)
extShootData_t extShootData;  // 实时射击信息(0x0003)
extPowerHeatData_t extPowerHeatData;//实时功率热量数据(0x0004)
tStudentPropInfo StudentPropInfo; // 赛场信息(0x0005)
extGameRobotPos_t extGameRobotPos;// 机器人位置和枪口朝向信息(0x0008)
extShowData_t extShowData;  // 学生上传自定义数据(0x0006)

const u8 sof=0xA5;  // 帧头
u8 custom_info_counter=0;  // 自定义数据包序号
u8 seq = 0;  // 发过来的包序号
u8 seq_real=0;

Bytes2Float bytes2float;  // flaot和字节互转
Bytes2U32 bytes2u32;  // flaot和u16互转

u8 referee_message[64];  // 完整数据帧存放, 理论44就够。
int message_byte_counter = 0;  // 字节存放位置计数
u8 blood_counter=0;  // (debug)被打计数


void init_referee_info() {
	extGameRobotPos.x = 0;
	extGameRobotPos.y = 0;
	extGameRobotPos.z = 0;
	extGameRobotPos.yaw = 0;
	extPowerHeatData.shooterHeat0 = 0;
	extPowerHeatData.shooterHeat1 = 0;
}

//crc8 生成多项式:G(x)=x8+x5+x4+1
const unsigned char CRC8_INIT2 = 0xff;
const unsigned char CRC8_TAB[256] = {
    0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83, 0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41,
    0x9d, 0xc3, 0x21, 0x7f, 0xfc, 0xa2, 0x40, 0x1e, 0x5f, 0x01, 0xe3, 0xbd, 0x3e, 0x60, 0x82, 0xdc,
    0x23, 0x7d, 0x9f, 0xc1, 0x42, 0x1c, 0xfe, 0xa0, 0xe1, 0xbf, 0x5d, 0x03, 0x80, 0xde, 0x3c, 0x62,
    0xbe, 0xe0, 0x02, 0x5c, 0xdf, 0x81, 0x63, 0x3d, 0x7c, 0x22, 0xc0, 0x9e, 0x1d, 0x43, 0xa1, 0xff,
    0x46, 0x18, 0xfa, 0xa4, 0x27, 0x79, 0x9b, 0xc5, 0x84, 0xda, 0x38, 0x66, 0xe5, 0xbb, 0x59, 0x07,
    0xdb, 0x85, 0x67, 0x39, 0xba, 0xe4, 0x06, 0x58, 0x19, 0x47, 0xa5, 0xfb, 0x78, 0x26, 0xc4, 0x9a,
    0x65, 0x3b, 0xd9, 0x87, 0x04, 0x5a, 0xb8, 0xe6, 0xa7, 0xf9, 0x1b, 0x45, 0xc6, 0x98, 0x7a, 0x24,
    0xf8, 0xa6, 0x44, 0x1a, 0x99, 0xc7, 0x25, 0x7b, 0x3a, 0x64, 0x86, 0xd8, 0x5b, 0x05, 0xe7, 0xb9,
    0x8c, 0xd2, 0x30, 0x6e, 0xed, 0xb3, 0x51, 0x0f, 0x4e, 0x10, 0xf2, 0xac, 0x2f, 0x71, 0x93, 0xcd,
    0x11, 0x4f, 0xad, 0xf3, 0x70, 0x2e, 0xcc, 0x92, 0xd3, 0x8d, 0x6f, 0x31, 0xb2, 0xec, 0x0e, 0x50,
    0xaf, 0xf1, 0x13, 0x4d, 0xce, 0x90, 0x72, 0x2c, 0x6d, 0x33, 0xd1, 0x8f, 0x0c, 0x52, 0xb0, 0xee,
    0x32, 0x6c, 0x8e, 0xd0, 0x53, 0x0d, 0xef, 0xb1, 0xf0, 0xae, 0x4c, 0x12, 0x91, 0xcf, 0x2d, 0x73,
    0xca, 0x94, 0x76, 0x28, 0xab, 0xf5, 0x17, 0x49, 0x08, 0x56, 0xb4, 0xea, 0x69, 0x37, 0xd5, 0x8b,
    0x57, 0x09, 0xeb, 0xb5, 0x36, 0x68, 0x8a, 0xd4, 0x95, 0xcb, 0x29, 0x77, 0xf4, 0xaa, 0x48, 0x16,
    0xe9, 0xb7, 0x55, 0x0b, 0x88, 0xd6, 0x34, 0x6a, 0x2b, 0x75, 0x97, 0xc9, 0x4a, 0x14, 0xf6, 0xa8,
    0x74, 0x2a, 0xc8, 0x96, 0x15, 0x4b, 0xa9, 0xf7, 0xb6, 0xe8, 0x0a, 0x54, 0xd7, 0x89, 0x6b, 0x35,
};


//crc16 生成多项式: 未知
uint16_t CRC_INIT = 0xffff;
const uint16_t wCRC_Table[256] = {
    0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
    0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
    0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
    0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
    0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
    0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
    0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
    0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
    0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
    0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
    0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
    0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
    0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
    0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
    0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
    0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
    0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
    0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
    0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
    0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
    0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
    0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
    0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
    0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
    0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
    0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
    0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
    0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
    0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
    0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
    0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
    0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};


/*
** Descriptions: CRC8 校验码生成
** Input: 信息数据, 信息数据长, CRC8_INIT2(0xff)
** Output: CRC8校验码
*/
unsigned char Get_CRC8_Check_Sum(unsigned char *pchMessage,unsigned int dwLength,unsigned char ucCRC8) {
    unsigned char ucIndex;
    while(dwLength--) {
        ucIndex = ucCRC8^(*pchMessage++);
        ucCRC8 = CRC8_TAB[ucIndex];
    }
    return(ucCRC8);
}


/*
** Descriptions: CRC8 校验程序
** Input: 需校验数据, 数据长度(= 信息长度 + 校验码长度)
** Output: True or False (CRC Verify Result)
*/
unsigned int Verify_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength) {
    unsigned char ucExpected = 0;
    if ((pchMessage == 0) || (dwLength <= 2)) 
        return false;
    ucExpected = Get_CRC8_Check_Sum (pchMessage, dwLength-1, CRC8_INIT2);
    return (ucExpected == pchMessage[dwLength-1]);  // 末位校验码判断
}


/*
** Descriptions: 增添 CRC8 至信息数据尾部
** Input: 信息数据(尾部需留空1位以加入校验码), 信息数据长度
** Output: 带校验码的数据
*/
void Append_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength) {
    unsigned char ucCRC = 0;
    if ((pchMessage == 0) || (dwLength <= 2))
        return;
    ucCRC = Get_CRC8_Check_Sum((unsigned char *)pchMessage, dwLength-1, CRC8_INIT2);  // 校验码生成
    pchMessage[dwLength-1] = ucCRC;  // 增添至尾部
}


/*
** Descriptions: CRC16 校验码生成
** Input: 信息数据, 信息数据长, CRC_INIT(0xffff)
** Output: CRC16校验码
*/
uint16_t Get_CRC16_Check_Sum(uint8_t *pchMessage,uint32_t dwLength,uint16_t wCRC)
{
    uint8_t chData;
    if (pchMessage == NULL) {
        return 0xFFFF;
    }
    while(dwLength--) {
        chData = *pchMessage++;
        (wCRC) = ((uint16_t)(wCRC) >> 8) ^ wCRC_Table[((uint16_t)(wCRC) ^ (uint16_t)(chData)) & 0x00ff];
    }
    return wCRC;
}


/*
** Descriptions: CRC16 校验程序
** Input: 需校验数据, 数据长度(= 信息长度 + 校验码长度, 即包含了校验码的长度)
** Output: True or False (CRC Verify Result)
*/
uint32_t Verify_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength) {
    uint16_t wExpected = 0;
    if ((pchMessage == NULL) || (dwLength <= 2)) {
        return false;
    }
    wExpected = Get_CRC16_Check_Sum ( pchMessage, dwLength - 2, CRC_INIT);
    return ((wExpected & 0xff) == pchMessage[dwLength - 2] && ((wExpected >> 8) & 0xff) == pchMessage[dwLength - 1]);
}


/*
** Descriptions: 增添 CRC16 至信息数据尾部
** Input: 信息数据(尾部需留空2位以加入校验码), 信息数据长度
** Output: 带校验码的数据
*/
void Append_CRC16_Check_Sum(uint8_t * pchMessage,uint32_t dwLength) {
    uint16_t wCRC = 0;
    if ((pchMessage == NULL) || (dwLength <= 2)) {
        return;
    }
    wCRC = Get_CRC16_Check_Sum ( (u8 *)pchMessage, dwLength-2, CRC_INIT );
    pchMessage[dwLength-2] = (u8)(wCRC & 0x00ff);
    pchMessage[dwLength-1] = (u8)((wCRC >> 8)& 0x00ff);
}


// 单字节数组转u16(2字节), 高低位反序
uint16_t _bytes2u16(uint8_t * chosen_Message) {
    uint32_t temp=0;
    // 长度为2，高低位逆序拼合
    temp = *chosen_Message;
    chosen_Message++;
    temp += (*chosen_Message<<8);
    return temp;
}


// 单字节数组转u32(4字节), 高低位未知
uint32_t _bytes4u32(uint8_t * chosen_Message) {
    bytes2u32.b[0] = chosen_Message[0];
    bytes2u32.b[1] = chosen_Message[1];
    bytes2u32.b[2] = chosen_Message[2];
    bytes2u32.b[3] = chosen_Message[3];
    return bytes2u32.u32_value;
}


// 单字节数组转float(4字节), 高低位正常
float _bytes2float(uint8_t * chosen_Message) {
    bytes2float.b[0] = chosen_Message[0];
    bytes2float.b[1] = chosen_Message[1];
    bytes2float.b[2] = chosen_Message[2];
    bytes2float.b[3] = chosen_Message[3];
    return bytes2float.f;
}


// float转4长度单字节数组
void float2bytes(float chosen_value, u8 * res_message) {
    int i;
    bytes2float.f = chosen_value;
    for(i=0;i<4;i++)
        res_message[i] = bytes2float.b[i];
}


// 比赛机器人状态（0x0001）, 发送频率为10Hz。
void extGameRobotState_interpret(uint8_t * extGameRobotState_Message) {
	  extGameRobotState.stageRemianTime = _bytes2u16(&extGameRobotState_Message[0]);
		extGameRobotState.gameProgress = extGameRobotState_Message[2];
		extGameRobotState.robotLevel = extGameRobotState_Message[3];
		extGameRobotState.remainHP = _bytes2u16(&extGameRobotState_Message[4]);
	  extGameRobotState.maxHP = _bytes2u16(&extGameRobotState_Message[6]);
}



 //伤害数据(0x0002)，受到伤害时发送
void extRobotHurt_interpret(uint8_t * extRobotHurt_Message) {
    uint8_t _temp;
    _temp = extRobotHurt_Message[0];
		extRobotHurt.armorType = _temp&0xff;  // 标识装甲ID(4bits)
    extRobotHurt.hurtType = (_temp>>4);  // 血量变化类型(4bits)
    blood_counter ++;  // 击打计数
    return;
}

int shoot_counter_referee=0;
 //实时射击信息(0x0003)
void extShootData_interpret(uint8_t * extShootData_Message) {
    extShootData.bulletType = extShootData_Message[0];  // 子弹类型
    extShootData.bulletFreq = extShootData_Message[1];  // 子弹射频（发/s）
    extShootData.bulletSpeed = _bytes2float(&extShootData_Message[2]);  // 子弹射速（m/s）
    shoot_counter_referee++;
	return;
}
	//实时功率热量数据(0x0004)
void extPowerHeatData_interpret(uint8_t * extPowerHeatData_Message) 
	
{
  extPowerHeatData.chassisVolt = _bytes2float(&extPowerHeatData_Message[0]);  // 底盘输出电压：V
	extPowerHeatData.chassisCurrent = _bytes2float(&extPowerHeatData_Message[4]);  // 底盘输出电流	:A
	extPowerHeatData.chassisPower = _bytes2float(&extPowerHeatData_Message[8]);  // 底盘输出功率:W
	extPowerHeatData.chassisPowerBuffer = _bytes2float(&extPowerHeatData_Message[12]);  // 底盘功率缓冲:W
	extPowerHeatData.shooterHeat0 = _bytes2u16(&extPowerHeatData_Message[16]);  //17mm枪口热量
	extPowerHeatData.shooterHeat1 = _bytes2u16(&extPowerHeatData_Message[18]);  //42mm枪口热量
	return;
}


// 机器人位置和枪口朝向信息(0x0008)
void extGameRobotPos_interpret(uint8_t * extGameRobotPos_Message) {
  extGameRobotPos.x = _bytes2float(&extGameRobotPos_Message[0]);  // x轴坐标，单位米
	extGameRobotPos.y = _bytes2float(&extGameRobotPos_Message[4]);  // y轴坐标，单位米
	extGameRobotPos.z = _bytes2float(&extGameRobotPos_Message[8]);  // z轴坐标，单位米
	extGameRobotPos.yaw = _bytes2float(&extGameRobotPos_Message[12]);  // yaw轴角度，单位°
	return;
}


void StudentPropInfo_interpret(uint8_t * RealShootData_Message) {
	uint8_t _temp;
	_temp = RealShootData_Message[0];
	StudentPropInfo.RobotColor = _temp;
	StudentPropInfo.RedBaseSta = (_temp>>2);
	StudentPropInfo.BlueBaseSta = (_temp>>4);
	StudentPropInfo.IslandLanding = (_temp>>6);
	
	_temp = RealShootData_Message[1];
	StudentPropInfo.RedAirPortSta = (_temp);
	StudentPropInfo.BlueAirPortSta = (_temp>>4);
	
	_temp = RealShootData_Message[2];
	StudentPropInfo.No1PillarSta = (_temp);
	StudentPropInfo.No2PillarSta = (_temp>>4);
	
	_temp = RealShootData_Message[3];
	StudentPropInfo.No3PillarSta = (_temp);
	StudentPropInfo.No4PillarSta = (_temp>>4);
	
	_temp = RealShootData_Message[4];
	StudentPropInfo.No5PillarSta = (_temp);
	StudentPropInfo.No6PillarSta = (_temp>>4);
	
	_temp = RealShootData_Message[5];
	StudentPropInfo.RedBulletBoxSta = (_temp);
	StudentPropInfo.BlueBulletBoxSta = (_temp>>4);
	
	StudentPropInfo.RedBulletBoxSta = _bytes2u16(&RealShootData_Message[6]);
	StudentPropInfo.BlueBulletBoxSta = _bytes2u16(&RealShootData_Message[8]);
	
	_temp = RealShootData_Message[10];
	StudentPropInfo.No0BigRuneSta = (_temp);
	StudentPropInfo.No1BigRuneSta = (_temp>>4);
	
	StudentPropInfo.AddDefendPrecent=RealShootData_Message[11];	
}

// 完整校验数据帧, CRC8和CRC16
u8 Verify_frame(uint8_t * frame) {
    int frame_length;
	if(frame[0]!= sof) return false;
    frame_length = _bytes2u16(&frame[1]) + 5 + 2 + 2;
    if(Verify_CRC8_Check_Sum(frame, 5) && Verify_CRC16_Check_Sum(frame, frame_length)) {
//		if(seq > frame[3]) {
//			return false;
//		}
//		else {
//			seq = frame[3];
//			return true;
//		}
		return true;
    }
    else {
        return false;
    }
}

u8 blink_time=0;
// 数字闪烁显示测试
void data_blink(void) {
	blink_time++;
	if(blink_time<60) {
//		blink_time=0;
		extShowData.data3=8;
		return;
	}
	if(blink_time<120) {
		extShowData.data3 = 8.8888888888888888f;
		return;
	}
	if(blink_time>120)  {
		blink_time=0;
		return;
	}
}

void update_from_dma(void) {
	int i;
	u8 USART6_dma_x2[2*USART6_dma_len];
	for(i=0;i<USART6_dma_len;i++) {
		USART6_dma_x2[i]=USART6_dma[i];
		USART6_dma_x2[i+USART6_dma_len]=USART6_dma[i];
	}
//		
	for(i=0;i<USART6_dma_len;i++) {
		frame_interpret(&USART6_dma_x2[i]);
		USART6_dma[i]=0;
	}
	return;
}

u8 blood_seq=0;
// 使用完整数据帧更新全部裁判信息相关结构体。(带校验)
u8 frame_interpret(uint8_t * frame) { 
    if(Verify_frame(frame) == true) {
		if(seq_real>frame[3]&&frame[3]-seq_real>100) {
			return false;
		}
        cmdID = _bytes2u16(&frame[5]);
		seq_real=frame[3];
        switch(cmdID) {
            case 1: extGameRobotState_interpret(&frame[7]);break;  // 比赛进程信息
            case 2: extRobotHurt_interpret(&frame[7]);break; // 伤害数据
            case 3: extShootData_interpret(&frame[7]);break;  // 实时射击数据
						case 4: extPowerHeatData_interpret(&frame[7]);break;  //实时功率热量数据
					  case 8: extGameRobotPos_interpret(&frame[7]);break;  //// 机器人位置和枪口朝向信息
			//case 5:StudentPropInfo_interpret(&frame[7]);break;  //赛场信息
            default: break;
        }
		return true;
    }
	else {
		return false;
	}
}

// 弃用
// 使用读入单字节来更新全部裁判信息相关结构体, 
// 即仅累积字节为一完整数据包时 才调用frame_interpret函数 来更新相关结构体。
void referee_info_update(uint8_t single_byte) {
    // 不是头帧，开始复制入referee_message[]
    if(single_byte != sof) {
        message_byte_counter++;  // 从1开始索引复制
        referee_message[message_byte_counter] = single_byte;
    }
    // 若是头帧
    if(single_byte == sof) {
        frame_interpret(referee_message);  // 使用完整数据帧更新全部裁判信息相关结构体。
        referee_message[0] = sof;
        message_byte_counter = 0; // 重置
    }
}


// 自定义数据帧, 封装入指针custom_frame，长度 = 5+2+13+2 = 22
// 调用前请确保全局变量extShowData结构体已更新值
void custom_frame_pack(uint8_t * custom_frame) {
    custom_frame[0] = sof;
    custom_frame[1] = 12;  // data length
    custom_frame[2] = 0x00;
    custom_frame[3] = custom_info_counter;  // seq包序号
    Append_CRC8_Check_Sum(custom_frame, 5);
    // cmdID
    custom_frame[5] = 0x05;
    custom_frame[6] = 0x00;
    // 自定义数据，每个4字节(float)
    float2bytes(extShowData.data1, &custom_frame[7]);
    float2bytes(extShowData.data2, &custom_frame[11]);
    float2bytes(extShowData.data3, &custom_frame[15]);
		extShowData.mask = custom_frame[19];
    Append_CRC16_Check_Sum(custom_frame, 22);
    // 计数器自增
    custom_info_counter++;
    return;
}

