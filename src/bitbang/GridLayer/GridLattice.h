//
// Created by João Simões on 01/07/17.
//

#ifndef BULLET_TEST_GRIDLATTICE_H
#define BULLET_TEST_GRIDLATTICE_H

#include "BBPoint.h"

namespace bitbang
{

using namespace bitbang;

class BBWorldInterface;

class GridLattice
{
public:
    GridLattice();
    virtual ~GridLattice();
    
    virtual void SetCenter(const BBPoint &center);
    virtual const BBPoint &GetCenter() const;
    
    virtual float GetX() { return center.GetX(); };
    virtual float GetY() { return center.GetY(); };
    virtual float GetZ() { return center.GetZ(); };
    
    void SetSize(int pSize) { size = pSize; };
    
    void SetWorld(BBWorldInterface* pWorldInterface) { m_worldInterface = pWorldInterface; };

protected:
    BBPoint center;
    int size;
    
    BBWorldInterface* m_worldInterface;
};
    
}


#endif //BULLET_TEST_GRIDLATTICE_H
