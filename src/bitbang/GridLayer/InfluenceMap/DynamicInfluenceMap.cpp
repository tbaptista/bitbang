//
// Created by João Simões on 03/07/17.
//

#include "DynamicInfluenceMap.h"

namespace bitbang
{

DynamicInfluenceMap::DynamicInfluenceMap(string pName, irr::scene::ISceneNode *parent, irr::scene::ISceneManager *mgr,
                                         irr::s32 id, int sizeX, int sizeZ, int cellSize) :
                                        GridMapLayer<FloatLattice>(pName, sizeX, sizeZ, cellSize)
{
    
}

DynamicInfluenceMap::~DynamicInfluenceMap()
{

}

void DynamicInfluenceMap::PlaceInfluence()
{

}

void DynamicInfluenceMap::Update()
{

}

}
