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
#include "BBPerception.h"

namespace bitbang
{

const int BBPerception::nTYPEBOOLEAN = 0;
const int BBPerception::nTYPENUMBER = 1;
const int BBPerception::nTYPESTRING = 2;
	
/*!
 * \brief Constructor.
 *
 * The default constructor sets the name of the perception to "unnamed".
 *
 */
BBPerception::BBPerception()
{
	m_nOpCount = 0;
	m_strName = "unnamed";
	m_nType = -1;
	m_bOwnedByList = false;
    m_bModifiedByNonTerminalActions = false;
}


/*!
 * \brief Destructor.
 *
 */
BBPerception::~BBPerception()
{

}

/*!
 * \brief Check if this perception is of a given type
 *
 * \param n_type The type to check.
 * \return True if the type matches, false otherwise.
 *
 */
bool BBPerception::IsType(int n_type)
{
	if (m_nType == n_type)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*!
 * \brief Get the operator count for the perception.
 *
 * \return The number of operators available for this perception.
 *
 */
int BBPerception::GetOpCount()
{
	return m_nOpCount;
}

/*!
 * \brief Set the name of the perception.
 *
 * \param str_name The name to apply.
 *
 */
void BBPerception::SetName(string str_name)
{
	m_strName = str_name;
}

/*!
 * \brief Get the name of the perception.
 *
 * \return The name of this perception.
 *
 */
string BBPerception::GetName()
{
	return m_strName;
}

}
