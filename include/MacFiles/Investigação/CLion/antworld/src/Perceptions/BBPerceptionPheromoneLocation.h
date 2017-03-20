/*!
 * Copyright (c) 2009 by Tiago Baptista. All rights reserved.
 */

#ifndef _BBPERCEPTIONPHEROMONELOCATION_H
#define _BBPERCEPTIONPHEROMONELOCATION_H

#include "perceptions/BBPerceptionNumber.h"

using namespace bitbang;


class BBPerceptionPheromoneLocation : public BBPerceptionNumber
{
public:
	BBPerceptionPheromoneLocation(void);
	virtual ~BBPerceptionPheromoneLocation(void);
	virtual BBPerception* Clone();
	virtual void Update(BBObject& c_agent);
};

#endif //_BBPERCEPTIONPHEROMONELOCATION_H
