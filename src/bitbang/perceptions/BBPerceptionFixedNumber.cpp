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

#include "BBPerceptionFixedNumber.h"
#include <stdio.h>


namespace bitbang
{
/*!
 * \brief Constructor
 *
 * This constructor receives the fixed value that this perception will have.
 *
 * \param d_value The value to assign to this perception.
 *
 */
BBPerceptionFixedNumber::BBPerceptionFixedNumber(double d_value)
{
	m_dValue = d_value;
	m_strName = HumanReadable();
}

/*!
 * \brief
 * Destructor
 * 
 */
BBPerceptionFixedNumber::~BBPerceptionFixedNumber()
{
}

/*!
 * Creates a new perception with the same value as this one.
 *
 * \return Pointer to the new perception created.
 *
 */
BBPerception* BBPerceptionFixedNumber::Clone()
{
	BBPerceptionFixedNumber* pNewPerception = new BBPerceptionFixedNumber(m_dValue);
	return pNewPerception;
}

/*!
 * \brief Updates the current value of this perception.
 * 
 * \param c_agent Interface instance of the owner agent.
 * 
 * This method overrides the abstract Update() method of the parent object 
 * (BBPerceptionNumber). This is a null method, as this is a fixed perception.
 *
 */
void BBPerceptionFixedNumber::Update(BBObject& c_agent)
{
}

}
