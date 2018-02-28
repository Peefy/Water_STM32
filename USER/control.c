#include "include.h"

RemoteCtrType RemoteCtr = {Disable,0,SERVOMIDINIT};

int8 ShipRunEN = Disable;
const Byte TIM_Interval = 10;

static u8 TIMcountMotor = 0;
static u8 TIMcountServo = 0;

void Ship_Control(void)
{
	if(ShipRunEN == Enable)
	{
		 if(++TIMcountMotor>10)  //100ms改变电机电压一次 防止电机过热
		 {
				Motor_Control();
				TIMcountMotor = 0;
		 }

	}
	else
	{   
		 MoSet = INITMOTORDUTY;  
		 Set_Motor_PWM(MoSet);
	}
			 if(++TIMcountServo >4)
		 {
				Servo_Control();    // 舵机40ms控制一次
				TIMcountServo = 0;
		 }
	Ship_Protection_HC();
	PowerOnWaitPoseCali();
}

void Stop(void)
{
	ShipRunEN = Disable;
	up_fmq();	
}

void Run(void)
{
	ShipRunEN = Enable;
	down_fmq();	
}

#define WaitPose_s 20
uint16 WaitPoseCount = 0;
bool IsWaitSuccess = false; 
void PowerOnWaitPoseCali(void)
{
	if(++WaitPoseCount > WaitPose_s*1000/TIM_Interval && IsWaitSuccess == false)
	{
		CaliPoseButNotYaw();
		ShipRunEN = Enable;
		IsWaitSuccess = true;
	}
}
/*****************************************************/

/**********************定时运行***********************/

TimerGoType TimerGo = {1,1,0,Disable,50};  

void Timer_Run(void)   //测试用 TIM2 10ms
{   
	 if(ShipRunEN == Enable)
	 {
			if(TimerGo.Flag==0 && TimerGo.Time_count<=TimerGo.Time_s*100 && TimerGo.EN==Enable)
			{
					MoSet = TimerGo.Voltige_Percent;
			}
			if(TimerGo.Time_count>TimerGo.Time_s*1000 / TIM_Interval)
			{
					MoSet = 0;
					TimerGo.Flag=1;
					TimerGo.EN = Disable;
			}
			if(TimerGo.EN == Disable)
			{
					TimerGo.Flag=0;
					TimerGo.Time_count=0;
			}
			if(TimerGo.EN == 1 && TimerGo.Flag == 0)
          ++TimerGo.Time_count;         //TimerRun
		}
		else
		{		
			 TimerGo.EN = Disable;
			 TimerGo.Time_s = 2; 
			 TimerGo.Flag=0;
		}
}

void TimerRun_HC(void)
{
		TimerGo.EN = Disable;
		TimerGo.Flag = 0;
		TimerGo.Time_count = 0;
	   if(IsEmpty(Queue_Byte) == false)
	   	{
				TimerGo.Time_s = GetInQueue(Queue_Byte);
				TimerGo.Voltige_Percent = GetInQueue(Queue_Byte);
	   	}
		else
			  TimerGo.Time_s = 0;
		TimerGo.EN = Enable;
}

/********************RemoteCtr**************************/

void RemoteCtrDataDeal(void)
{
	 if(RemoteCtr.EN == Enable)
	 {
			SerSet = RemoteCtr.ServoDuty;
			MoSet = RemoteCtr.MotorDuty;
	 }
}

/****************ProTection******************/
int8 ShipProCount = 0;
int8 HC_NoSend_Count = 0;
const Byte HC_Send_Interval = 120;

bool IsChanged(int16 inn)
{
    static int16 Temp;
	  static bool Result;
	  Result = !(Temp == inn);
		Temp = inn;
	  return Result;
}

void Ship_Protection_HC(void)   //上位机断开通信保护 上位机遥控器模式特有
{
		if( ++HC_NoSend_Count >HC_Send_Interval / TIM_Interval + 1)
		{
				if(IsChanged(RecieveByte) == false && RemoteCtr.MotorDuty != 0 )
				{
						++ShipProCount;
				}
				else 
				{
						if( -- ShipProCount < 1)
							ShipProCount = 0;
				}	
				if(ShipProCount > 5)
				{
						RemoteCtr.EN = Disable;
						ShipProCount = 0;
						RemoteCtr.MotorDuty = 0;
						MoSet = 0;  // 电机不转
				}
				HC_NoSend_Count = 0;
		}
		
}

/********************上电延时启动************************/

const Byte PowerOn_Time_s = 22;  //接通电池瞬间 开始计时
DepartStartType DepartStart = {0,0,0};

void PowerOnStart_Main(void)
{
   if(DepartStart.Time_count > PowerOn_Time_s*1000/TIM_Interval  && DepartStart.Flag == 0) 
   { 
      DepartStart.Flag = 1;
      //RaceModeEN = Enable; 
   }
   if(DepartStart.EN == Disable)
   {
      DepartStart.Time_count = 0;
      DepartStart.Flag = 0;
   }

}

void PowerOnStart_TIM(void)
{
	  if(DepartStart.EN == Enable && DepartStart.Flag == 0)
       ++DepartStart.Time_count;           
}

void PowerOnStart_EN(void)
{
		#ifdef PowerOnGoEN
		DepartStart.EN = Enable;
		#endif
}






