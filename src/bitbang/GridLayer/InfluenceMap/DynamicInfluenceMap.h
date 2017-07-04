//
// Created by João Simões on 03/07/17.
//

#ifndef BULLET_TEST_DYNAMICINFLUENCEMAP_H
#define BULLET_TEST_DYNAMICINFLUENCEMAP_H

#include <GridLayer/GridMapLayer.h>
#include <string>
#include "../../../irrlicht/include/ISceneNode.h"
#include "GridLayer/GenericLattice/FloatLattice.h"

namespace bitbang
{

class Influence;

using namespace std;

class DynamicInfluenceMap : public GridMapLayer<FloatLattice>
{
public:
    DynamicInfluenceMap(string pName, irr::scene::ISceneNode *parent, irr::scene::ISceneManager *mgr, irr::s32 id,
                        int sizeX, int sizeZ,
                        int cellSize);
    virtual ~DynamicInfluenceMap();
    
    // Place a new source into the grid
    virtual void PlaceInfluence();
    // Method for updating all grid lattices
    virtual void Update();

private:
    vector<Influence*> influences;
};
    
}


#endif //BULLET_TEST_INFLUENCEMAP_H
