#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_

#include "include.h"

typedef enum
{
    Left = 1,	  
	  Straight = 0,
	  Right = -1
}DirectionType;

typedef struct
{
    byte Final;
}FlagType;

extern DirectionType ShipDirection;

void NewAnalysis(void);

#endif

