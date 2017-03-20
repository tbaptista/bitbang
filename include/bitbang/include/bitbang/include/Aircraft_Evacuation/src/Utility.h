//
//  Utility.h
//  AircraftEvacuation
//
//  Created by João Simões on 03/08/15.
//
//

#ifndef __AircraftEvacuation__Utility__
#define __AircraftEvacuation__Utility__

#include <stdio.h>
#include <string>
#include <vector>

#include "irrlicht.h"
#include "BBRandomGenerator.h"

#include "BBPoint.h"

using namespace std;
using namespace bitbang;

namespace utility {
    int stringToInt(string str);
    float stringToFloat(string str);
    bool stringToBool(string str);
    void ScaleToSize(irr::scene::ISceneNode* mesh, irr::f32 sizeX, irr::f32 sizeY, irr::f32 sizeZ);
    void VectorBetweenTwoPoints(BBPoint* initial, BBPoint* final, irr::core::vector3df* velocity);
    bool IsPointInTriangle(BBPoint* triangle[], BBPoint* point);
    float EuclideanDistance(BBPoint* p1, BBPoint *p2);
    float EuclideanDistanceSQ(BBPoint* p1, BBPoint *p2);
    bool AreClockWise(irr::core::vector2df* v1, irr::core::vector2df* v2);
    bool IsWithinRadius(irr::core::vector2df* v, float radiousSquared);
    void Split(const string& s, char delim, vector<string>& v);
    float GenerateRandomFloat(float min, float max);
    float constrainAngle(float x);
    bool Parallel(irr::core::vector3df a, irr::core::vector3df b, float tolerance);
}

#endif /* defined(__AircraftEvacuation__Utility__) */
