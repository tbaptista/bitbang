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
#include "BBSchedule.h"
#include "BBWorld.h"

namespace bitbang
{

/*!
 * \brief Constructor.
 *
 * This version of the constructor takes only the start time. This way the
 * schedule will be executed only once at that time. 
 *
 * \param start_time The time to execute the schedule.
 */
BBSchedule::BBSchedule(BBTime start_time)
{
	m_StartTime = start_time;
	m_RepeatTime = 0;
	m_bRepeat = false;
	m_NextTime = start_time;
	m_bOwnedByLib = true;
	m_pWorld = NULL;
}

/*!
 * \brief Constructor.
 *
 * This version of the constructor takes two times, the start time and the
 * repeat time. This will make a schedule execute the first time at start time
 * and than every time the repeat time passes. 
 *
 * \param start_time The time to execute the first time.
 * \param repeat_time The time interval between executions.
 */
BBSchedule::BBSchedule(BBTime start_time, BBTime repeat_time)
{
	m_StartTime = start_time;
	m_RepeatTime = repeat_time;
	m_bRepeat = true;
	m_NextTime = start_time;
	m_bOwnedByLib = true;
	m_pWorld = NULL;
}

/*!
 * \brief Destructor
 *
 */
BBSchedule::~BBSchedule()
{
}

/*!
 * \brief Get the name of the schedule.
 *
 * \return The name of this schedule.
 *
 */
string BBSchedule::GetName()
{
	return m_strName;
}

/*!
 * \brief Set the name of the schedule.
 *
 * \param str_new_val The new name for the schedule.
 *
 */
void BBSchedule::SetName(string str_new_val)
{
	m_strName = str_new_val;
}

/*!
 * \brief Check if the schedule should execute.
 *
 * Call this method with the current time to check if the schedule should
 * execute.
 *
 * \param current_time The current time.
 * \return True if the schedule should execute, false otherwise.
 *
 */
bool BBSchedule::Check(BBTime current_time)
{
	if (current_time >= m_NextTime)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*!
 * \brief Set the next execution of the schedule.
 *
 * This method will set the next time the schedule should execute for repetable
 * schedules.
 *
 */
void BBSchedule::ReSchedule()
{
	if (m_bRepeat)
	{
		m_NextTime = m_NextTime + m_RepeatTime;
	}
}

}
