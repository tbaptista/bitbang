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
#ifndef _BBSCHEDULESCRIPTABLE_H_
#define _BBSCHEDULESCRIPTABLE_H_

#include "BBSchedule.h"

namespace bitbang
{

/*!
 * \brief This class implements a scriptable schedule.
 *
 * This schedule can be used in scripting, implementing the execute function to 
 * a script function.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2005-06-08
 *
 * \see BBSchedule
 */
class BBScheduleScriptable : public BBSchedule
{
public:
	BBScheduleScriptable(BBTime start_time);
	BBScheduleScriptable(BBTime start_time, BBTime repeat_time);
	virtual ~BBScheduleScriptable();
	virtual void Execute(){};
};

}
#endif //_BBSCHEDULESCRIPTABLE_H_
