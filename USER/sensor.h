#ifndef _SENSOR_H_
#define _SENSOR_H_

#include "include.h"

typedef struct
{
	Byte Number;
	u32 Count;
	u16 PulseNum;
	u16 PulseNumPre;
	byte Status;
	u8 WeightInit;
	u8 WeightNow;
}Sensor_Type;

typedef struct
{
	byte RightWeightTotal;
	byte LeftWeightTotal;
	byte RightMaxWeight;
	byte LeftMaxWeight;
	const byte const_LeftRight_index;
	const byte const_Total_index;
	byte QianLeftRecNum;
	byte QianRightRecNum;
	bool HasQianSensorRec;
	bool HouSensorIsUseful;
}SensorPara_Type;

extern Sensor_Type Sensor[16];  //实际只用了12个 具体看宏
extern SensorPara_Type SensorPara;

// 2 3 6 10 用不了
#define Clock_0_Sensor  Sensor[0]  //9
/*******Left**********/
#define Clock_1_Sensor  Sensor[1]  //11
#define Clock_2_Sensor  Sensor[4]  //12
#define Clock_3_Sensor  Sensor[5]  //13 
#define Clock_4_Sensor  Sensor[7]  //14
#define Clock_5_Sensor  Sensor[8]  //15

#define Clock_6_Sensor  Sensor[9]  //0
/*******Right**********/
#define Clock_7_Sensor  Sensor[11] //1
#define Clock_8_Sensor  Sensor[12] //4
#define Clock_9_Sensor  Sensor[13] //5
#define Clock_10_Sensor Sensor[14] //7
#define Clock_11_Sensor Sensor[15] //8


//2 3 6 10 no use

#define QianMiddleSensor   Sensor[0]
/*******Right**********/
#define QianRightSensor1   Sensor[1]
#define QianRightSensor2   Sensor[4]
#define QianRightSensor3   Sensor[5]

#define HouRightSensor2     Sensor[7]
#define HouRightSensor1     Sensor[8]

#define HouMiddleSensor    Sensor[9]
/*******Left**********/
#define HouLeftSensor1    Sensor[11]
#define HouLeftSensor2    Sensor[12]

#define QianLeftSensor3    Sensor[13]
#define QianLeftSensor2    Sensor[14]
#define QianLeftSensor1    Sensor[15]


extern int16 SensorStatus_SC;

void SensorDeal(void);
void Sensor_Init(void);
void SensorWeight_Init(void);
void SensorParaClear(SensorPara_Type *This);
byte GetQianLeftRecNum(void);
byte GetQianRightRecNum(void);

#endif
