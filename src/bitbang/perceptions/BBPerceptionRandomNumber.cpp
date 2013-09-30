/*
 * BitBang (http://www.bitbang.org)
 * Copyright (C) 2004-2011 Tiago Baptista
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

#include "BBPerceptionRandomNumber.h"
#include "BBRandomGenerator.h"
#include <stdlib.h>

namespace bitbang
{
	BBPerceptionRandomNumber::BBPerceptionRandomNumber()
	{
		m_bInt = true;
		m_strName = "Random Number";
		m_dValue = g_RandomGenerator.RandInt((int)m_dRange);
	}
	
	BBPerceptionRandomNumber::BBPerceptionRandomNumber(int n_range)
	{
		m_bInt = true;
		m_strName = "Random Number";
		m_dRange = n_range;
		m_dValue = g_RandomGenerator.RandInt(n_range);
	}
	
	BBPerceptionRandomNumber::~BBPerceptionRandomNumber()
	{
	}
	
	BBPerception* BBPerceptionRandomNumber::Clone()
	{
		return new BBPerceptionRandomNumber(m_dRange);
	}
	
	void BBPerceptionRandomNumber::Update(BBObject& c_agent)
	{
		m_dValue = g_RandomGenerator.RandInt((int)m_dRange);
	}
}

