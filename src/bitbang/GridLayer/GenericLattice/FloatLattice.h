//
// Created by João Simões on 03/07/17.
//

#ifndef BULLET_TEST_FLOATLATTICE_H
#define BULLET_TEST_FLOATLATTICE_H

#include "GridLayer/GridLattice.h"

namespace bitbang
{

class FloatLattice : public GridLattice
{
public:
    FloatLattice() {};
    FloatLattice(float pX, float pZ) { SetCenter(BBPoint(pX, 0, pZ)); };
    virtual ~FloatLattice() {};
    
    void SetCurrentValue(float pValue) { currentValue = pValue; };
    float GetCurrentValue() { return currentValue; };
    void SetOldValue(float pValue) { oldValue = pValue; };
    float GetOldValue() { return oldValue; };

private:
    float currentValue;
    float oldValue;
};
    
}

#endif //BULLET_TEST_FLOATLATTICE_H
