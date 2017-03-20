/*!
 * 
 * Copyright (c) 2009 by Tiago Baptista. All rights reserved.
 */

#ifndef PHEROMONESCHEDULE_H_
#define PHEROMONESCHEDULE_H_

#include "BBSchedule.h"

using namespace bitbang;

class PheromoneSchedule : public BBSchedule
{
public:
	PheromoneSchedule(BBTime start_time);
	PheromoneSchedule(BBTime start_time, BBTime repeat_time);
	virtual ~PheromoneSchedule();
	
	virtual void Execute();
};


#endif //CREATEAGENTSSCHEDULE_H_
