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

#include "BBVisionReach3DCone.h"
#include "BBWorld.h"
#include <vector>
#include <math.h>

namespace bitbang
{

BBVisionReach3DCone::BBVisionReach3DCone()
{
	m_fVisionRange = 0;
	m_fVisionQuadRange = 0;
	m_fReach = 0;
	m_fQuadReach = 0;
	m_fVisionAngle = 0;

	m_ObjectListsVector.push_back(&m_VisionList);
	m_ObjectListsVector.push_back(&m_ReachList);
}
	
BBVisionReach3DCone::~BBVisionReach3DCone()
{
}
	
void BBVisionReach3DCone::Update(BBPoint& c_position, BBPoint& c_rotation)
{
	if (m_VisionList.size() != 0)
	{
		m_VisionList.clear();
	}

	if (m_ReachList.size() != 0)
	{
		m_ReachList.clear();
	}
	
	double dDegreesToRadians = 3.1415926535897932384626433832795f / 180.0f;

	bool bRotationMatrixInitialized = false;
	//double rotationMatrix0;
	//double rotationMatrix1;
	//double rotationMatrix2;
	//double rotationMatrix3;
	//double rotationMatrix4;
	//double rotationMatrix5;
	double rotationMatrix6;
	double rotationMatrix7;
	double rotationMatrix8;
	
	double dMinDistance = 9999999.9f;
		
	BBObjectMap::iterator iObject;
	BBObjectMap* pObjectMap = m_pWorld->GetObjectMap();
	for (iObject = pObjectMap->begin(); iObject != pObjectMap->end(); iObject++)
	{
		BBObject* pObj = iObject->second;

		if (pObj->GetID() != m_nOwnerID)
		{		
			double dx= pObj->GetX() - c_position.GetX();
			double dx2 = dx * dx;
		
			if (dx2 > m_fVisionQuadRange)
			{
				continue;
			}		
		
			double dy= pObj->GetY() - c_position.GetY();
			double dy2 = dy * dy;
		
			if (dy2 > m_fVisionQuadRange)
			{
				continue;
			}
		
			double dz= pObj->GetZ() - c_position.GetZ();
			double dz2 = dz * dz;
		
			if (dz2 > m_fVisionQuadRange)
			{
				continue;
			}
		
			double d = dx2 + dy2 + dz2;
		
			if (d < m_fVisionQuadRange)
			{
				// Object in range
				
				if (!bRotationMatrixInitialized)
				{
					double dAngleX = c_rotation.GetX() * dDegreesToRadians;
					double dAngleY = c_rotation.GetY() * dDegreesToRadians;
					double dAngleZ = c_rotation.GetZ() * dDegreesToRadians;
								
					double cr = cos(dAngleX);
					double sr = sin(dAngleX);
					double cp = cos(dAngleY);
					double sp = sin(dAngleY);
					double cy = cos(dAngleZ);
					double sy = sin(dAngleZ);

					//rotationMatrix0 = cp * cy;
					//rotationMatrix1 = cp * sy;
					//rotationMatrix2 = -sp;

					//double srsp = sr * sp;
					double crsp = cr * sp;

					//rotationMatrix3 = srsp * cy - cr * sy;
					//rotationMatrix4 = srsp * sy + cr * cy;
					//rotationMatrix5 = sr * cp;

					rotationMatrix6 = crsp * cy + sr * sy;
					rotationMatrix7 = crsp * sy - sr * cy;
					rotationMatrix8 = cr * cp;
					
					bRotationMatrixInitialized = true;
				}
				
				//double dPosVecX = (rotationMatrix0 * dx) + (rotationMatrix1 * dy) + (rotationMatrix2 * dz);
				//double dPosVecY = (rotationMatrix3 * dx) + (rotationMatrix4 * dy) + (rotationMatrix5 * dz);
				double dPosVecZ = (rotationMatrix6 * dx) + (rotationMatrix7 * dy) + (rotationMatrix8 * dz);				
				
				// Calculate length of object position vector
				// Using value before rotation for optimization purposes
				double dPosVecLength = sqrt(d);
				
				// Calculate angle with Z axis
				double dAngle = acos(dPosVecZ / dPosVecLength);
				
				//printf("x1: %f; y1: %f; z1: %f\n", dPosVecX, dPosVecY, dPosVecZ);
				//printf("angle: %f\n", dAngle);
				
				// Calculate half vision angle
				double dHalfAng = m_fVisionAngle * dDegreesToRadians / 2.0f;
			
				// Test vision field
				if (dAngle < dHalfAng)
				{
					m_VisionList.push_back(pObj->GetID());
					//printf("id visible: %d\n", pObj->GetID());

					//test reach
					if (m_fReach != 0)
					{
						if (d < m_fQuadReach)
						{
							if (d < dMinDistance)							
							{
								dMinDistance = d;
							}
							
							m_ReachList.push_back(pObj->GetID());
						}
					}
				}
			}
		}
	
		//PrintVisionList();
		//PrintReachList();
        }
}

/*!
 * \brief Test if a object is reachable.
 * 
 * \param int id of object to test.
 * 
 * \return bool true if reachable, false otherwise
 *
 */
bool BBVisionReach3DCone::IsReachable(int n_object_id)
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
int BBVisionReach3DCone::GetReachableObjectByType(int n_type)
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
void BBVisionReach3DCone::SetReach(float f_reach)
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
void BBVisionReach3DCone::SetVisionRange(float f_range)
{
	m_fVisionRange = f_range;
	m_fVisionQuadRange = f_range * f_range;
}

/*!
 * \brief Set vision angle.
 *
 * \param f_angle The angle.
 *
 */
void BBVisionReach3DCone::SetVisionAngle(float f_angle)
{
	m_fVisionAngle = f_angle;
}

/*!
 * \brief Get vision range.
 *
 * \return The vision range
 *
 */
float BBVisionReach3DCone::GetVisionRange()
{
	return m_fVisionRange;
}

/*!
 * \brief Get the vision angle.
 *
 * \return The vision angle
 *
 */
float BBVisionReach3DCone::GetVisionAngle()
{
	return m_fVisionAngle;
}

/*!
 * \brief Prints vision list to console.
 */
void BBVisionReach3DCone::PrintVisionList()
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
void BBVisionReach3DCone::PrintReachList()
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

