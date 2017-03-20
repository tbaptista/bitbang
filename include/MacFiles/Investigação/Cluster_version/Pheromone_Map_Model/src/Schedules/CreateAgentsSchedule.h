/*!
 * 
 * Copyright (c) 2004-2006 by Telmo Menezes and Tiago Baptista. All rights reserved.
 */

#ifndef CREATEAGENTSSCHEDULE_H_
#define CREATEAGENTSSCHEDULE_H_

#include "BBSchedule.h"

using namespace bitbang;


class CreateAgentsSchedule : public BBSchedule
{
public:
	CreateAgentsSchedule(BBTime start_time);
	CreateAgentsSchedule(BBTime start_time, BBTime repeat_time);
	virtual ~CreateAgentsSchedule();
	
	virtual void Execute();
};
	


#endif //CREATEAGENTSSCHEDULE_H_

