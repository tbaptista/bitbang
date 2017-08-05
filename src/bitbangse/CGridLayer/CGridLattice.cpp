//
// Created by João Simões on 03/08/17.
//

#include "CGridLattice.h"
#include "ISceneManager.h"
#include "../util/CUtilities.h"
#include "CWorld.h"
#include "btBulletDynamicsCommon.h"

namespace bitbang
{

CGridLattice::CGridLattice() : GridLattice()
{

}

CGridLattice::CGridLattice(irr::scene::ISceneManager *pParentSceneManager) : GridLattice(), m_parentSmgr(pParentSceneManager)
{

}

CGridLattice::CGridLattice(irr::scene::ISceneManager *pParentSceneManager, BBPoint pCenter, int pSize) : GridLattice(), m_parentSmgr(pParentSceneManager)
{
    // Set lattice center
    this->SetCenter(pCenter);
}

CGridLattice::~CGridLattice()
{
    delete m_sceneNode;
}

void CGridLattice::Init()
{
    // Init graphics
    if (m_isVisible)
    {
        m_sceneNode = m_parentSmgr->addCubeSceneNode();
        m_sceneNode->setPosition(irr::core::vector3df(this->GetX(), this->GetY(), this->GetZ()));
        cutilities::ScaleToSize(m_sceneNode, this->size, 0.0, this->size);
        m_sceneNode->setRotation(irr::core::vector3df(0, 0, 0)); // no rotation
        m_sceneNode->setDebugDataVisible(1); //draws white edges in squares, useful for debugging and viewing
        m_sceneNode->setVisible(m_isVisible);
    }
    
    // Init physics
    if (m_isRigid)
    {
        CWorld* world = static_cast<CWorld*>(this->m_worldInterface);
        btDynamicsWorld* physicsWorld = world->GetPhysicsWorld();
    
        // Create spherical collision shape for the object
        btCollisionShape* latticeShape = new btSphereShape((btScalar) 0.5 * this->size);
    
        // Create a new collision object
        m_collisionObject = new btCollisionObject();
        // Associate the collision shape
        m_collisionObject->setCollisionShape(latticeShape);
        // As the collision object is static, better performance is achived by considering it an island sleeping
        m_collisionObject->setActivationState(ISLAND_SLEEPING);
    
        // Change the object positon to match the center of the lattice
        btTransform transform = m_collisionObject->getWorldTransform();
        transform.setOrigin(cutilities::FromBBPointToBtVector3(center));
        m_collisionObject->setWorldTransform(transform);
    
        // Add collision object to the bullet's world
        physicsWorld->addCollisionObject(m_collisionObject);
    }
}


}

