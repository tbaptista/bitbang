//
//  EvacAgent.h
//  AircraftEvacuation
//
//  Created by João Simões on 10/07/15.
//
//

#ifndef __AircraftEvacuation__EvacAgent__
#define __AircraftEvacuation__EvacAgent__

#include <stdio.h>

#include "BBTypes.h"
#include "irrlicht.h"
#include "BrainConfig.h"
#include "Node.hpp"
#include "Graph.hpp"
#include "EvacuationExit.hpp"
#include "CSimObject.h"
#include "BoundingBox.h"
#include "BoundingCircle.hpp"
#include "Node.hpp"
#include "MemoryEntry.hpp"
#include "DynamicFeature.hpp"

#include <vector>
#include <deque>

using namespace bitbang;
using namespace std;
class GridMapLayer;

typedef map<string, MemoryEntry*> MemoryMap;
typedef map<string, vector<string> > AttributesMap;

class EvacAgent : public CSimObject
{
public:
    static const int CLASSID = 1001;
    
    static int m_nAgentCount;
    static int m_nPassengersCount;
    
    EvacAgent(irr::IrrlichtDevice* p_device);
    virtual ~EvacAgent();
    
    virtual void OnObjectUpdate(double d_elapsed_time);
    virtual void OnSelect();
    virtual void OnDeselect();
    virtual bool Init();
    virtual void Die();
    
    //Graphics
    void ScaleToGivenSize();
    
    // Initiallization
    void InitBase();
    void InitCrewMember();
    void InitCustomBrain();
    
    // Psichogical and phsycal initialization
    void InitAgentAttributes(AttributesMap* pAttributesMap);
    
    // Collision
    void GenerateBoundingBox();
    void GenerateBoundingCircle();
    void GenerateCrewMemberBoundingCircle();
    
    // Brain
    void SetCustomBrain(BrainConfig* customBrain) { m_CustomBrain = customBrain;};
    
    // Steering Behaviour
    void SetVelocity(float pVelocity) { velocity = pVelocity; };
    float GetVelocity() { return velocity; };
    float GetRotateSpeed() { return rotateSpeed; };
    void AlignAgentRotation();
    irr::core::vector3df* GetVelocityVector() { return &velocityVector; };
    
    //FOV In Graph Movement
    bool IsInterceptionZoneBusy(Node* pNode);
    bool IsAnAgentAhead(BBPoint* agentStartPosition);
    bool IsAnAgentAheadNodeInd(BBPoint* previousPosition);
    
    //Negotiation
    EvacAgent* IsAnAgentInNegotiationZone(Node* pNode);
    void AddCumulativeWaitTime(BBTime pCumulativeTime) { cumulativeWaitTime = pCumulativeTime; };

    // FOV Stearing
    void UpdateCellsInFOV();
    vector<BoundingBox*>* GetCellsInFOV() { return &cellsInFOV; };
    void PrintCellsInFOV();
    void GetVisionTriangle(BBPoint* trianglePoint[]);
    
    // Graph Movement
    Connection* GetCurrentConnection() { return currentConnection; };
    Node* GetCurrentNode() { return currentNode; };
    void SetCurrentNode(Node* pNode) { currentNode = pNode; };
    void SetCurrentConnection(Connection* pConnection) { currentConnection = pConnection; };
    void SetLastNonTerminalAction(string actionName) { lastNonTerminalAction = actionName; };
    //bool FollowPath(Node* targetNode);
    //bool MoveAgent(BBPoint start, BBPoint* end);
    bool ChooseNextNode();
    vector<Connection*>* GetPath() { return &path; };
    void CleanCurrentPath() { path.clear(); };
    bool OnNode() { return onNode; };
    bool HasNextGoalNodes() { return goalNodes->size() == 2; };
    Connection* GetFirstConnection() { return (!goalConnections->empty()) ? goalConnections->front() : NULL; };
    Connection* GetSecondConnection() { return (goalConnections->size() == 2) ? goalConnections->back() : NULL; };
    Node* GetFirstNode() { return (goalNodes->size() > 0) ? goalNodes->front() : NULL; };
    Node* GetSecondNode() { return (goalNodes->size() == 2) ? goalNodes->back() : NULL; };
    deque<Connection*>* GetGoalConnections() { return goalConnections; };
    deque<Node*>* GetGoalNodes() { return goalNodes; };
    bool Walk();
    bool ExecuteMovement(Node* targetNodem, BBPoint* startPosition);
    
    // Others
    EvacuationExit* GetAssignedExit() { return assignedExit; };
    void SetAssignedExit(EvacuationExit* p_Exit) { assignedExit = p_Exit; };
    BBPoint* GetDesiredDirection() { return desiredPosition; };
    void SetDesiredDirection(BBPoint* pDesiredPosition) { desiredPosition = pDesiredPosition; };
    
    // Memory
    void AddMemoryEntry(string pName, MemoryEntry& pMemoryEntry);
    MemoryEntry* GetMemoryEntry(string pName);
    BBPoint* GetLocationMemory(string pName);
    void SetLocationMemory(string pName, BBPoint* pLocation);
    
    BoundingBox* GetBoundingBox() { return box; };
    BoundingCircle* GetBoundingCircle() { return boundingCircle; };
    
protected:
    virtual void LogDeath();
    
private:
    string GetInfoText();
    void UpdateDynamicFeatures();
    
    BrainConfig* m_CustomBrain;
    
    vector<DynamicFeature*> dynamicFeatures;
    /**
     *  Map with all memory entries
     */
    MemoryMap memoryMap;
    /*
     *  Grid map cells perceived by the agent
     */
    vector<BoundingBox*> cellsInFOV;
    /**
     *  Agent's bounding box
     */
    BoundingBox* box;
    /**
     *  Agent's velocity
     */
    float velocity;
    /**
     *  Agent's circle box
     */
    BoundingCircle* boundingCircle;
    /**
     *  Desired postion coordinates
     */
    BBPoint* desiredPosition;
    /**
     *  Exit to redirect
     */
    EvacuationExit* assignedExit;
    /**
     *  Current node of the agent
     */
    Node* currentNode;
    /**
     *  Current connection of the agent
     */
    Connection* currentConnection;
    /**
     *  Queue of next two goal connections. Front: current correction; Back: secundary connection
     */
    deque<Connection*>* goalConnections;
    /**
     *  Goal nodes
     */
    deque<Node*>* goalNodes;
    /**
     *  Current path over the graph
     */
    vector<Connection*> path;
    /**
     *  Current target node coordinates
     */
    BBPoint currentTemporaryTarget;
    /**
     *  Indicates wether the agent is following a path
     */
    bool followingPath;
    /**
     *  Indicate wether an agent is placed over a graph node
     */
    bool onNode;
    
    // Psicologic attributes
    /**
     *  Passenger's stress level
     */
    int stress;
    /**
     *  Response delay when perceived evacuation call
     */
    float responseTime;
    /**
     *  Uncertain degree of the agents (should be a feature)
     */
    int uncertain;
    /**
     *  Indicates if an agent is ahead
     */
    bool isAnAgentAhead;
    
    // Physical attributes
    /**
     *  Max movement speed
     */
    float travelSpeed;
    /**
     *  Rotation speed
     */
    float rotateSpeed;
    /**
     *  Agent's current velocity vector
     */
    irr::core::vector3df velocityVector;
    /**
     *  Pre-computed values for colission verification
     */
    float minDistanceToCriticalZone;
    float minDistanceToCriticalZoneSquared;
    
    // Metrics
    vector<float> m_DeathLogFieldValues;
    /**
     *  Time wasted without movement
     */
    BBTime cumulativeWaitTime;
    /**
     *  Info box in GUI
     */
    irr::gui::IGUIStaticText* m_pInfoBox;
    /**
     *  Track last non terminal executed
     */
    string lastNonTerminalAction;
};

#endif /* defined(__AircraftEvacuation__EvacAgent__) */
