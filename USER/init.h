#ifndef _INIT_H_
#define _INIT_H_

#include "include.h"

/*********AD???????*********/   
#define Key_UP_Value     93
#define Key_DOWN_Value   929
#define Key_LEFT_Value   511
#define Key_RIGHT_Value  672
#define Key_OK_Value     340
/*********AD?????????*********/
#define  NO     0
#define  RIGHT  1
#define  DOWN   2
#define  LEFT   3
#define  UP     4
#define  OK     5

float absi(float ); 
float min(float ,float );
s16 min_s16(s16 inn1,s16 inn2);
void All_Init(void);
void LED_Init(void);
void TIM2_Init(void);

void MyLEDToggle(void);

//#define PowerEN
//#define SpeedSelectedEN

#endif
