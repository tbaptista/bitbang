//
// Created by João Simões on 04/07/17.
//

#include "CUtilities.h"
#include "BBPoint.h"

namespace cutilities
{

void ScaleToSize(irr::scene::ISceneNode *mesh, irr::f32 sizeX, irr::f32 sizeY, irr::f32 sizeZ)
{
    if (mesh == NULL)
    {
        return;
    }
    
    irr::core::vector3d<irr::f32> *edges = new irr::core::vector3d<irr::f32>[8];
    irr::core::aabbox3d<irr::f32> boundingBox = mesh->getTransformedBoundingBox();
    
    boundingBox.getEdges(edges);
    
    irr::f32 height = edges[1].Y - edges[0].Y;
    irr::f32 width = edges[5].X - edges[1].X;
    irr::f32 depth = edges[2].Z - edges[0].Z;
    
    irr::f32 factorX = sizeX / width;
    irr::f32 factorY = sizeY / height;
    irr::f32 factorZ = sizeZ / depth;
    
    mesh->setScale(irr::core::vector3df(factorX, factorY, factorZ));
}

btVector3 FromBBPointToBtVector3(bitbang::BBPoint pBBPoint)
{
    return btVector3(pBBPoint.GetX(), pBBPoint.GetY(), pBBPoint.GetZ());
}

bitbang::BBPoint FromBtVectorToBBPoint(btVector3 pVector)
{
    return bitbang::BBPoint(pVector.x(), pVector.y(), pVector.z());
}

}