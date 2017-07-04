//
// Created by João Simões on 01/07/17.
//

#include "GridLattice.h"

namespace bitbang
{

GridLattice::GridLattice()
{
    
}

GridLattice::~GridLattice()
{
    
}

void GridLattice::SetCenter(const BBPoint &center)
{
    GridLattice::center = center;
}

const BBPoint &GridLattice::GetCenter() const
{
    return center;
}
    
}
