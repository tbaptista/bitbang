/*
 * BitBang (http://www.bitbang.org)
 * Copyright (C) 2004-2008 Tiago Baptista
 *						   Telmo Menezes
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the version 2 of the GNU General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef _BBSCHEDULE_H_
#define _BBSCHEDULE_H_

#include <string>
#include <iostream>

#include "BBTypes.h"

using namespace std;

namespace bitbang
{
	
class BBWorldInterface;

/*!
 * \brief A schedule to be executed at a specified time or interval.
 *
 * This class defines an event that is executed once at a specified time or at
 * every time interval defined. This is just the base class that must be derived
 * as it contains a purely virtual method that must be implemtented in the child
 * class. That method is the Execute method that defines what to do at the
 * execution of the schedule.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2005-06-07
 *
 * \see Separate items with the '|' character.
 */
class BBSchedule
{
public:
	BBSchedule(BBTime start_time);
	BBSchedule(BBTime start_time, BBTime repeat_time);
	virtual ~BBSchedule();
	
	//Get/Set
	string GetName();
	void SetName(string str_new_val);
	BBTime GetStartTime(){return m_StartTime;};
	BBTime GetRepeatTime(){return m_RepeatTime;};
	bool IsRepeatable(){return m_bRepeat;};
	void StopRepeating(){m_bRepeat = false;};
	BBTime GetNextTime(){return m_NextTime;};
	bool GetOwnedByLib(){return m_bOwnedByLib;};
	void SetWorld(BBWorldInterface* p_world){m_pWorld = p_world;};
	
	bool Check(BBTime current_time);
	void ReSchedule();
	
	/*!
	 * \brief Purely virtual mehod that defines the execute procedure of the
	 *        schedule. 
	 *
	 */
	virtual void Execute() = 0;
	
protected:
	bool m_bOwnedByLib;
	BBWorldInterface* m_pWorld;
	
private:
	string m_strName;
	BBTime m_StartTime;
	BBTime m_RepeatTime;
	bool m_bRepeat;
	BBTime m_NextTime;
};
}
#endif //_BBSCHEDULE_H_
