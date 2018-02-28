#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "include.h"

#define Enable 1
#define DisEnable 0


typedef struct 
{
    int8 EN;
    int16 MotorDuty;
    int16 ServoDuty;	
}RemoteCtrType;

typedef struct
{
		uint8 Time_s ;         
		uint8 Flag;
		uint16 Time_count;    
	  uint8 EN;       
	  uint8 Voltige_Percent;
}TimerGoType;

typedef struct
{
		uint16 Time_count;    
	  uint8 EN;  
		uint8 Flag;
}DepartStartType;

typedef struct
{
    uint16 Kp;
	uint16 Ki;
	uint16 Kd;
	float Real_P;
	float Real_I;
	float Real_D;
}PIDType;

typedef
struct
{
		uint8 IsTest;
}StartTestType;

extern TimerGoType TimerGo;
extern RemoteCtrType RemoteCtr;
extern int8 ChipRunEN;
extern StartTestType StartTest;

void Chip_Control(void);

void Stop(void);
void Run(void);

void Timer_Run(void);
void TimerRun_HC(void);

void Chip_Protection_HC(void);

void RemoteCtrDataDeal(void);


//#define PowerOnGoEN

void PowerOnStart_TIM(void);
void PowerOnStart_Main(void);
void PowerOnStart_EN(void);
void PowerOnWaitPoseCali(void);

void StartTestGPIO_Init(void);


#endif
