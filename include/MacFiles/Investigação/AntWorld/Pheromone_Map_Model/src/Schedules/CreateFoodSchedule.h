/*!
 * 
 * Copyright (c) 2004-2008 by Tiago Baptista. All rights reserved.
 */

#ifndef CREATEFOODSCHEDULE_H_
#define CREATEFOODSCHEDULE_H_

#include "BBSchedule.h"

using namespace bitbang;

class CreateFoodSchedule : public BBSchedule
{
public:
	CreateFoodSchedule(BBTime start_time);
	CreateFoodSchedule(BBTime start_time, BBTime repeat_time);
	virtual ~CreateFoodSchedule();
	
	virtual void Execute();
};


#endif //CREATEAGENTSSCHEDULE_H_
