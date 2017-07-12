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
    cerr << "Initializing " << GetName() << " object..." << endl;

	if (!CSimObject::Init())
	{
        cerr << "Error while initializing object" << endl;
		return false;
	}
	
	//Create MotionState
	CIrrMotionState* MotionState = new CIrrMotionState(m_pNode, this);
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
	else if (m_nNodeType == NODETYPE_SPHERE)
	{
		Shape = new btSphereShape(0.5f);
	}
	else
	{
		return false;
	}

	//Add mass
	btVector3 LocalInertia;
	Shape->calculateLocalInertia((btScalar) m_dMass, LocalInertia);

    cerr << "Creating rigid body..." << endl;
	//Create the rigid body
	m_pRigidBody = new btRigidBody((btScalar) m_dMass, MotionState, Shape, LocalInertia);

    cerr << "Rigid body created!" << endl;

	return true;
}

void CPhysicsObject::ApplyConstantForce(btVector3& pForceDirection)
{
	m_pRigidBody->applyCentralForce(pForceDirection);
}

void CPhysicsObject::ApplyConstantForce(float x, float y, float z)
{
	m_pRigidBody->applyCentralForce(btVector3((btScalar) x, (btScalar) y, (btScalar) z));
}

void CPhysicsObject::ScaleToGivenSize(float sizeX, float sizeY, float sizeZ)
{
	irr::scene::ISceneNode* mesh = m_pNode;

	if (mesh == NULL)
	{
		return;
	}

	irr::core::vector3d<irr::f32>* edges = new irr::core::vector3d<irr::f32>[8];
	irr::core::aabbox3d<irr::f32> boundingBox = mesh->getTransformedBoundingBox();

	boundingBox.getEdges(edges);

	irr::f32 height = edges[1].Y - edges[0].Y;
	irr::f32 width = edges[5].X - edges[1].X;
	irr::f32 depth = edges[2].Z - edges[0].Z;

	irr::f32 factorX = sizeX/width;
	irr::f32 factorY = sizeY/height;
	irr::f32 factorZ = sizeZ/depth;

	m_fScaleX = factorX;
	m_fScaleY = factorY;
	m_fScaleZ = factorZ;

	btCollisionShape* collisionShape = m_pRigidBody->getCollisionShape();
	collisionShape->setLocalScaling(btVector3(m_fScaleX, m_fScaleY, m_fScaleZ));

	mesh->setScale(irr::core::vector3df(factorX,factorY,factorZ));
}
