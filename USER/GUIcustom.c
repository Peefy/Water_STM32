//Last Write Time: 2016-08-15  14:03:56
#include "GUIcustom.h"

extern s8 index_FirstItermInPage;

extern s32 Para16s[Iterm_TOTAL];


char ParaNames[Iterm_TOTAL][ItermNameLengthMax+1]=
{
"AD0",
"AD1",
"RcByte",
"rc",
"Yaw",
"Roll",
"Pitch",
"RcByte",
"MotorD",
"ServoD",
"SerSet",
"SerMid",
"RunEN",
"MoSet",
"CtrEN",
"S0Cnt",
"S1Cnt",
"S2Cnt",
"S3Cnt",
"S4Cnt",
"S5Cnt",
"S6Cnt",
"S7Cnt",
"S8Cnt",
"S9Cnt",
"S10Cnt",
"S11Cnt",
"S12Cnt",
"S13Cnt",
"S14Cnt",
"S15Cnt",
"MNDuty",
"LowCoe",
"SerKp",
"SerKd",
"Goal",
"Goal",
"ZDspd",
"WDspd",
"TR_s",
"TR_en",
"R_W1",
"R_W2",
"R_W3",
"L_W1",
"L_W2",
"L_W3"
};

const s32 ParaSteps[Iterm_TOTAL]=
{
1,
1,
1,
1,
1,
1,
1,
1,
10,
1,
10,
10,
1,
10,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
10,
10,
1,
1,
1,
1,
1,
1,
1,
1
};

const s32 ParaMax[Iterm_TOTAL]=
{
65535,
65535,
65535,
65535,
65535,
65535,
65535,
65535,
65535,
65535,
65535,
65535,
1,
65535,
1,
65535,
65535,
65535,
65535,
65535,
65535,
65535,
65535,
65535,
65535,
65535,
65535,
65535,
65535,
65535,
65535,
100,
100,
10000,
10000,
10000,
10000,
90,
90,
100,
100,
100,
100,
100,
100,
100,
100
};

const s32 ParaMin[Iterm_TOTAL]=
{
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0
};

void Panel_LoadParas(u8 index)
{
	if(index != 0)
		Para16s[0] = AD_Value[0];
	if(index != 1)
		Para16s[1] = AD_Value[1];
	if(index != 2)
		Para16s[2] = RecieveByte;
	if(index != 3)
		Para16s[3] = recieve;
	if(index != 4)
		Para16s[4] = Yaw.ShowData;
	if(index != 5)
		Para16s[5] = Roll.ShowData;
	if(index != 6)
		Para16s[6] = Pitch.ShowData;
	if(index != 7)
		Para16s[7] = RecieveByte;
	if(index != 8)
		Para16s[8] = MotorDuty;
	if(index != 9)
		Para16s[9] = ServoDuty;
	if(index != 10)
		Para16s[10] = SerSet;
	if(index != 11)
		Para16s[11] = SerMid;
	if(index != 12)
		Para16s[12] = ShipRunEN;
	if(index != 13)
		Para16s[13] = MoSet;
	if(index != 14)
		Para16s[14] = RemoteCtr.EN;
	if(index != 15)
		Para16s[15] = Sensor[0].PulseNum;
	if(index != 16)
		Para16s[16] = Sensor[1].PulseNum;
	if(index != 17)
		Para16s[17] = Sensor[2].PulseNum;
	if(index != 18)
		Para16s[18] = Sensor[3].PulseNum;
	if(index != 19)
		Para16s[19] = Sensor[4].PulseNum;
	if(index != 20)
		Para16s[20] = Sensor[5].PulseNum;
	if(index != 21)
		Para16s[21] = Sensor[6].PulseNum;
	if(index != 22)
		Para16s[22] = Sensor[7].PulseNum;
	if(index != 23)
		Para16s[23] = Sensor[8].PulseNum;
	if(index != 24)
		Para16s[24] = Sensor[9].PulseNum;
	if(index != 25)
		Para16s[25] = Sensor[10].PulseNum;
	if(index != 26)
		Para16s[26] = Sensor[11].PulseNum;
	if(index != 27)
		Para16s[27] = Sensor[12].PulseNum;
	if(index != 28)
		Para16s[28] = Sensor[13].PulseNum;
	if(index != 29)
		Para16s[29] = Sensor[14].PulseNum;
	if(index != 30)
		Para16s[30] = Sensor[15].PulseNum;
	if(index != 31)
		Para16s[31] = MotorNowDuty ;
	if(index != 32)
		Para16s[32] = LowStartCoe;
	if(index != 33)
		Para16s[33] = SerPD.Kp;
	if(index != 34)
		Para16s[34] = SerPD.Kd;
	if(index != 35)
		Para16s[35] = ServoPara.TurnGoalAngle;
	if(index != 36)
		Para16s[36] = ServoPara.TurnGoalAngle;
	if(index != 37)
		Para16s[37] = MotorPara.StraghtSpeed;
	if(index != 38)
		Para16s[38] = MotorPara.TurnSpeed;
	if(index != 39)
		Para16s[39] = TimerGo.Time_s;
	if(index != 40)
		Para16s[40] = TimerGo.EN;
	if(index != 41)
		Para16s[41] = Clock_1_Sensor.WeightInit;
	if(index != 42)
		Para16s[42] = Clock_2_Sensor.WeightInit;
	if(index != 43)
		Para16s[43] = Clock_3_Sensor.WeightInit;
	if(index != 44)
		Para16s[44] = Clock_11_Sensor.WeightInit;
	if(index != 45)
		Para16s[45] = Clock_10_Sensor.WeightInit;
	if(index != 46)
		Para16s[46] = Clock_9_Sensor.WeightInit ;
}
void Panel_SaveParas()
{
	AD_Value[0] = Para16s[0];
	AD_Value[1] = Para16s[1];
	RecieveByte = Para16s[2];
	recieve = Para16s[3];
	Yaw.ShowData = Para16s[4];
	Roll.ShowData = Para16s[5];
	Pitch.ShowData = Para16s[6];
	RecieveByte = Para16s[7];
	MotorDuty = Para16s[8];
	ServoDuty = Para16s[9];
	SerSet = Para16s[10];
	SerMid = Para16s[11];
	ShipRunEN = Para16s[12];
	MoSet = Para16s[13];
	RemoteCtr.EN = Para16s[14];
	Sensor[0].PulseNum = Para16s[15];
	Sensor[1].PulseNum = Para16s[16];
	Sensor[2].PulseNum = Para16s[17];
	Sensor[3].PulseNum = Para16s[18];
	Sensor[4].PulseNum = Para16s[19];
	Sensor[5].PulseNum = Para16s[20];
	Sensor[6].PulseNum = Para16s[21];
	Sensor[7].PulseNum = Para16s[22];
	Sensor[8].PulseNum = Para16s[23];
	Sensor[9].PulseNum = Para16s[24];
	Sensor[10].PulseNum = Para16s[25];
	Sensor[11].PulseNum = Para16s[26];
	Sensor[12].PulseNum = Para16s[27];
	Sensor[13].PulseNum = Para16s[28];
	Sensor[14].PulseNum = Para16s[29];
	Sensor[15].PulseNum = Para16s[30];
	MotorNowDuty  = Para16s[31];
	LowStartCoe = Para16s[32];
	SerPD.Kp = Para16s[33];
	SerPD.Kd = Para16s[34];
	ServoPara.TurnGoalAngle = Para16s[35];
	ServoPara.TurnGoalAngle = Para16s[36];
	MotorPara.StraghtSpeed = Para16s[37];
	MotorPara.TurnSpeed = Para16s[38];
	TimerGo.Time_s = Para16s[39];
	TimerGo.EN = Para16s[40];
	Clock_1_Sensor.WeightInit = Para16s[41];
	Clock_2_Sensor.WeightInit = Para16s[42];
	Clock_3_Sensor.WeightInit = Para16s[43];
	Clock_11_Sensor.WeightInit = Para16s[44];
	Clock_10_Sensor.WeightInit = Para16s[45];
	Clock_9_Sensor.WeightInit  = Para16s[46];
}


//函数指针
void (*pPannelCmd[Iterm_CMD_TOTAL])(void)=
{
GUI_Sleep,
Writeflash,
Read,
ClearRecieveCount,
Servo_Debug,
CaliPose,
Run,
Stop,
ChangeIsAlwaysRun,
HighSpeed,
MiddleSpeed,
LowSpeed,
ChangeHouSensorIsUseful,
ChangeSerMid,
ChangeSerMid,
ChangeSerMid
};

char CMDNames[Iterm_CMD_TOTAL][ItermCMDNameLengthMax+1]=
{
"Sleep",
"Writef",
"Read",
"ClrRec",
"SerDeb",
"CaPose",
"Run",
"Stop",
"CgRun",
"HiSpd",
"MiSpd",
"LoSpd",
"HouSen",
"ChgMid",
"ChgMid",
"ChgMid"
};

char *CMDNames_[Iterm_CMD_TOTAL]=
{
"Sleep",
"Writef",
"Read",
"ClrRec",
"SerDeb",
"CaPose",
"Run",
"Stop",
"CgRun",
"HiSpd",
"MiSpd",
"LoSpd",
"HouSen",
"ChgMid",
"ChgMid",
"ChgMid"
};
