//
// Created by João Simões on 04/07/17.
//

#ifndef PROJECT_CUTILITIES_H
#define PROJECT_CUTILITIES_H

#include <LinearMath/btVector3.h>
#include "irrlicht.h"
#include "BBPoint.h"

namespace cutilities
{
    void ScaleToSize(irr::scene::ISceneNode *mesh, irr::f32 sizeX, irr::f32 sizeY, irr::f32 sizeZ);
    btVector3 FromBBPointToBtVector3(bitbang::BBPoint pBBPoint);
    bitbang::BBPoint FromBtVectorToBBPoint(btVector3 pVector);
}

#endif //PROJECT_CUTILITIES_H
