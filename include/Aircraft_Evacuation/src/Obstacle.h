//
//  Obstacle.h
//  AircraftEvacuation
//
//  Created by João Simões on 04/09/15.
//
//

#ifndef __AircraftEvacuation__Obstacle__
#define __AircraftEvacuation__Obstacle__

#include <stdio.h>

#include "GenericComponent.h"
#include "irrlicht.h"

class Obstacle : public GenericComponent
{
public:
    static const int CLASSID = 1004;
    
    Obstacle(irr::IrrlichtDevice* p_device, float p_PosX, float p_PosZ, float p_Width, float p_Depth);
    virtual ~Obstacle();
    
    virtual bool Init();
    
    void InitBase();
};

#endif /* defined(__AircraftEvacuation__Obstacle__) */
