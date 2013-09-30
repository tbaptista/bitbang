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
#include "BBScheduleScriptable.h"
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
BBScheduleScriptable::BBScheduleScriptable(BBTime start_time) : BBSchedule(start_time)
{
	m_bOwnedByLib = false;
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
BBScheduleScriptable::BBScheduleScriptable(BBTime start_time, BBTime repeat_time) : BBSchedule(start_time, repeat_time)
{
	m_bOwnedByLib = false;
}


/*!
 * \brief Destructor
 *
 */
BBScheduleScriptable::~BBScheduleScriptable()
{
}

}
