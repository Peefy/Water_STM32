#ifndef _SLAVECOM_H_
#define _SLAVECOM_H_

#include "include.h"

#define SLAVECOM_EN 1

/************SC œ‡πÿ**************/
#define Byte unsigned char

#define SC_CheckByte1 0xFF
#define SC_CheckByte2 0xEE

#define Recv_Data1 RemoteCtr.MotorDuty
#define Recv_Data2 RemoteCtr.ServoDuty

#define RemoteCheckByte1 0xFF
#define RemoteCheckByte2 0xAA
#define InstructionsCheckByte 0xFE
#define DataSetCheckByte 0xCB


#define CaliPoseByte   0x44
#define StopCMDByte    0x22
#define RunCMDByte     0x33
#define TimerGoByte    0x11
#define ResetByte      0x55
#define FlashWriteByte 0x66
#define FlashReadByte  0x77
#define MotorSpeedSetByte 0x88

#define DataSet_UpDataByte 0x11
#define DataSet_DownDataByte 0x22

void SC_DataDeal(void);
void Board_SendData(void);
void ComWithHC(void);


#endif
