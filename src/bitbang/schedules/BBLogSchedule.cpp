/*!
 * 
 * Copyright (c) 2004-2009 by Telmo Menezes and Tiago Baptista. All rights reserved.
 */

#include "BBLogSchedule.h"
#include "BBWorldInterface.h"

namespace bitbang
{

BBLogSchedule::BBLogSchedule(BBTime start_time) : BBSchedule(start_time)
{
	//This schedule is not supposed to be run only once!
	cerr << "Error: BBLogSchedule is not supposed to run only once." << endl;
}

BBLogSchedule::BBLogSchedule(BBTime start_time, BBTime repeat_time) : BBSchedule (start_time, repeat_time)
{

}

BBLogSchedule::~BBLogSchedule()
{
}

void BBLogSchedule::Execute()
{
	m_pWorld->LogDynamicStats();
}
	
}

