#ifndef _POSE_H_
#define _POSE_H_

#include "include.h"

#define POSE_EN 1

typedef struct
{
  int16 InitData;
	int16 ShowData;
  int16 Offset;
}AngleType;

#define AngleMAX 180
#define AngleMIN -180

extern AngleType Yaw,Roll,Pitch;

void AutoAngle(void);
void PoseGet(void);
void CaliPose(void);
void CaliPoseButNotYaw(void);

#endif
