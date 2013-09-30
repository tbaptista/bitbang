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

#include "BBPerceptionSphere.h"
#include "BBWorld.h"
#include "BBObject.h"
#include <vector>
#include <stdexcept>

namespace bitbang
{

	BBPerceptionSphere::BBPerceptionSphere()
	{
		m_nOwnerID = -1;
		m_pWorld = NULL;
	}
	
	BBPerceptionSphere::~BBPerceptionSphere()
	{
	}
	
	BBObjectIDList& BBPerceptionSphere::GetObjectList(int n_index)
	{
		if (n_index >= (int)m_ObjectListsVector.size())
		{
			throw range_error("Index is larger than vector size!");
		}
		
		return *(m_ObjectListsVector[n_index]);
	}

	BBObject* BBPerceptionSphere::GetObject(int n_object_id)
	{
		return (m_pWorld->GetObject(n_object_id));
	}
}

