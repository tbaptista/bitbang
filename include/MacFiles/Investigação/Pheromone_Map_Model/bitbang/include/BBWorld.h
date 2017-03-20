/*
 * BitBang (http://www.bitbang.org)
 * Copyright (C) 2004-2009 Tiago Baptista
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
#if !defined(EA_CF604AD1_52E2_4686_9F32_878BAB8EDB60__INCLUDED_)
#define EA_CF604AD1_52E2_4686_9F32_878BAB8EDB60__INCLUDED_

#include <list>
#include <map>
#include <vector>
#include <string>

using namespace std;

#include "BBWorldInterface.h"
#include "BBTypes.h"
#include "BBTimer.h"
#include "BBCSVFileLog.h"

namespace bitbang
{
class BBSchedule;
class BBObject;
class BBCSVFileLog;
typedef list<BBSchedule*> BBScheduleList;
typedef map<int, BBObject*> BBObjectMap;

/*!
 * \brief The Bit Bang world.
 *
 * This class represents the Bit Bang world. All supra-agent definitions and
 * functionality are defined here.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2005-06-08
 *
 */
class BBWorld : public BBWorldInterface
{
public:
	BBWorld();
	virtual ~BBWorld();
	
	virtual void RegisterObject(BBObject& object);
	virtual void RemoveObject(int n_id);
	void RemoveDeadAgents();
	virtual BBObject* GetObject(int n_id);
	void AddSchedule(BBSchedule* p_schedule);
	void Scheduler();
	void ProcessAgents();
	BBObjectMap* GetObjectMap();
	void SetThinkProbability(int n_probabilty){m_nThinkProbability = n_probabilty;};
	bool IsPaused(){return m_Timer.IsPaused();};
	virtual void Pause();
	virtual void Resume();
	/*!
	 * \brief Sets real time / computational time mode.
	 *
	 * \param b_real_time true = real time, false = computational time
	 *
	 */
	void SetRealTime(bool b_real_time){m_Timer.SetRealTime(b_real_time);};
	bool GetRealTime(){return m_Timer.GetRealTime();};
	BBTime GetTime(){return m_Timer.GetTime();};
	virtual void LogDynamicStats() {};
	
protected:
	void UpdateObjects();
	
	BBObjectMap m_ObjectMap;
	BBObjectIDList m_DeadAgentsList;
	BBScheduleList m_ScheduleList;
	BBTimer m_Timer;
	int m_nThinkProbability;
	BBCSVFileLog m_WorldDynamicLog;
};
}
#endif // !defined(EA_CF604AD1_52E2_4686_9F32_878BAB8EDB60__INCLUDED_)
