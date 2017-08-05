//
// Created by João Simões on 03/08/17.
//

#include "FloatLattice.h"

namespace bitbang
{

FloatLattice::FloatLattice() : CGridLattice()
{
    currentValue = 0.0;
    oldValue = 0.0;
}

FloatLattice::FloatLattice(irr::scene::ISceneManager* pParentSceneManager, BBPoint pCenter, int pSize) : CGridLattice(pParentSceneManager, pCenter, pSize)
{

}

}