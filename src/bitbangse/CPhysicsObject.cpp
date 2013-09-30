/*
 * BitBang (http://www.bitbang.org)
 * Copyright (C) 2004-2009 Tiago Baptista
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

#include "CPhysicsObject.h"
#include "CIrrMotionState.h"

#include "irrlicht.h"

#include <iostream>
#include <string>
using namespace std;

/*!
 * \brief Constructor.
 *
 */
CPhysicsObject::CPhysicsObject(irr::IrrlichtDevice* p_device) : CSimObject(p_device)
{
	m_pRigidBody = NULL;
	
	m_dMass = 0;
}

/*!
 * \brief Destructor.
 *
 */
CPhysicsObject::~CPhysicsObject()
{

}

/*!
 * \brief Initialize the Bullet objects.
 *
 * \return true on success, false on failure.
 *
 */
bool CPhysicsObject::Init()
{
	if (!CSimObject::Init())
	{
		return false;
	}
	
	//Create MotionState
	CIrrMotionState* MotionState = new CIrrMotionState(m_pNode);
	btCollisionShape* Shape = NULL;
	
	//Create the shape
	if (m_nNodeType == NODETYPE_CUBE)
	{
		btVector3 HalfExtents(m_fScaleX * 0.5f, m_fScaleY * 0.5f, m_fScaleZ * 0.5f);
		Shape = new btBoxShape(HalfExtents);
	}
	else if (m_nNodeType == NODETYPE_MESH || m_nNodeType == NODETYPE_ANIMATEDMESH)
	{
		irr::core::aabbox3df BoundingBox = m_pNode->getBoundingBox();
		irr::core::vector3df Extents = BoundingBox.getExtent();
		btVector3 HalfExtents(Extents.X * 0.5f, Extents.Y * 0.5f, Extents.Z * 0.5f);
		Shape = new btBoxShape(HalfExtents);
	}
	else
	{
		return false;
	}
	
	//Add mass
	btVector3 LocalInertia;
	Shape->calculateLocalInertia(m_dMass, LocalInertia);
	
	//Create the rigid body
	m_pRigidBody = new btRigidBody(m_dMass, MotionState, Shape, LocalInertia);

	return true;
}
