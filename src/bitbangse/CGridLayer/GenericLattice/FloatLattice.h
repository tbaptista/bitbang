//
// Created by João Simões on 03/07/17.
//

#ifndef BULLET_TEST_FLOATLATTICE_H
#define BULLET_TEST_FLOATLATTICE_H

#include "CGridLayer/CGridLattice.h"

namespace bitbang
{

class FloatLattice : public CGridLattice
{
public:
    FloatLattice();
    FloatLattice(irr::scene::ISceneManager* pParentSceneManager, BBPoint pCenter, int pSize);
    virtual ~FloatLattice() {};
    
    virtual void SetCurrentValue(float pValue) { currentValue = pValue; };
    virtual float GetCurrentValue() { return currentValue; };
    void SetOldValue(float pValue) { oldValue = pValue; };
    float GetOldValue() { return oldValue; };

private:
    float currentValue;
    float oldValue;
};
    
}

#endif //BULLET_TEST_FLOATLATTICE_H
