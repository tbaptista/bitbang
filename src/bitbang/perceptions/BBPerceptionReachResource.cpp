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

#include "BBPerceptionReachResource.h"
#include "BBObject.h"
#include "BBPerceptionSphere.h"

namespace bitbang
{

/*!
 * \brief
 * Constructor
 * 
 * Constructor with no paramenters.
 *
 */
BBPerceptionReachResource::BBPerceptionReachResource()
{
	m_strName = "Reaching Resource";
}

/*!
 * \brief
 * Destructor
 * 
 */
BBPerceptionReachResource::~BBPerceptionReachResource()
{
}

BBPerception* BBPerceptionReachResource::Clone()
{
	return new BBPerceptionReachResource();
}

/*!
 * \brief
 * Updates the current value of this perception.
 * 
 * \param c_agent Interface instance of the owner agent.
 * 
 * This method overrides the abstract Update() method of the parent object 
 * (BBPerception) and updated the current value of the perception for the 
 * specific case of BBPerceptionReachResource. This method gets called by
 * the owner agent Think() method before executing its cognition process.
 *
 * \see
 * BBObject::Think()
 *
 */
void BBPerceptionReachResource::Update(BBObject& c_agent)
{	
	BBObject* pObject;
	
	BBObjectIDList& ReachList = c_agent.GetPerceptionSphere(0).GetObjectList(1);
	BBObjectIDList::iterator iID;
	m_bValue = false;

	for (iID = ReachList.begin(); !m_bValue && (iID != ReachList.end()); iID++)
	{
		pObject = c_agent.GetPerceptionSphere(0).GetObject(*iID);
		if (pObject != NULL)
		{
			if (pObject->IsType(BBObject::TYPE_THING))
			{
				m_bValue = true;
			}
		}
	}
}


}

