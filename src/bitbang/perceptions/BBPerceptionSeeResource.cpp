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
#include "BBPerceptionSeeResource.h"
#include "BBPerceptionSphere.h"
#include "BBObject.h"
#include "BBWorld.h"
#include "BBObject.h"

namespace bitbang
{

/*!
 * \brief
 * Constructor
 * 
 * Constructor with no paramenters.
 *
 */
BBPerceptionSeeResource::BBPerceptionSeeResource()
{
	m_strName = "Seeing Resource";
}

/*!
 * \brief
 * Destructor
 * 
 */
BBPerceptionSeeResource::~BBPerceptionSeeResource()
{
}

BBPerception* BBPerceptionSeeResource::Clone()
{
	return new BBPerceptionSeeResource();
}

/*!
 * \brief
 * Updates the current value of this perception.
 * 
 * \param c_agent Interface instance of the owner agent.
 * \return nothing
 * 
 * This method overrides the abstract Update() method of the parent object 
 * (BBPerception) and updated the current value of the perception for the 
 * specific case of BBPerceptionSeeResource. This method gets called by
 * the owner agent Think() method before executing its cognition process.
 *
 * \see
 * BBObject::Think()
 *
 */
void BBPerceptionSeeResource::Update(BBObject& c_agent)
{
	
	BBObject* pObject;
	BBObjectIDList& VisionList = c_agent.GetPerceptionSphere(0).GetObjectList(0);
	BBObjectIDList::iterator iID;
	m_bValue = false;
	
	for (iID = VisionList.begin(); !m_bValue && (iID != VisionList.end()); iID++)
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
