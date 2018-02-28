#include "include.h"

int16 ServoDuty = 0;
int16 SerMid = SERVOMIDINIT;
int16 SerPWM = SERVOMIDINIT;
int16 SerSet = SERVOMIDINIT;

PIDType SerPD = {46,0,400,0,0,0};// Kp Ki Kd
ServoParaType ServoPara = {0,SERVOMIDINIT,false,false};

int GetServoNowDuty(void)
{
	static int16 ServoDutyTemp;
	ServoDutyTemp = ServoDutyReg;
	ServoPara.DutyNow = ServoDutyTemp;
	return ServoPara.DutyNow;
}

void Set_Servo_PWM(int value) 	//舵机占空比0.05 ~ 0.1  1000us ~ 2000us 
{   
   SerPWM = SerMid + value;   
   if(SerPWM>SerMid + SERVO_RANGE_L)  SerPWM = SerMid + SERVO_RANGE_L; 
   if(SerPWM<SerMid - SERVO_RANGE_R)  SerPWM = SerMid - SERVO_RANGE_R;
	 if(SerPWM <= SERVO_DUTY_REFINE_S)  SerPWM = SERVO_DUTY_REFINE_S;
	 if(SerPWM >= SERVO_DUTY_REFINE_B)  SerPWM = SERVO_DUTY_REFINE_B;
   ServoDutyReg = SerPWM;
}

void Servo_PD(int16 GoalTemp)
{
    static float e = 0; 
    static float e_bef = 0;        
    static float ec = 0;       
	int16 SerSet_Delta = 0;
	if(GoalTemp >= 0  && Yaw.ShowData >= 0)
		e = absi(GoalTemp - Yaw.ShowData)/100.0;
	else if (GoalTemp < 0  && Yaw.ShowData < 0)
		e = absi(GoalTemp - Yaw.ShowData)/100.0;
	else if (GoalTemp < 0  && Yaw.ShowData >= 0)
		e = MIN(18000 - Yaw.ShowData + GoalTemp + 18000,Yaw.ShowData - GoalTemp)/100.0;
	else if (GoalTemp >= 0  && Yaw.ShowData < 0)
		e = MIN(18000 - GoalTemp + Yaw.ShowData + 18000,GoalTemp - Yaw.ShowData)/100.0;
	ec = e - e_bef;
	SerPD.Real_P = SerPD.Kp * 0.1;
	SerPD.Real_D = SerPD.Kd * 0.1;
	SerSet_Delta = SerPD.Real_P * e + SerPD.Real_D* ec;
	e_bef = e;
	SerSet = SERVOMIDINIT + ShipDirection * SerSet_Delta;
}

void SensorJudgeTurn(void)
{
		SerSet = SERVOMIDINIT + ShipDirection * 100 * 
			MAX(SensorPara.LeftMaxWeight,SensorPara.RightMaxWeight);
}

extern char* CMDNames_[Iterm_CMD_TOTAL];
extern void GUI_RefreshCmdUI(void);
#define ServoDebugPanelShowStr CMDNames_[4]

void Servo_Debug(void)
{
	static byte ModeCount = 0;
	ModeCount = !ModeCount;
	ServoPara.DebugEN = ModeCount;
	ServoPara.DebugEN == true ? up_fmq():down_fmq();
  ServoDebugPanelShowStr = ServoPara.DebugEN == true ? "SerDebOn ":"SerDebOff"; 
	GUI_RefreshCmdUI();
}

void ServoPWM_Cal(void)
{
    
}

void Servo_Control(void)
{
	  if(ServoPara.PDcontrolerEN == true && RemoteCtr.EN == DisEnable && ServoPara.DebugEN == false)
		{

	     Servo_PD(ServoPara.TurnGoalAngle);
			 //Servo_PD(60 * 100); //别忘记乘以100  测试用
		}
    Set_Servo_PWM(SerSet - SERVOMIDINIT);
}

void ServoPDChangeFromHC(void)
{
	SerPD.Kp = GetInQueue(Queue_Byte) * 256 + GetInQueue(Queue_Byte);
	SerPD.Kd = GetInQueue(Queue_Byte) * 256 + GetInQueue(Queue_Byte);
	ok_fmq();
	ok_fmq();
}





