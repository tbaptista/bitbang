/*
 * BitBang (http://www.bitbang.org)
 * Copyright (C) 2009 Tiago Baptista
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

#include "BBVisionReach2DCircle.h"
#include "BBWorld.h"
#include <vector>
#include <math.h>

namespace bitbang
{

BBVisionReach2DCircle::BBVisionReach2DCircle()
{
	m_fVisionRange = 0;
	m_fVisionQuadRange = 0;
	m_fReach = 0;
	m_fQuadReach = 0;

	m_ObjectListsVector.push_back(&m_VisionList);
	m_ObjectListsVector.push_back(&m_ReachList);
}
	
BBVisionReach2DCircle::~BBVisionReach2DCircle()
{
}
	
void BBVisionReach2DCircle::Update(BBPoint& c_position, BBPoint& c_rotation)
{
	if (m_VisionList.size() != 0)
	{
		m_VisionList.clear();
	}
	
	if (m_ReachList.size() != 0)
	{
		m_ReachList.clear();
	}
	
	BBObjectMap::iterator iObject;
	BBObjectMap* pObjectMap = m_pWorld->GetObjectMap();
	for (iObject = pObjectMap->begin(); iObject != pObjectMap->end(); iObject++)
	{
		BBObject* pObj = iObject->second;
		
		if (pObj->GetID() != m_nOwnerID)
		{		
			double dx= pObj->GetX() - c_position.GetX();
			double dx2 = dx * dx;
			
			if (dx2 < m_fVisionQuadRange)
			{
				double dz= pObj->GetZ() - c_position.GetZ();
				double dz2 = dz * dz;
				
				if (dz2 < m_fVisionQuadRange)
				{
					double d2 = dx2 + dz2;
					
					if (d2 < m_fVisionQuadRange)
					{
						// Object in range
						m_VisionList.push_back(pObj->GetID());
						
						
						//test reach
						if (m_fReach != 0)
						{
							if (d2 < m_fQuadReach)
							{
								m_ReachList.push_back(pObj->GetID());
							}
						}
					}
				}
			}
		}
	}
	
	//PrintVisionList();
	//PrintReachList();
}

/*!
 * \brief Test if a object is reachable.
 * 
 * \param int id of object to test.
 * 
 * \return bool true if reachable, false otherwise
 *
 */
bool BBVisionReach2DCircle::IsReachable(int n_object_id)
{
		
	BBObjectIDList::iterator iObject;

	for (iObject = m_ReachList.begin(); iObject != m_ReachList.end(); iObject++)
	{				
		if ((*iObject) == n_object_id)
		{
			return true;
		}
	}

	return false;
}

/*!
 * \brief Get an object that can be reached and is of the specified
 *        type.
 *
 * Returns the first object of the specified type from the list of objects
 * that can be reached.
 *
 * \param n_type The type of object to return.
 * \return The ID of the object or -1 if no object of that type was found.
 *
 */
int BBVisionReach2DCircle::GetReachableObjectByType(int n_type)
{
	BBObjectIDList::iterator iID;
	for (iID = m_ReachList.begin(); iID != m_ReachList.end(); iID++)
	{
		BBObject* pObj = m_pWorld->GetObject(*iID);
		
		if ((pObj != NULL) && (pObj->IsType(n_type)))
		{
			return *iID;
		}
	}
	
	return -1;
}

/*!
 * \brief Set reach
 *
 * Distance threshold for an object to be considered reachable.
 *
 * \param f_reach The reach.
 *
 */
void BBVisionReach2DCircle::SetReach(float f_reach)
{
	m_fReach = f_reach;
	m_fQuadReach = f_reach * f_reach;
}

/*!
 * \brief Set vision range. 
 *
 * The vision range determines how far other objects can be 
 * seen.
 *
 * \param f_range The range.
 *
 */
void BBVisionReach2DCircle::SetVisionRange(float f_range)
{
	m_fVisionRange = f_range;
	m_fVisionQuadRange = f_range * f_range;
}

/*!
 * \brief Get vision range.
 *
 * \return The vision range
 *
 */
float BBVisionReach2DCircle::GetVisionRange()
{
	return m_fVisionRange;
}

/*!
 * \brief Prints vision list to console.
 */
void BBVisionReach2DCircle::PrintVisionList()
{

	printf("Vision List: ");
		
	BBObjectIDList::iterator iID;
	for (iID = m_VisionList.begin(); iID != m_VisionList.end(); iID++)
	{				
		int nID = *iID;
		
		printf(" %d ", nID);
	}
	
	printf("\n");
}

/*!
 * \brief Prints reach list to console.
 */
void BBVisionReach2DCircle::PrintReachList()
{
	
	printf("Reach List: ");
		
	BBObjectIDList::iterator iID;
	for (iID = m_ReachList.begin(); iID != m_ReachList.end(); iID++)
	{				
		int nID = *iID;
		
		printf(" %d ", nID);
	}
	
	printf("\n");
}

}

