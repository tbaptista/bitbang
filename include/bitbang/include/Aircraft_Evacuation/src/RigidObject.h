//
//  RigidObject.h
//  AircraftEvacuation
//
//  Created by João Simões on 14/08/15.
//
//

#ifndef __AircraftEvacuation__RigidObject__
#define __AircraftEvacuation__RigidObject__

#include <stdio.h>

#include "CSimObject.h"
#include "BBTypes.h"
#include "irrlicht.h"

#include "BoundingBox.h"

class RigidObject : public CSimObject
{
public:
    RigidObject(irr::IrrlichtDevice* p_device);
    virtual ~RigidObject();
    
    BoundingBox* GetBoundingBox() {return box;};
    
protected:
    BoundingBox* box;
};

#endif /* defined(__AircraftEvacuation__RigidObject__) */