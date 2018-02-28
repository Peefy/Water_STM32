#include "include.h"

int16 MotorDuty = 0;
int16 MoSet = 0;

int8 RaceModeEN = DisEnable;

MotorParaType MotorPara = {65,65,0};

#ifdef RaceMode
		bool IsAlwaysRun = true;
#else
		bool IsAlwaysRun = false;
#endif

void Set_Motor_PWM(int value)             
{   
	MotorDutyReg = (int)RANGE(value,MINMOTORDUTY,MAXMOTORDUTY);
}

void Motor_Control(void)
{
		int StaightSpeedTemp = SensorPara.HasQianSensorRec == true ?  MotorPara.StraghtSpeed : MIN_SPEED;
		int TurnSpeedTemp = SensorPara.HasQianSensorRec == true ?  MotorPara.TurnSpeed : MIN_SPEED;
		if(RaceModeEN == Enable)
		{
			if(ShipDirection == Straight)
				MoSet = MotorPara.StraghtSpeed;
			else
				MoSet = MotorPara.TurnSpeed;
		}
		#ifdef YaoKongDebug
		if(TimerGo.EN == false && RemoteCtr.EN == false)
		{
			if(SensorStatus_SC == 0)
			{		
					MoSet = (IsAlwaysRun == true) ? (StaightSpeedTemp - 10) :MINMOTORDUTY;

			}
			else 
			{
				if(ShipDirection == Straight) MoSet = StaightSpeedTemp;
				else                   			 MoSet = TurnSpeedTemp;
			}
		}
		#endif
		Set_Motor_PWM(LowValtageStart());  //慢慢给电机电压
		//Set_Motor_PWM(MoSet);            //直接给电机电压
}

byte LowStartCoe = 50;  //越小滞后越厉害 范围1~100
byte SlowDownCoe = 50;  //越小滞后越厉害 范围1~100
byte MotorNowDuty = 0;

int16 LowValtageStart(void)  //低通滤波 给定积分算法 使平滑加速 因为南孚电池不给力 
{
	  static int16 MN_Temp = 0;
	  if(MoSet >= GetMotorNowDuty() + 9)
			MN_Temp = (float)(MoSet * LowStartCoe + GetMotorNowDuty() * (100 - LowStartCoe))/100.0 + 0.5;//加0.5代表四舍五入
		else if( GetMotorNowDuty() >= MoSet + 8)
		  MN_Temp = (float)(MoSet * SlowDownCoe + GetMotorNowDuty() * (100 - SlowDownCoe))/100.0 + 0.5;//加0.5代表四舍五入;
		else
			MN_Temp = MoSet;
		return MN_Temp;
}

int GetMotorNowDuty(void)
{
	  static int16 MotorDutyTemp;
		MotorDutyTemp = MotorDutyReg;
		MotorNowDuty = MotorDutyTemp;
		return MotorDutyTemp;
}

void HighSpeed(void)
{
	MotorPara.StraghtSpeed = 70;
	MotorPara.TurnSpeed = 55;
	up_fmq();
}

void MiddleSpeed(void)

{    MotorPara.StraghtSpeed = 50;
	   MotorPara.TurnSpeed = 40;
		up_fmq();
}

void LowSpeed(void)
{
	MotorPara.StraghtSpeed = 40;
	MotorPara.TurnSpeed = 30;
	up_fmq();
}

void SpeedFromHC(void)
{
	MotorPara.StraghtSpeed =  GetInQueue(Queue_Byte);
	MotorPara.TurnSpeed = MotorPara.StraghtSpeed - 20;
	up_fmq();
}

extern char* CMDNames_[Iterm_CMD_TOTAL];
extern void GUI_RefreshCmdUI(void);
#define IsAlwaysRunPanelShowStr CMDNames_[8]

void ChangeIsAlwaysRun()
{
	IsAlwaysRun = !IsAlwaysRun;
	IsAlwaysRun == true?up_fmq():down_fmq();
	IsAlwaysRunPanelShowStr = IsAlwaysRun == true?"CgRunOn ":"CgRunOff";
	GUI_RefreshCmdUI();
}

