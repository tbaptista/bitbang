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

#ifndef _BBVISIONREACH2DCIRCLE_H
#define _BBVISIONREACH2DCIRCLE_H

#include "BBTypes.h"
#include "BBPerceptionSphere.h"

namespace bitbang
{

/*!
 * \brief This class maintains a 2D circular vision and reach perception sphere
 *
 * The circle of perception may be configured by range (radius). The axis used are
 * X and Z.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2009-06-06
 *
 * \see BBPerceptionSphere
 *
 */
class BBVisionReach2DCircle : public BBPerceptionSphere
{
public:
	BBVisionReach2DCircle();
	virtual ~BBVisionReach2DCircle();
	virtual void Update(BBPoint& c_position, BBPoint& c_rotation);
	
	void SetReach(float f_reach);
	void SetVisionRange(float f_range);
	float GetVisionRange();

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
};
}


#endif //_BBVISIONREACH2DCIRCLE_H

