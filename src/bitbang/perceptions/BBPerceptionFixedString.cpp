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

#include "BBPerceptionFixedString.h"

namespace bitbang
{
	
	/*!
	 * \brief Constructor
	 *
	 * This constructor receives the fixed value that this perception will have.
	 *
	 * \param str_value The value to assign to this perception.
	 *
	 */
	BBPerceptionFixedString::BBPerceptionFixedString(string str_value)
	{
		m_strValue = str_value;
		m_strName = str_value;
	}
	
	/*!
	 * \brief
	 * Destructor
	 * 
	 */
	BBPerceptionFixedString::~BBPerceptionFixedString()
	{
	}
	
	/*!
	 * Creates a new perception with the same value as this one.
	 *
	 * \return Pointer to the new perception created.
	 *
	 */
	BBPerception* BBPerceptionFixedString::Clone()
	{
		BBPerceptionFixedString* pNewPerception = new BBPerceptionFixedString(m_strValue);
		return pNewPerception;
	}
	
	/*!
	 * \brief Updates the current value of this perception.
	 *
	 * This method overrides the abstract Update() method of the parent object 
	 * (BBPerceptionNumber). This is a null method, as this is a fixed perception.
	 * 
	 * \param c_agent Interface instance of the owner agent.
	 *
	 */
	void BBPerceptionFixedString::Update(BBObject& c_agent)
	{
	}
	
}
