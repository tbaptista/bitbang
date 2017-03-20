//
//  BoundingBox.h
//  AircraftEvacuation
//
//  Created by João Simões on 14/08/15.
//
//

#ifndef __AircraftEvacuation__BoundingBox__
#define __AircraftEvacuation__BoundingBox__

#include <stdio.h>
#include "BBPoint.h"

using namespace bitbang;

class BoundingBox
{
public:
    BoundingBox(BBPoint* pos, float sizeX, float sizeZ);
    BoundingBox(BBPoint* pos);
    BoundingBox();
    ~BoundingBox();
    void SetWidth(float p_Width) {width = p_Width;};
    void SetDepth(float p_Depth) {depth = p_Depth;};
    float GetWidth() {return width;};
    float GetDepth() {return depth;};
    BBPoint* GetPosition() {return position;};
    void SetPosition(BBPoint* p_Position) {position = p_Position;};
    void HumanReadable();
    int GetOwnerID() { return ownerID; };
    void SetOwnerID(int pOwnerID) { ownerID = pOwnerID; };
    
    bool Intercept(BoundingBox* box);
    bool LineSegmentInterception(BBPoint* start, BBPoint* end);
    
    int InterceptLineSegments(BBPoint* l1p1, BBPoint* l1p2, BBPoint* l2p1, BBPoint* l2p2);
private:
    BBPoint* position;
    float width;
    float depth;
    
    int ownerID;
};

#endif /* defined(__AircraftEvacuation__BoundingBox__) */
