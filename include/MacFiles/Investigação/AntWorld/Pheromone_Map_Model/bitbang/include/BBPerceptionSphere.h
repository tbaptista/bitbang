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
#ifndef _BBPERCEPTIONSPHERE_H
#define _BBPERCEPTIONSPHERE_H

#include "BBTypes.h"
#include <vector>

namespace bitbang
{
	
class BBWorld;
class BBObject;

/*!
 * \brief Abstract base class for perceptions of range sensors.
 *
 * To accomodate several types of sphere (range) perceptions, this
 * class defines an interface to implement e.g. vision, smell, hearing.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2006-12-18
 *
 * \see BBVisionReach3DCone
 *
 */
class BBPerceptionSphere
{
public:
	BBPerceptionSphere();
	virtual ~BBPerceptionSphere();
	BBObjectIDList& GetObjectList(int n_index);
	BBObject* GetObject(int n_object_id);
	virtual void Update(BBPoint& c_position, BBPoint& c_rotation) = 0;
	void SetOwnerID(int n_id){m_nOwnerID = n_id;};
	void SetWorld(BBWorld* p_world){m_pWorld = p_world;};
	
protected:
	vector<BBObjectIDList*> m_ObjectListsVector;
	int m_nOwnerID;
	BBWorld* m_pWorld;
};
}


#endif //_BBPERCEPTIONSPHERE_H

