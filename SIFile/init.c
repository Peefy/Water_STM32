#include "include.h"

//#region HardWare and Core

void LED_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE); 				  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	LED = 0;
}

void MyLEDToggle(void)
{
		static u8 TIMcount = 0;
	 if(++TIMcount>20)  //1s
	 {
			LED = !LED;	  
		  TIMcount = 0;
	 }	
}

void TIM2_Init_ms(int16 ms)
{
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	ms = RANGE(ms,0,6000);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseStructure.TIM_Period = ms * 10 - 1; // 10ms??
	TIM_TimeBaseStructure.TIM_Prescaler =7200 - 1; //??????TIMx???????????  ???
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //??????:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM??????
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
    
    TIM_Cmd(TIM2,ENABLE);
    
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    
    TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ????
	NVIC_Init(&NVIC_InitStructure);	//??
	
	
}

void TIM2_Init(void) //10ms
{
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseStructure.TIM_Period = 20000 - 1; // 10ms中断
	TIM_TimeBaseStructure.TIM_Prescaler = 36 - 1; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);
	
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根�
	
	TIM_Cmd(TIM2,ENABLE);   //使能定时器
		
}

float absi(float data_s)       
{
    return data_s>=0?data_s:-data_s;
}

float min(float inn1,float inn2)
{
		return (inn1>=inn2)?inn2:inn1;
}

s16 min_s16(s16 inn1,s16 inn2)
{
		return (inn1>=inn2)?inn2:inn1;
}

void MYLCD_P8x16Str(byte x,byte y,char ch[])
{
		LCD_P8x16Str(x, y*2, ch);
}

uint8 OLED_Key_Status;

uint8 KeyScan(void) 
{

    if(absi(AD_Value[0] - Key_DOWN_Value)<35)
    {
       OLED_Key_Status = DOWN;
    }
    else if(absi(AD_Value[0] - Key_LEFT_Value)<35)
    {
       OLED_Key_Status = LEFT;
    }
    else if(absi(AD_Value[0] - Key_RIGHT_Value)<35)
    {
       OLED_Key_Status = RIGHT;
    }
    else if(absi(AD_Value[0] - Key_OK_Value)<15)
    {
       OLED_Key_Status = OK;
    }    
		else if(absi(AD_Value[0] - Key_UP_Value)<15)
    {
       OLED_Key_Status = UP;
    }
    else
    {
       OLED_Key_Status = NO;
    }
    return OLED_Key_Status;
}

//#endregion HardWare and Core

void All_Init(void)
{
	  delay_init(72);	    		 //延时函数初始化	
		TIM2_Init();       //10ms定时器
		TIM3_PWM_Init();   //MOTOR_PWM  PTA6  
	  TIM4_PWM_Init();   //SERVO_PWM  PTB6 
	  LED_Init();        //板子上的灯初始化
	  OLED_Init();       //液晶屏初始化
    USART1_Init();          //陀螺仪 
	#ifdef SLAVECOM_EN
		USART2_Init();  		//无线串口
	#endif  
		DMA_ADC1_Init();    //AD按键初始化
	  Sensor_Init();      //红外传感器初始化                                                                          
	  sound_init();	      //蜂鸣器初始化
		InitQueue(Queue_Byte);//队列初始化
		PowerOnStart_EN();
		PowerOnSpeedSelect();		
	  #ifdef	IWDG_EN
	  IWDG_Init();
		#endif
}

