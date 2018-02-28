#ifndef _BLDC_H_
#define _BLDC_H_

#include "include.h"

#define MotorPWM_Pin GPIO_Pin_6    //TIM3_CH1
#define MotorPWM_GPIO GPIOA

#define MotorDutyReg TIM3->CCR1   // 0~100

#define MAXMOTORDUTY  99
#define MINMOTORDUTY  0
#define INITMOTORDUTY 0

#define AcceleratorMid 0

typedef struct
{
    byte StraghtSpeed;
	  byte TurnSpeed;
	  byte SpeedSelectConut;
}MotorParaType;

extern int16 MotorDuty;
extern int16 MoSet;
extern int8 RaceModeEN;

extern MotorParaType MotorPara;

void Motor_Control(void);
void Set_Motor_PWM(int );
int16 LowVoltageStart(int16);
int16 SmoothingSlowDown(void);  
int GetMotorNowDuty(void);
void HighSpeed(void);
void MiddleSpeed(void);
void LowSpeed(void);
void SpeedFromHC(void);


#define MIN_SPEED 20

#define YaoKongDebug 1
#define RaceMode 1

#endif
