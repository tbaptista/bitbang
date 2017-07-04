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
    virtual ~FloatLattice() {};
    
    void SetValue(float pValue) { value = pValue; };
    float GetValue() { return value; };

private:
    float value;
};
    
}
    

#endif //BULLET_TEST_FLOATLATTICE_H
