#pragma once

#include "irrlicht.h"
#include "driverChoice.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "CWorld.h"

using namespace std;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

using namespace std;
using namespace bitbang;

class AntWorldVisualMap : public irr::scene::ISceneNode , public CWorld
{
public:
	AntWorldVisualMap(irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, irr::s32 id, vector< vector<float> >& m_pPheromoneMap, int pGranularity);
	void initSquare(int i, int j);
	int updateGranularitySquareValue(int line, int col, float value);
	void updateSquare(int i, int j, float value, bool show);
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
	void logData(const char* basePath, const char* configID, const char* runID);
	int getGranularity();
	~AntWorldVisualMap(void);

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

	float *pheromoneSquares;
	float *pheromoneSquaresTotalSum;

	vector< irr::scene::IMeshSceneNode* > *squares;
	irr::scene::ISceneManager* smgr;
	irr::u32 *indices;
	irr::core::aabbox3d<irr::f32> Box;
	irr::video::S3DVertex *Vertices;
	irr::video::SMaterial Material;

};

