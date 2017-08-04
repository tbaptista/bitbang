//
// Created by João Simões on 03/08/17.
//

#include "FloatLattice.h"

namespace bitbang
{

FloatLattice::FloatLattice() : CGridLattice()
{

}

FloatLattice::FloatLattice(irr::scene::ISceneManager* pParentSceneManager, BBPoint pCenter, int pSize) : CGridLattice(pParentSceneManager, pCenter, pSize)
{

}

}