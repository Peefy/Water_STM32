
#include "include.h"

DirectionType ShipDirection = Straight;
DirectionType ShipDirection_Pre = Straight;

FlagType MyFlag = {0};

void NewAnalysis(void)  //
{
	byte QianLeftWeightMax = 0,QianRightWeightMax = 0;
	byte HouLeftWeightMax = 0,HouRightWeightMax = 0;
	
//	byte QianLeftWeightTotal = 0 ,QianRightWeightTotal = 0;
	
	QianRightWeightMax = ByteFindMax(QianRightSensor1.WeightNow,QianRightSensor2.WeightNow,QianRightSensor3.WeightNow,0);
	QianLeftWeightMax =  ByteFindMax(QianLeftSensor1.WeightNow,QianLeftSensor2.WeightNow,QianLeftSensor3.WeightNow,0);
	HouLeftWeightMax = MAX(HouLeftSensor1.WeightNow,HouLeftSensor2.WeightNow);
	HouRightWeightMax = MAX(HouRightSensor1.WeightNow,HouRightSensor2.WeightNow);
	
	//QianRightWeightTotal = QianRightSensor1.WeightNow + QianRightSensor2.WeightNow + QianRightSensor3.WeightNow;
	//QianLeftWeightTotal = QianLeftSensor1.WeightNow + QianLeftSensor2.WeightNow + QianLeftSensor3.WeightNow;
	
  if(QianLeftWeightMax != 0 || QianRightWeightMax != 0)
	{
			if(QianLeftWeightMax > QianRightWeightMax)
				ShipDirection = Left;
			else if(QianLeftWeightMax < QianRightWeightMax)
				ShipDirection = Right;
			else
				ShipDirection = Straight;
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
		SensorPara.LeftMaxWeight = SensorPara.HasQianSensorRec == true ? QianLeftWeightMax : HouLeftWeightMax;
		ServoPara.TurnGoalAngle = Yaw.ShowData - SensorPara.LeftMaxWeight * 15 * 15; //左右两边不对称，因为舵在船一边偏右
		if(ServoPara.TurnGoalAngle < -18000)
			ServoPara.TurnGoalAngle += 36000;
	}
  else if(ShipDirection == Right)
	{
		SensorPara.RightMaxWeight = SensorPara.HasQianSensorRec == true ? QianRightWeightMax : HouRightWeightMax;
		ServoPara.TurnGoalAngle = Yaw.ShowData + SensorPara.RightMaxWeight * 15 * 10;//左右两边不对称，因为舵在船一边偏右
		if(ServoPara.TurnGoalAngle > 18000)
			ServoPara.TurnGoalAngle -= 36000;
	}
	else if(ShipDirection == Straight)
	{
		
		ServoPara.TurnGoalAngle = Yaw.ShowData;
	}
	
	ShipDirection_Pre = ShipDirection;
	SensorPara.LeftWeightTotal = 0;
  SensorPara.RightWeightTotal = 0;	
	SensorPara.RightMaxWeight = 0;
	SensorPara.LeftMaxWeight = 0;
}











