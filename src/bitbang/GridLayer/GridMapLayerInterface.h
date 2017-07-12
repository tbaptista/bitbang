//
// Created by João Simões on 30/06/17.
//

#ifndef BULLET_TEST_GRIDMAPLAYERINTERFACE_H
#define BULLET_TEST_GRIDMAPLAYERINTERFACE_H

namespace bitbang
{

class GridLattice;

class GridMapLayerInterface
{
public:
    virtual std::string GetName() = 0;
    virtual void SetName(std::string pName) = 0;
    virtual int GetSizeX() = 0;
    virtual int GetSizeZ() = 0;
    virtual int GetNCellsX() = 0;
    virtual int GetNCellsZ() = 0;
    virtual int GetCellSize() = 0;
    virtual int GetCellIndex(float x, float z) = 0;
    virtual int GetIndex(float pos) = 0;
    virtual void Update(double d_elapsed_time = 0) = 0;
    virtual GridLattice* GetCellAt(float x, float z) = 0;
};
    
}

#endif //BULLET_TEST_GRIDMAPLAYERINTERFACE_H
