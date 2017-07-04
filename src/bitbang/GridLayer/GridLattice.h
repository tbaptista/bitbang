//
// Created by João Simões on 01/07/17.
//

#ifndef BULLET_TEST_GRIDLATTICE_H
#define BULLET_TEST_GRIDLATTICE_H

#include "BBPoint.h"

namespace bitbang
{

using namespace bitbang;

class GridLattice
{
public:
    GridLattice();
    virtual ~GridLattice();
    
    virtual void SetCenter(const BBPoint &center);
    virtual const BBPoint &GetCenter() const;

private:
    BBPoint center;
};
    
}


#endif //BULLET_TEST_GRIDLATTICE_H
