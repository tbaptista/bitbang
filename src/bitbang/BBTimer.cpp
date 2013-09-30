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

#include "BBTimer.h"
#include "BBOS.h"

namespace bitbang
{

	/*!
	 * \brief BBTimer constructor.
	 *
	 */
	BBTimer::BBTimer()
	{
		m_Time = 0;
		m_ComputationalTimeDelta = 0.01;
		m_fTimeMultiplier = 1;
		m_bRealTime = true;
		m_LastUpdateTime = BBOS::GetTime();
		m_bPaused = false;
	}
	
	BBTimer::~BBTimer()
	{		
	}
	
	/*!
	 * \brief Resume the timer.
	 *
	 * Call this method to start the timer after creation, as on contruction it
	 * is stopped. Also use this method to resume after it was paused.
	 *
	 */
	void BBTimer::Resume()
	{
		if (m_LastUpdateTime == 0)
		{
			m_LastUpdateTime = BBOS::GetTime();
		}
		
		m_bPaused = false;
	}
	
	/*!
	 * \brief Advance the timer.
	 *
	 * This method must be called by the simulation main loop to keep the time
	 * updated. Even if the simulation is paused, this method should be called.
	 *
	 */
	void BBTimer::UpdateTime()
	{
		BBTime CurTime = BBOS::GetTime();
		
		if (!m_bPaused)
		{
			if (m_bRealTime)
			{
				m_Time = m_Time + ((CurTime - m_LastUpdateTime) * m_fTimeMultiplier);
			}
			else
			{
				m_Time += m_ComputationalTimeDelta;
			}
		}
		
		m_LastUpdateTime = CurTime;
	}
	
}

