//
//  GenericComponent.h
//  AircraftEvacuation
//
//  Created by João Simões on 01/08/15.
//
//

#ifndef __AircraftEvacuation__GenericComponent__
#define __AircraftEvacuation__GenericComponent__

#include <stdio.h>

#include "RigidObject.h"
#include "Node.hpp"
#include "irrlicht.h"

#include "BoundingBox.h"

using namespace std;

class GenericComponent : public RigidObject
{
public:
    static const int CLASSID = 1002;
    
    GenericComponent(irr::IrrlichtDevice* p_device, float p_PosX, float p_PosZ);
    GenericComponent(irr::IrrlichtDevice* p_device, float p_PosX, float p_PosZ, float p_Width, float p_Depth);
    virtual ~GenericComponent();
    
    virtual bool Init();
    
    void GenerateBoundingBox();
    bool Intercept(BBObject* object);
    
protected:
    irr::IrrlichtDevice* m_pDevice;
};

#endif /* defined(__AircraftEvacuation__GenericComponent__) */
