#include "include.h"

Sensor_Type Sensor[16] = {{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},
													{9,0},{10,0},{11,0},{12,0},{13,0},{14,0},{15,0},{16,0}};
//只用了12个传感器
SensorPara_Type SensorPara = {0,0,0,0,9,16,0,0,true,true};												
													
int16 SensorStatus_SC;
													
void Sensor_Init(void)   
{
		GPIO_InitTypeDef GPIO_InitStructure; 
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB| RCC_APB2Periph_GPIOA |RCC_APB2Periph_AFIO, ENABLE); 		//初始化别忘了时钟	
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1  | GPIO_Pin_4 | GPIO_Pin_5
																	|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9
																	|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14
																	|GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		/****************PB2 和 PB6 不行********************/
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0); //把GPIO连接到中断上
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1); //把GPIO连接到中断上
		//GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource3); //把GPIO连接到中断上
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource4); //把GPIO连接到中断上
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5); //把GPIO连接到中断上
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource7); //把GPIO连接到中断上
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource8); //把GPIO连接到中断上
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource9); //把GPIO连接到中断上
		//GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource10); //把GPIO连接到中断上
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource11); //把GPIO连接到中断上
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource12);//把GPIO连接到中断上
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource13);//把GPIO连接到中断上
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);//把GPIO连接到中断上
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource15);//把GPIO连接到中断上
		/****************Line2 和 Line6 不行********************/
		EXTI_InitStructure.EXTI_Line=EXTI_Line0;//PB0-->Line0
		EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//上升沿和下降沿都触发；
		EXTI_InitStructure.EXTI_LineCmd=ENABLE;
		EXTI_Init(&EXTI_InitStructure);
    
    EXTI_InitStructure.EXTI_Line=EXTI_Line1;//PB1-->Line1
    EXTI_Init(&EXTI_InitStructure);   
    //EXTI_InitStructure.EXTI_Line=EXTI_Line2;//PB2-->Line2
    //EXTI_Init(&EXTI_InitStructure);   
    //EXTI_InitStructure.EXTI_Line=EXTI_Line3;//PB3-->Line3
    //EXTI_Init(&EXTI_InitStructure);
    EXTI_InitStructure.EXTI_Line=EXTI_Line4;//PB4-->Line4
    EXTI_Init(&EXTI_InitStructure);    
    EXTI_InitStructure.EXTI_Line=EXTI_Line5;//PB5-->Line5
    EXTI_Init(&EXTI_InitStructure);
    //EXTI_InitStructure.EXTI_Line=EXTI_Line6;//PB6-->Line6
    //EXTI_Init(&EXTI_InitStructure);
    EXTI_InitStructure.EXTI_Line=EXTI_Line7;//PB7-->Line7
    EXTI_Init(&EXTI_InitStructure);   
    EXTI_InitStructure.EXTI_Line=EXTI_Line8;//PB8-->Line8
    EXTI_Init(&EXTI_InitStructure);
    EXTI_InitStructure.EXTI_Line=EXTI_Line9;//PB9-->Line9
    EXTI_Init(&EXTI_InitStructure);
    //EXTI_InitStructure.EXTI_Line=EXTI_Line10;//PB10-->Line10
    //EXTI_Init(&EXTI_InitStructure);
    EXTI_InitStructure.EXTI_Line=EXTI_Line11;//PB11-->Line11
    EXTI_Init(&EXTI_InitStructure);
    EXTI_InitStructure.EXTI_Line=EXTI_Line12;//PB12-->Line12
    EXTI_Init(&EXTI_InitStructure);
    EXTI_InitStructure.EXTI_Line=EXTI_Line13;//PB13-->Line13
    EXTI_Init(&EXTI_InitStructure);   
    EXTI_InitStructure.EXTI_Line=EXTI_Line14;//PB14-->Line14
    EXTI_Init(&EXTI_InitStructure);
    EXTI_InitStructure.EXTI_Line=EXTI_Line15;//PB15-->Line15
    EXTI_Init(&EXTI_InitStructure);
		
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;//PB0
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;    
    NVIC_Init(&NVIC_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;//PB1
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;    
    NVIC_Init(&NVIC_InitStructure);
    
    //NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;//PB2没有
    //NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
    //NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;    
    //NVIC_Init(&NVIC_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel=EXTI3_IRQn;//PB3
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;    
    NVIC_Init(&NVIC_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel=EXTI4_IRQn;//PB4
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;    
    NVIC_Init(&NVIC_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;//PB5,PB6,PB7,PB8,PB9
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;    
    NVIC_Init(&NVIC_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel=EXTI15_10_IRQn;//PB10,PB11,PB12,PB13,PB14,PB15
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;    
    NVIC_Init(&NVIC_InitStructure);   
		
		SensorWeight_Init();
		
}

void EXTI0_IRQHandler(void)
{
		if( EXTI_GetITStatus(EXTI_Line0) != RESET )
		{
				EXTI_ClearITPendingBit(EXTI_Line0);   
				if(++Sensor[0].Count > 65534) 
						Sensor[0].Count = 0;
		} 
}
void EXTI1_IRQHandler(void)
{
		if( EXTI_GetITStatus(EXTI_Line1) != RESET )
		{
				EXTI_ClearITPendingBit(EXTI_Line1);       
				if(++Sensor[1].Count > 65534) 
						Sensor[1].Count = 0;
		} 
}
/*
void EXTI2_IRQHandler(void)
{
  if( EXTI_GetITStatus(EXTI_Line2) != RESET )
	{
		EXTI_ClearITPendingBit(EXTI_Line2);       
	} 
}
*/
void EXTI3_IRQHandler(void)
{
		if( EXTI_GetITStatus(EXTI_Line3) != RESET )
		{
				EXTI_ClearITPendingBit(EXTI_Line3);   
				if(++Sensor[3].Count > 65534) 
						Sensor[3].Count = 0;
		} 
}
void EXTI4_IRQHandler(void)
{
		if( EXTI_GetITStatus(EXTI_Line4) != RESET )
		{
				EXTI_ClearITPendingBit(EXTI_Line4);    
				if(++Sensor[4].Count> 65534) 
						Sensor[4].Count = 0;
		} 
}
void EXTI9_5_IRQHandler(void)
{
		if( EXTI_GetITStatus(EXTI_Line5) != RESET )
		{
				EXTI_ClearITPendingBit(EXTI_Line5);  
				if(++Sensor[5].Count > 65534) 
						Sensor[5].Count = 0;
		}  
		/*if( EXTI_GetITStatus(EXTI_Line6) != RESET )
		{
				EXTI_ClearITPendingBit(EXTI_Line6);       
		} */   
		if( EXTI_GetITStatus(EXTI_Line7) != RESET )
		{
				EXTI_ClearITPendingBit(EXTI_Line7); 
				if(++Sensor[7].Count > 65534) 
						Sensor[7].Count = 0;
		}   
		if( EXTI_GetITStatus(EXTI_Line8) != RESET )
		{
				EXTI_ClearITPendingBit(EXTI_Line8);
				if(++Sensor[8].Count > 65534) 
						Sensor[8].Count = 0;
		}    
		if( EXTI_GetITStatus(EXTI_Line9) != RESET )
		{
				EXTI_ClearITPendingBit(EXTI_Line9);
				if(++Sensor[9].Count > 65534) 
						Sensor[9].Count = 0;
		}
}
void EXTI15_10_IRQHandler(void)
{
		if( EXTI_GetITStatus(EXTI_Line10) != RESET )
		{
				EXTI_ClearITPendingBit(EXTI_Line10);   
				if(++Sensor[10].Count > 65534) 
						Sensor[10].Count = 0;
		}
		if( EXTI_GetITStatus(EXTI_Line11) != RESET )
		{
				EXTI_ClearITPendingBit(EXTI_Line11);  
				if(++Sensor[11].Count > 65534) 
						Sensor[11].Count = 0;			
		}
		if( EXTI_GetITStatus(EXTI_Line12) != RESET )
		{
				EXTI_ClearITPendingBit(EXTI_Line12);  
				if(++Sensor[12].Count > 65534) 
						Sensor[12].Count = 0;
		}
		if( EXTI_GetITStatus(EXTI_Line13) != RESET )
		{
				EXTI_ClearITPendingBit(EXTI_Line13); 
				if(++Sensor[13].Count > 65534) 
						Sensor[13].Count = 0;      
		}
		if( EXTI_GetITStatus(EXTI_Line14) != RESET )
		{
				EXTI_ClearITPendingBit(EXTI_Line14);  
				if(++Sensor[14].Count > 65534) 
						Sensor[14].Count = 0;
		}
		if( EXTI_GetITStatus(EXTI_Line15) != RESET )
		{
				EXTI_ClearITPendingBit(EXTI_Line15);    
				if(++Sensor[15].Count > 65534) 
						Sensor[15].Count = 0;
		}
}

extern char* CMDNames_[Iterm_CMD_TOTAL];
extern void GUI_RefreshCmdUI(void);
#define HouSensorIsUsefulPanelShowStr CMDNames_[12]

void ChangeHouSensorIsUseful(void)
{
		up_fmq();
		SensorPara.HouSensorIsUseful = !SensorPara.HouSensorIsUseful;
		HouSensorIsUsefulPanelShowStr = \
			SensorPara.HouSensorIsUseful == true ?"HouSenOn ":"HouSenOff";
		GUI_RefreshCmdUI();
}

void SensorWeight_Init(void)
{
	/*
		QianMiddleSensor.Weight = 1;
		QianLeftSensor.Weight = 2;
		QianRightSensor.Weight = 2;
	
	  HouMiddleSensor.Weight = 1;
		HouLeftSensor.Weight = 8;
		HouRightSensor.Weight = 8; 
	
		ZuoMiddleSensor.Weight = 10
		ZuoLeftSensor.Weight = 6;
		ZuoRightSensor.Weight = 4; 
	
		YouMiddleSensor.Weight = 10;
		YouLeftSensor.Weight = 4;
		YouRightSensor.Weight = 6; 
	*/
//正前方	
    Clock_0_Sensor.WeightInit = 0;
/*******Right**********/
    Clock_1_Sensor.WeightInit = 20;
		Clock_2_Sensor.WeightInit = 43;
		Clock_3_Sensor.WeightInit = 70;
		Clock_4_Sensor.WeightInit = 69;
		
		Clock_5_Sensor.WeightInit = 68;
//???
		Clock_6_Sensor.WeightInit = 10;
/*******Left**********/
		Clock_7_Sensor.WeightInit = 68;
		Clock_8_Sensor.WeightInit = 69;
		
		Clock_9_Sensor.WeightInit = 70;
		Clock_10_Sensor.WeightInit = 43;
		Clock_11_Sensor.WeightInit = 20;
	  
}

static byte SensorToZeroCount = 0;
#define TIM_Interval 10
int16 SensorToZero_ms = 400;

void SensorDeal(void)   //Ignore the Transmission Delay 
{
	  byte i = 0;
		if(++SensorToZeroCount>SensorToZero_ms/TIM_Interval)
		{
				SensorToZeroCount = 0;
	      for(;i<16;++i)
				{
					 //Sensor[i].PulseNum = (u16)(((float)Sensor[i].Count * 0.9 +  (float)Sensor[i].PulseNum * 0.1) + 0.5);//低通滤波
						Sensor[i].PulseNum = Sensor[i].Count;
					 //if(Sensor[i].PulseNum > Sensor[i].PulseNumPre + 22)   //防抖动滤波 正式比赛频率太高 所以去掉
							//Sensor[i].PulseNum = Sensor[i].PulseNumPre;
					 Sensor[i].Count = 0;
					 Sensor[i].PulseNumPre = Sensor[i].PulseNum;
					 
				}
				for(i=0;i<16;++i)
				{					 
				   if(Sensor[i].PulseNum >= 6)
					 {
							Sensor[i].Status = 1;
						  SensorStatus_SC |= 1<<i;
						  Sensor[i].WeightNow = Sensor[i].WeightInit;
					 }
					 else
					 {
						  Sensor[i].Status = 0; 
						  SensorStatus_SC &= ~(1<<i);
							Sensor[i].WeightNow = 0;
					 }
				}
				ServoPara.PDcontrolerEN = true;
				NewAnalysis();
		}
}

void SensorParaClear(SensorPara_Type *This)
{
		This->RightWeightTotal = 0;
		This->LeftWeightTotal  = 0;
		This->LeftMaxWeight  = 0;
		This->RightMaxWeight = 0;
		This->QianLeftRecNum  = 0;
		This->QianRightRecNum = 0;
}

byte GetQianLeftRecNum(void)
{
		if(QianLeftSensor3.Status == 1)
		{
				if(QianLeftSensor2.Status == 1)
				{
						if(QianLeftSensor1.Status == 1)
								return 3;
						else
							  return 2;
				}
				else
				{
						if(QianLeftSensor1.Status == 1)
								return 2;
						else
							  return 1;
				}
		}
		else
		{
				if(QianLeftSensor2.Status == 1)
				{
						if(QianLeftSensor1.Status == 1)
								return 2;
						else
							  return 1;
				}
				else
				{
						if(QianLeftSensor1.Status == 1)
								return 1;
						else
							  return 0;
				}
		}
}

byte GetQianRightRecNum(void)
{
				if(QianRightSensor3.Status == 1)
		{
				if(QianRightSensor2.Status == 1)
				{
						if(QianRightSensor1.Status == 1)
								return 3;
						else
							  return 2;
				}
				else
				{
						if(QianRightSensor1.Status == 1)
								return 2;
						else
							  return 1;
				}
		}
		else
		{
				if(QianRightSensor2.Status == 1)
				{
						if(QianRightSensor1.Status == 1)
								return 2;
						else
							  return 1;
				}
				else
				{
						if(QianRightSensor1.Status == 1)
								return 1;
						else
							  return 0;
				}
		}
}






