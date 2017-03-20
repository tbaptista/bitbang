/*!
 *
 * Copyright (c) 2014 by Tiago Baptista. All rights reserved.
 *
 */

#ifndef __AntWorld__CInfluenceMapSceneNode__
#define __AntWorld__CInfluenceMapSceneNode__

#include "IMeshSceneNode.h"
#include "IMesh.h"

using namespace irr;

class CInfluenceMapSceneNode : public irr::scene::ISceneNode
{
public:
    CInfluenceMapSceneNode( scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);
    virtual ~CInfluenceMapSceneNode();
    
    
    
private:
    scene::IMesh* Mesh;
    core::aabbox3d<f32> Box;
};

#endif /* defined(__AntWorld__CInfluenceMapSceneNode__) */
