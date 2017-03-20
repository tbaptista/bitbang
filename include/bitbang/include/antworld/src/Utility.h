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
#include "math.h"

#include "BBRandomGenerator.h"

#include "BBPoint.h"

using namespace std;
using namespace bitbang;

namespace utility {
    float EuclideanDistance(BBPoint* p1, BBPoint *p2);
    float EuclideanDistanceSQ(BBPoint* p1, BBPoint *p2);
}

#endif /* defined(__AircraftEvacuation__Utility__) */
