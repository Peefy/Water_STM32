#ifndef _SERVO_H_
#define _SERVO_H_

#include "include.h"

#define ServoPWM_Pin GPIO_Pin_6  //TIM4_CH1
#define ServoPWM_GPIO GPIOB

#define ServoDutyReg TIM4->CCR1  //<2000

//��� PWMռ�ձȴ�ʱ����ת PWMռ�ձ�Сʱ����ת
#define SERVOMIDINIT   1530
#define SERVO_RANGE_R  480
#define SERVO_RANGE_L  720

#define SERVO_DUTY_REFINE_S 1050
#define SERVO_DUTY_REFINE_B 2250

#define Servo_TrunLeft_PoseSign -1
#define Servo_TrunRight_PoseSign 1

#define ServoRun_MaxTurnAngle 250  //��λ��

typedef struct
{
    int16 TurnGoalAngle;
	  int16 DutyNow;
	  bool PDcontrolerEN;
		bool DebugEN;
}ServoParaType;

extern int16 ServoDuty;
extern int16 SerSet;
extern int16 ServoDutyNow;
extern int16 Goal_Angle;

extern ServoParaType ServoPara;

void Set_Servo_PWM(int );
void Servo_Debug(void);
void Servo_Control(void);
void ServoPDChangeFromHC(void);


#define SERVO_DEBUG

#endif
