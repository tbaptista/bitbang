//
//  GridMapLayer.h
//  AircraftEvacuation
//
//  Created by João Simões on 11/08/15.
//
//

#ifndef __AircraftEvacuation__GridMapLayer__
#define __AircraftEvacuation__GridMapLayer__

#include <stdio.h>
#include <vector>
#include <map>
#include "irrlicht.h"

#include "RigidObject.h"
#include "SeatsBlock.h"
#include "EvacAgent.h"
#include "BoundingBox.h"
#include "BBPoint.h"
#include "EvacWorld.h"
#include "SeatsBlock.h"

using namespace std;

class GridMapLayer : public irr::scene::ISceneNode
{
public:
    GridMapLayer(irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, irr::s32 id, int sizeX, int sizeZ, int cellSize);
    ~GridMapLayer();
    void AddObject(RigidObject* object, bool isPercepted);
    void AddAgent(EvacAgent* pAgent);
    void DeleteObjectsMap();
    void UpdateAgentPosition(BBPoint* previousPosition, BBPoint* currentPosition, EvacAgent* pAgent);
    void RemoveAgent(EvacAgent* pAgent, BBPoint* previousPosition);
    
    void InitSquare(int i, int j);
    virtual void onRegisterSceneNode();
    virtual void render();
    virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
    virtual irr::u32 getMaterialCount() const;
    virtual irr::video::SMaterial& getMaterial(irr::u32 i);
    
    bool CheckObjectsInCell(int k, EvacAgent* agent);
    void RemoveAgentFromCell(int k, EvacAgent* agent);
    bool CheckForCollisions(BoundingBox* objectBox, bool isAgent);
    bool CheckRayInterception();
    
    // Bounding circle collision
    EvacAgent* CheckAgentsCollisionsCircle(BoundingCircle* boundingCircle);
    EvacAgent* CheckAgentsCollisionsCircleInCell(int k, BoundingCircle* boundingCircle);
    void CheckAllAgentsCollisionsCircle(BoundingCircle* boundingCircle, map<int, EvacAgent*>* collisionAgents);
    void CheckAllAgentsCollisionsCircleInCell(int k, BoundingCircle* boundingCircle, map<int, EvacAgent*>* collisionAgents);
    
    // Collision Verification
    bool CanMoveFromTo(BBPoint* start, BBPoint* target, bool verticalMovement);
    bool CanCreateNode(int graphPositionX, int graphPositionZ);
    bool CanCreateNodeAtContinous(float posX, float posZ);
    
    void RegisterSeatBlockNodes(SeatsBlock* pSeatBlock);
    bool CheckObjectsCollisionsInCell(int k, BoundingBox* objectBox);
    bool CheckAgentsCollisionsInCell(int k, BoundingBox* objectBox);
    
    void GetCellsWithinTriangle(BBPoint* triangle[], vector<BoundingBox*> *cells, BBPoint* agentPosition);
    void GetObjectsWithinTriangle(BBPoint* triangle[], BBObjectIDList* objects, int objectID);
    void GetBoundaries(BBPoint* triangle[], int* triangleBoundaries);
    void GetObjectsWithinRectangularZone(vector<BBObject*>* objects, int pObjectID, float pMinX, float pMaxX, float pMinZ, float pMaxZ);
    
    bool IsPointInCell(BBPoint* position, int x, int z);
    float Sign(BBPoint* p1, BBPoint* p2, BBPoint* p3);
    bool PointInTriangle(BBPoint* triangle[], BBPoint* point);
    
    int GetAgentsMapSize() { return agentsMap->size(); };
    
private:
    // General parameters
    vector<RigidObject*>* gridMap; // This only includes the objects that are considered to the graph building process
    vector<EvacAgent*>* agentsMap; // All spacial dynamic objects
    vector<RigidObject*>* perceivedObjectsMap; // All static objects perpected and with a influence to the agents (e.g. exit signs, evacuation exits)
    
    BoundingBox* squaresBoxes;
    int nSquaresX;
    int nSquaresZ;
    int cellSize;
    int halfOfCellSize;
    int tenthOfCellSize;
    int numVertex;
    float agentSize;
    
    // Grid's visual attributes
    vector< irr::scene::IMeshSceneNode* > *squares;
    irr::scene::ISceneManager* smgr;
    irr::u32 *indices;
    irr::core::aabbox3d<irr::f32> Box;
    irr::video::S3DVertex *Vertices;
    irr::video::SMaterial Material;
    
    bool CheckIfSameStraightLine();
};

#endif /* defined(__AircraftEvacuation__GridMapLayer__) */
