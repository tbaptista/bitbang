//
//  EvacWorld.h
//  Aircraft_Evacuation
//
//  Created by João Simões on 07/07/15.
//
//

#ifndef __Aircraft_Evacuation__EvacWorld__
#define __Aircraft_Evacuation__EvacWorld__

#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <random>

#include "CWorld.h"
#include "BBCSVFileLog.h"
#include "BrainConfig.h"
#include "EvacConfig.h"
#include "GridMapLayer.h"
#include "Graph.hpp"
#include "EvacuationExit.hpp"
#include "SeatsBlock.h"
#include "BBCSVFileLog.h"

#include "BoundingBox.h"

using namespace std;
using namespace bitbang;


/*!
 @class EvacWorld
 @superclass CWorld
 @discussion Represents the evacuation simulation environment. All passengers and aircraft structures are built here
*/
class EvacWorld : public CWorld
{
public:
    EvacWorld();
    virtual ~EvacWorld();
    
    virtual void Init();
    default_random_engine* GetRandomGenerator() { return &generator; };
    default_random_engine* GetSeatRandomGenerator() { return &seatRandomGenerator; };
    default_random_engine* GetPopulationRandomGenerator() { return &populationRandomGenerator; };
    
    void CreatePassenger(float blockNumber, float seatNumber);
    void CreateCrewMember(float posX, float posZ);
    void PlaceCrewMembersCloseToExits();
    
    GridMapLayer* GetGridMapLayer() { return objectsMap; };
    Graph* GetGraph() { return graph; };
    vector<SeatsBlock*> GetSeatBlocks() { return seatBlocks; };
    Node* GetRandomEvacuationExitNode();
    
    bool InterceptWithAgents(EvacAgent* pAgent);
    
    virtual void LogDynamicStats();
    void LogEvacuationExits();
    
private:
    /**
     *  Configuration loader
     */
    EvacConfig m_Config;
    /**
     *  Auxiliar structure to hold component specification when being loaded from configuration file
     */
    map<string, string> objectSpecifications;
    /**
     *  Spatial grid layer
     */
    GridMapLayer* objectsMap;
    /**
     *  Movement's graph
     */
    Graph* graph;
    /**
     *  Agent's brain loader
     */
    BrainConfig customBrainConfig;
    /**
     *  Population file path
     */
    string passengersConfigPath;
    /**
     *  Auxiliar structure to hold passenger's attributes
     */
    AttributesMap passengerAttributes;
    set<int> availableBlocks;  // Support set used to hold the available seat blocks
    /**
     *  Evacuation exits in the aircraft
     */
    vector<EvacuationExit*> evacuationExits;
    /**
     *  Seat blocks in the aircraft
     */
    vector<SeatsBlock*> seatBlocks;
    /**
     *  Random generator
     */
    default_random_engine generator;
    /**
     *  New random generator
     */
    default_random_engine seatRandomGenerator;
    /**
     *  Population random generator
     */
    default_random_engine populationRandomGenerator;
    /**
     *  Passenger evacuation log
     */
    BBCSVFileLog passengerEvacuationLog;
    /**
     *  General log with global metrics
     */
    BBCSVFileLog exitsLog;
    vector<float> exitsLogData;
    
    void InitGraphics();
    void ConnectNodeToNeighboors(int nodePositionX, int nodePositionZ);
    void InitAircraftConfiguration();
    void ReadConfigBlock(string blockIdentifier);
    bool ComputeObjectArguments(string objectArguments);
    void LoadConfigFile(string configPath);
    void ConnectEvacuationExits();
    void RegisterEvacuationExits();
    void LoadAircraftPopulation();
    void ComputePassengerCategory(string cPassengerType);
    void ReadCategoryAttributes(string categoryName);
    void BuildGraphWorld();
    void RegisterSeatBlockNodes(SeatsBlock* pSeatBlock);
    void ConnectSeatBlocksToGraph();
    void BuildGraph();
    void DetermineNodePotencials();
    void LoadCrewMembersConfig();
    void ReadCrewMembersConfigBlock();
    
    // Methods to obtain the
    EvacuationExit* GetNearestExit(BBPoint* objectPos);
    EvacuationExit* GetNearestExitInFront(BBPoint* objectPos);
    EvacuationExit* GetNearestExitInZone(BBPoint* objectPos);
    EvacuationExit* GetNearestMostFamiliarExit(BBPoint* objectPos);
    void GetAgentRegion(BBPoint* objectPos, vector<float> &region);
    
    void CreateAircraftGround(float sizeX, float sizeZ, string texturePath);
    
    void InitLogs();
};

#endif /* defined(__Aircraft_Evacuation__EvacWorld__) */
