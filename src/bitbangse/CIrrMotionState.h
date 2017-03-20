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

#include "btBulletDynamicsCommon.h"
#include "CPhysicsObject.h"

namespace irr{
namespace scene {
class ISceneNode;
}	
}

class CIrrMotionState :  public btDefaultMotionState
{
public:
	CIrrMotionState(irr::scene::ISceneNode* p_node, CPhysicsObject* p_object);

	virtual void getWorldTransform(btTransform& center_of_mass_world_trans) const;
	virtual void setWorldTransform(const btTransform& center_of_mass_world_trans);
	
	static void QuaternionToEuler(const btQuaternion& TQuat, btVector3& TEuler);
	
private:
	irr::scene::ISceneNode* m_pNode;

    CPhysicsObject* m_pObject;
};

