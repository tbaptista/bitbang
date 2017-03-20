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

#ifndef _BBVISIONREACH3DCONE_H
#define _BBVISIONREACH3DCONE_H

#include "BBTypes.h"
#include "BBPerceptionSphere.h"

namespace bitbang
{

/*!
 * \brief This class maintains a conical vision and reach perception sphere
 *
 * The cone of perception may be configured by range and angle.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2006-12-18
 *
 * \see BBPerceptionSphere
 *
 */
class BBVisionReach3DCone : public BBPerceptionSphere
{
public:
	BBVisionReach3DCone();
	virtual ~BBVisionReach3DCone();
	virtual void Update(BBPoint& c_position, BBPoint& c_rotation);
	
	void SetReach(float f_reach);
	void SetVisionRange(float f_range);
	void SetVisionAngle(float f_angle);
	float GetVisionRange();
	float GetVisionAngle();

	bool IsReachable(int n_object_id);
	int GetReachableObjectByType(int n_type);

	void PrintVisionList();
	void PrintReachList();

protected:
	BBObjectIDList m_VisionList;
	BBObjectIDList m_ReachList;

	float m_fVisionRange;
	float m_fVisionQuadRange;
	float m_fReach;
	float m_fQuadReach;
	float m_fVisionAngle;
};
}


#endif

