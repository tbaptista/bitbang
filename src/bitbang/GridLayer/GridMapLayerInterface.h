//
// Created by João Simões on 30/06/17.
//

#ifndef BULLET_TEST_GRIDMAPLAYERINTERFACE_H
#define BULLET_TEST_GRIDMAPLAYERINTERFACE_H

namespace bitbang
{

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
    virtual void Update() = 0;
};
    
}

#endif //BULLET_TEST_GRIDMAPLAYERINTERFACE_H
