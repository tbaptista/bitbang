#pragma once

#include "irrlicht.h"
#include "driverChoice.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "CWorld.h"
#include "AntConfig.h"

using namespace std;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

using namespace std;
using namespace bitbang;

class AntMap : public irr::scene::ISceneNode , public CWorld
{
public:
    AntMap(irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, irr::s32 id, int lenX, int lenY, int pGranularity, float evapRate);
    void initSquare(int i, int j);
    int updateGranularitySquareValue(int line, int col, float value);
    void UpdateSquare(int position, float value);
    virtual void OnRegisterSceneNode();
    virtual void render();
    virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
    virtual irr::u32 getMaterialCount() const;
    virtual irr::video::SMaterial& getMaterial(irr::u32 i);
    bool isDrawn();
    void setDrawn( bool d);
    bool isUpdated();
    void setUpdated( bool u);
    void freeAllocations();
    void LogPheromoneMap(const char* logsPath, const char* run, const char*configID);
    int getGranularity();
    void UpdateMap();
    void PlacePheromone(float line, float column, float amount);
    float GetPheromoneValue(float line, float column);
    ~AntMap(void);
    
private:
    
    int sizeX;
    int sizeZ;
    int maxInfluence;
    int numSquaresX;
    int numSquaresZ;
    int numVertex;
    int granularity;
    int halfGranularity;
    int tenthOfGranularity;
    int pheromoneHeight;
    bool drawn;
    bool updated;
    
    float evaporationRate;
    int pheromoneMaxInfluence;
    
    float *pheromoneGranularityMap;
    
    vector< irr::scene::IMeshSceneNode* > *squares;
    irr::scene::ISceneManager* smgr;
    irr::u32 *indices;
    irr::core::aabbox3d<irr::f32> Box;
    irr::video::S3DVertex *Vertices;
    irr::video::SMaterial Material;
    
};

