#include "include.h"

const u8 AngleDataHead = 0xaa;
const u8 AngleDataTail = 0x55;

AngleType Yaw,Roll,Pitch;

void AutoAngle(void)
{
		#ifdef POSE_EN
		Pose_UARTSendbyte(0xa5);
    Pose_UARTSendbyte(0x51); 
		#endif
}

int32 RecieveByte = 0;
void PoseGet(void)
{ 	  
	  Byte Rec;	
		#ifdef POSE_EN
	  static uint8 index = 0,Rebuf[8] = {0};
    Rec = USART_ReceiveData(USART1);	
    Rebuf[index++] = Rec;
    if(!(Rebuf[0] == AngleDataHead))
		{
				index = 0;
				Rebuf[0] = 0;
		}
		if(index >= 8)
		{
				if(Rebuf[7] == AngleDataTail)
				{
						Yaw.InitData = (Rebuf[1]<<8|Rebuf[2]) ;
						Roll.InitData = (Rebuf[3]<<8|Rebuf[4]) ;
						Pitch.InitData = (Rebuf[5]<<8|Rebuf[6]);
					  Yaw.ShowData = Yaw.InitData - Yaw.Offset;
						Roll.ShowData = Roll.InitData - Roll.Offset;
						Pitch.ShowData = Pitch.InitData - Pitch.Offset;
				}
		index = 0;
		}
    #else
		Rec = USART_ReceiveData(USART1);	
		#endif
}

void CaliPose(void)
{
	  Yaw.Offset = Yaw.InitData;
		Roll.Offset = Roll.InitData;
		Pitch.Offset = Pitch.InitData;
    ok_fmq();	
}

void CaliPoseButNotYaw(void)
{
	  //Yaw.Offset = Yaw.InitData;
		Roll.Offset = Roll.InitData;
		Pitch.Offset = Pitch.InitData;
    ok_fmq();	
}
