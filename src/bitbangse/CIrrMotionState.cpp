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

#include "CIrrMotionState.h"
#include "irrlicht.h"

using namespace irr;

CIrrMotionState::CIrrMotionState(scene::ISceneNode *p_node, CPhysicsObject* p_object) : btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
                                                                                               btVector3(
                                                                                                       p_node->getPosition().X,
                                                                                                       p_node->getPosition().Y,
                                                                                                       p_node->getPosition().Z)))
{
    m_pNode = p_node;
    m_pObject = p_object;
}

/*!
 * \brief Synchronizes world transform from user to physics.
 *
 * \param center_of_mass_world_trans
 * Reference to a btTransform where to put the current world transform.
 *
 */
void CIrrMotionState::getWorldTransform(btTransform &center_of_mass_world_trans) const
{
    center_of_mass_world_trans = m_graphicsWorldTrans * m_centerOfMassOffset.inverse() ;
    //center_of_mass_world_trans = m_graphicsWorldTrans;
}

/*!
 * \brief Synchronizes world transform from physics to user.
 *
 * Bullet only calls the update of world transform for active objects.
 *
 * \param center_of_mass_world_trans 
 * Reference to a btTransform with the current world transform.
 *
 */
void CIrrMotionState::setWorldTransform(const btTransform &center_of_mass_world_trans)
{
    m_startWorldTrans = center_of_mass_world_trans;
    //m_graphicsWorldTrans = center_of_mass_world_trans;

    m_graphicsWorldTrans = center_of_mass_world_trans * m_centerOfMassOffset ;

    const btVector3 &Point = center_of_mass_world_trans.getOrigin();
    m_pNode->setPosition(core::vector3df((f32) Point[0], (f32) Point[1], (f32) Point[2]));
    m_pObject->SetPosition((f32) Point[0], (f32) Point[1], (f32) Point[2]);

    // Set rotation
    btVector3 EulerRotation;
    QuaternionToEuler(center_of_mass_world_trans.getRotation(), EulerRotation);
    m_pNode->setRotation(core::vector3df(EulerRotation[0], EulerRotation[1], EulerRotation[2]));
    m_pObject->SetRotation(EulerRotation[0], EulerRotation[1], EulerRotation[2]);
}

/*!
 * \brief Converts a Bullet quaternion to an Irrlicht euler angle
 *
 * \param TQuat 
 * Constant reference to the quaternion to be converted.
 *
 * \param TEuler
 * Refernce to the vector to hold the converted euler angle.
 */
void CIrrMotionState::QuaternionToEuler(const btQuaternion &TQuat, btVector3 &TEuler)
{
    btScalar W = TQuat.getW();
    btScalar X = TQuat.getX();
    btScalar Y = TQuat.getY();
    btScalar Z = TQuat.getZ();
    float WSquared = W * W;
    float XSquared = X * X;
    float YSquared = Y * Y;
    float ZSquared = Z * Z;

    TEuler.setX(atan2f(2.0f * (Y * Z + X * W), -XSquared - YSquared + ZSquared + WSquared));
    TEuler.setY(asinf(-2.0f * (X * Z - Y * W)));
    TEuler.setZ(atan2f(2.0f * (X * Y + Z * W), XSquared - YSquared - ZSquared + WSquared));
    TEuler *= core::RADTODEG;
}

