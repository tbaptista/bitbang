//
// Created by João Simões on 03/08/17.
//

#include "CGridLattice.h"
#include "ISceneManager.h"
#include "../util/CUtilities.h"

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
    m_sceneNode = m_parentSmgr->addCubeSceneNode();
    m_sceneNode->setPosition(irr::core::vector3df(this->GetX(), this->GetY(), this->GetZ()));
    cutilities::ScaleToSize(m_sceneNode, this->size, 0.0, this->size);
    m_sceneNode->setRotation(irr::core::vector3df(0, 0, 0)); // no rotation
    m_sceneNode->setDebugDataVisible(1); //draws white edges in squares, useful for debugging and viewing
    m_sceneNode->setVisible(m_isVisible);
    
    // Init physics
}


}

