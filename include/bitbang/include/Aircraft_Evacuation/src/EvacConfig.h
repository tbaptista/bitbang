//
//  EvacConfig.h
//  Aircraft_Evacuation
//
//  Created by João Simões on 07/07/15.
//
//

#ifndef __Aircraft_Evacuation__EvacConfig__
#define __Aircraft_Evacuation__EvacConfig__

#include <stdio.h>
#include <string>

#include "CFileConfig.h"
#include "BBTypes.h"

using namespace std;
using namespace bitbang;

class EvacConfig : public CFileConfig
{
private:
    virtual bool ReadValue(string str_name);

public:
    // World
    static string ConfigID;
    static BBTime TimeLimit;
    static bool RealTime;
    static double ComputationalTimeDelta;
    static int FieldWidth;
    static int FieldLength;
    static int CellSize;
    static bool DebugGraph;
    
    // Passengers
    static int NumberOfPassengers;
    static float VisionRange;
    static float VisionAngle;
    static float Reach;
    static float PassengerStepSize;
    static float AgentSize;
    static float UpdateBackVisionProb;
    static float ThinkProbability;
    static float ReleaseCurrentNodesProbability;
    
    // Naviation Parameters
    static float ConflictRegionRadious;
    static float NegotiationZoneRadious;
    static float FindAlternativeRouteProbability;
    
    // Exit configuration
    static bool RandomExitAvailability;
    static bool UseRandomPriorities;
};

#endif /* defined(__Aircraft_Evacuation__EvacConfig__) */
