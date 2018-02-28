
#include "include.h"

DirectionType ShipDirection = Straight;
DirectionType ShipDirection_Pre = Straight;

FlagType MyFlag = {0};

void NewAnalysis(void)  //
{
	byte QianLeftWeightMax = 0,QianRightWeightMax = 0;
	byte HouLeftWeightMax = 0,HouRightWeightMax = 0;
	byte QianRecNumTotal = 0;
	//byte QianLeftWeightTotal = 0 ,QianRightWeightTotal = 0;
	
	QianRightWeightMax = ByteFindMax(QianRightSensor1.WeightNow,QianRightSensor2.WeightNow,QianRightSensor3.WeightNow,0);
	QianLeftWeightMax =  ByteFindMax(QianLeftSensor1.WeightNow,QianLeftSensor2.WeightNow,QianLeftSensor3.WeightNow,0);
	HouLeftWeightMax = MAX(HouLeftSensor1.WeightNow,HouLeftSensor2.WeightNow);
	HouRightWeightMax = MAX(HouRightSensor1.WeightNow,HouRightSensor2.WeightNow);
	
	SensorPara.QianLeftRecNum = GetQianLeftRecNum();
	SensorPara.QianRightRecNum = GetQianRightRecNum();
	QianRecNumTotal = SensorPara.QianLeftRecNum + SensorPara.QianRightRecNum;
	//QianRightWeightTotal = QianRightSensor1.WeightNow + QianRightSensor2.WeightNow + QianRightSensor3.WeightNow;
	//QianLeftWeightTotal = QianLeftSensor1.WeightNow + QianLeftSensor2.WeightNow + QianLeftSensor3.WeightNow;
	
  if(QianLeftWeightMax != 0 || QianRightWeightMax != 0)
	{
			if(QianLeftWeightMax > QianRightWeightMax)
			{
				ShipDirection = Left;
				if(QianRecNumTotal >= 5 )
					QianLeftWeightMax = QianLeftWeightMax - QianRightWeightMax;
			}
			else if(QianLeftWeightMax < QianRightWeightMax)
			{
				ShipDirection = Right;
				if(QianRecNumTotal >= 5 )
					QianRightWeightMax = QianRightWeightMax - QianLeftWeightMax;
			}
			else 
			{
				if(SensorPara.QianLeftRecNum > SensorPara.QianRightRecNum)     //防止反射
				{
					ShipDirection = Left;
					QianLeftWeightMax = (SensorPara.QianLeftRecNum - SensorPara.QianRightRecNum) * 16;
				}
				else if(SensorPara.QianLeftRecNum < SensorPara.QianRightRecNum) //防止反射
				{
					ShipDirection = Right;
					QianRightWeightMax = (SensorPara.QianRightRecNum - SensorPara.QianLeftRecNum) * 16;
				}
				else
					ShipDirection = Straight;
			}
			SensorPara.HasQianSensorRec = true;
	}
	else if(HouLeftWeightMax != 0 || HouRightWeightMax != 0)
	{
			if(SensorPara.HouSensorIsUseful == true)
			{
				if(HouLeftWeightMax > HouRightWeightMax)
					ShipDirection = Left;
				else if(HouLeftWeightMax < HouRightWeightMax)
					ShipDirection = Right;
				else
					ShipDirection = Straight;
			}
			else
			{
					ShipDirection = Straight;
			}
			SensorPara.HasQianSensorRec = false;
	}
	else
	{
			ShipDirection = Straight;
			SensorPara.HasQianSensorRec = true;
	}
	
	if(ShipDirection == Left)
	{
		SensorPara.LeftMaxWeight = SensorPara.HasQianSensorRec == true 
			? QianLeftWeightMax : HouLeftWeightMax;
		ServoPara.TurnGoalAngle = Yaw.ShowData - SensorPara.LeftMaxWeight * 15 * 15; //左右两边不对称，因为舵在船一边偏右 720/480 = 1.5
		if(ServoPara.TurnGoalAngle < -18000)
			ServoPara.TurnGoalAngle += 36000;
	}
  else if(ShipDirection == Right)
	{
		SensorPara.RightMaxWeight = SensorPara.HasQianSensorRec == true 
			? QianRightWeightMax : HouRightWeightMax;
		ServoPara.TurnGoalAngle = Yaw.ShowData + 
			SensorPara.RightMaxWeight * 15 * 10;//左右两边不对称，因为舵在船一边偏右
		if(ServoPara.TurnGoalAngle > 18000)
			ServoPara.TurnGoalAngle -= 36000;
	}
	else if(ShipDirection == Straight)
	{		
		ServoPara.TurnGoalAngle = Yaw.ShowData;
	}
	
	ShipDirection_Pre = ShipDirection;
	SensorParaClear(&SensorPara);
}











