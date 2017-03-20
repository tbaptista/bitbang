/*!
 * 
 * Copyright (c) 2004-2009 by Telmo Menezes and Tiago Baptista. All rights reserved.
 */

#ifndef BBLOGSCHEDULE_H_
#define BBLOGSCHEDULE_H_

#include "BBSchedule.h"
#include "BBTypes.h"


namespace bitbang
{

class BBLogSchedule : public BBSchedule
{
public:
	BBLogSchedule(BBTime start_time);
	BBLogSchedule(BBTime start_time, BBTime repeat_time);
	virtual ~BBLogSchedule();
	
	virtual void Execute();
};
}

#endif //BBLOGSCHEDULE_H_
