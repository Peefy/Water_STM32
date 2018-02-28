#include "include.h"

//To ensure that the host computer sends more slowly than Microcontroller

#define CtrInfo_ByteCount 7
#define CtrCMD_ByteCount 2
#define DataSet_ByteCount 6

void SC_DataDeal(void)
{
   static Byte Temp;
	 while(IsEmpty(Queue_Byte) == false)
	 {
			if(DeQueue(Queue_Byte,&Temp) != -1)
			{
					if(Temp == RemoteCheckByte1 && GetCount(Queue_Byte) >= (CtrInfo_ByteCount - 1))
					{     
						   if(GetInQueue(Queue_Byte) == RemoteCheckByte2)
							 {
								  RemoteCtr.EN = GetInQueue(Queue_Byte);
									Recv_Data1 = GetInQueue(Queue_Byte) * 256 + GetInQueue(Queue_Byte);
									Recv_Data2 = GetInQueue(Queue_Byte) * 256 + GetInQueue(Queue_Byte);	
							 }								 
					}
					else if(Temp == InstructionsCheckByte && GetCount(Queue_Byte) >= (CtrCMD_ByteCount - 1))
					{
               				switch(GetInQueue(Queue_Byte))
						   {
								 case CaliPoseByte:CaliPose();break;
								 case StopCMDByte:Stop();break;
								 case RunCMDByte:Run();break;
								 case TimerGoByte:TimerRun_HC();break;
								 case ResetByte:IWDG_Reset();break;
								 case FlashWriteByte:Writeflash();break;
								 case FlashReadByte:Read();break;
								 case MotorSpeedSetByte:SpeedFromHC();break;
								 default:break;
               				}
					}
					else if(Temp == DataSetCheckByte && GetCount(Queue_Byte) >= (DataSet_ByteCount- 1))
					{
						   switch(GetInQueue(Queue_Byte))
						   {
								 case DataSet_UpDataByte:;break;
								 case DataSet_DownDataByte:ServoPDChangeFromHC();break;
								 default:break;
               				}
					}
				}
	 }
	 RemoteCtrDataDeal();
}

void SC_UARTSendbyte(u8 ch)
{
	 while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);	
	
   USART_SendData(USART2, (uint8_t) ch);
}

void SC_UARTSendWord(u16 ch)
{
   SC_UARTSendbyte((Byte)ch);
	 SC_UARTSendbyte((Byte)(ch>>8));
}

#define DATA1 Yaw.ShowData
#define DATA2 Roll.ShowData
#define DATA3 Pitch.ShowData
#define DATA4 SensorStatus_SC
#define DATA5 TimerGo.Flag
#define DATA6 TimerGo.EN
#define DATA7 ServoPara.TurnGoalAngle


void Board_SendData(void)
{
	#ifdef  SLAVECOM_EN
   SC_UARTSendbyte(SC_CheckByte1);
	 SC_UARTSendbyte(SC_CheckByte2);
	 SC_UARTSendWord(DATA1);
	 SC_UARTSendWord(DATA2);
	 SC_UARTSendWord(DATA3);
   SC_UARTSendWord(DATA4);
	 SC_UARTSendbyte(DATA5);
   SC_UARTSendbyte(DATA6);
	 
	 SC_UARTSendWord(Clock_0_Sensor.PulseNum);
	 SC_UARTSendWord(Clock_1_Sensor.PulseNum);
   SC_UARTSendWord(Clock_2_Sensor.PulseNum);
 	 SC_UARTSendWord(Clock_3_Sensor.PulseNum);
   SC_UARTSendWord(Clock_4_Sensor.PulseNum);
 	 SC_UARTSendWord(Clock_5_Sensor.PulseNum);
 	 SC_UARTSendWord(Clock_6_Sensor.PulseNum);
	 SC_UARTSendWord(Clock_7_Sensor.PulseNum);
	 SC_UARTSendWord(Clock_8_Sensor.PulseNum);
	 SC_UARTSendWord(Clock_9_Sensor.PulseNum);
	 SC_UARTSendWord(Clock_10_Sensor.PulseNum);
	 SC_UARTSendWord(Clock_11_Sensor.PulseNum);
	
	#endif
}

void ComWithHC(void)
{
		Board_SendData();    //向上位机发送数据
		SC_DataDeal();       //接收上位机的数据
}

