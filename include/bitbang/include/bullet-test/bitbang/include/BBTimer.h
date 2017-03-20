/*
 * BitBang (http://www.bitbang.org)
 * Copyright (C) 2004-2008 Tiago Baptista
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

#ifndef _BBTIMER_H
#define _BBTIMER_H

#include "BBTypes.h"

namespace bitbang
{
class BBTimer
{
public:
	BBTimer();
	virtual ~BBTimer();
	
	void UpdateTime();
	void Resume();
	/*!
	 * \brief Pause the timer.
	 *
	 * UpdateTime can still be called (and should be called) that time will
	 * not advance.
	 *
	 */
	void Pause(){m_bPaused = true;};
	/*!
	 * \brief Set the time multiplier.
	 *
	 * Sets the multiplier used to convert from actual time to simulation time. The
	 * actual time is counted in seconds. A multiplier of 1 means that for every
	 * actual second the simulation counts also one time unit. A multiplier of 60
	 * would mean that for every actual second 60 time units would pass in the
	 * simulation.
	 *
	 * \param f_time_multiplier The time multiplier.
	 *
	 */
	void SetTimeMultiplier(float f_time_multiplier){m_fTimeMultiplier = f_time_multiplier;};
	/*!
	 * \brief Set the time step.
	 *
	 * This method is used to set the step size used to advance time when
	 * the timer is set the computational time mode of operation.
	 *
	 * \seealso BBTimer::SetRealTime()
	 *
	 */
	void SetComputationalTimeDelta(BBTime delta){m_ComputationalTimeDelta = delta;};
	/*!
	 * \brief Set the timer to run in real or computational time.
	 *
	 * The timer can be used in two different modes of operation: real time
	 * and computational time. In real time, the time is synchronised to
	 * the actual time provided by the OS. In this mode, each time step will
	 * be bigger or smaller depending on the time elapsed between calls to
	 * UpdateTime. In the computational time mode of operation, the time
	 * step is fixed.
	 *
	 * \param b_real_time True to set the timer to real time, false to set
	 *					  it to computational time.
	 *
	 * \seealso BBTimer::SetComputationalTimeDelta()
	 */
	void SetRealTime(bool b_real_time){m_bRealTime = b_real_time;};
	/*!
	 * \brief Get the mode of operation of the timer.
	 *
	 * \return True if the timer is running in real time, false if it is
	 *	       running in computational time.
	 *
	 * \seealso BBTimer::SetRealTime()
	 *
	 */
	bool GetRealTime(){return m_bRealTime;};
	/*!
	 * \brief Get the current time.
	 *
	 * \return The current time.
	 *
	 */
	BBTime GetTime(){return m_Time;};
	/*!
	 * \brief Get the running state of the timer.
	 *
	 * \return True if the timer is paused, false otherwise.
	 *
	 */
	bool IsPaused(){return m_bPaused;};
	
private:
	BBTime m_Time;
	BBTime m_ComputationalTimeDelta;
	float m_fTimeMultiplier;
	BBTime m_LastUpdateTime;
	bool m_bRealTime;
	bool m_bPaused;
};
}

#endif //_BBTIMER_H
