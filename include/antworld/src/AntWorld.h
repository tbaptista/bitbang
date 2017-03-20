/*!
 * 
 * Copyright (c) 2009 by Tiago Baptista. All rights reserved.
 *
 */

#ifndef ANTWORLD_H
#define ANTWORLD_H

#include "CWorld.h"
#include "BBCSVFileLog.h"
#include "AntConfig.h"
#include "AntMap.h"
#include "AntBrainConfig.h"
#include "AntAgent.h"
#include <vector>


using namespace std;
using namespace bitbang;

class AntWorld : public CWorld
{
public:
	AntWorld();
	virtual ~AntWorld();
	
	virtual void RemoveObject(int n_id);
	virtual void Init();
	void CreateFeedingZone(float f_x, float f_y, float f_z, float f_radius);
	void CreateAnt(int brainType, float f_x, float f_y, float f_z);
	virtual void LogDynamicStats();
	
	//Pheromone Map
	void UpdatePheromoneMap();
    void UpdatePheromoneMap2();
	void PlacePheromone(float f_x, float f_y, float f_strength, int pPheromoneType);
	float GetPheromone(float f_x, float f_y);
	void SetShowInfluenceMap(bool b_show_influence_map){m_bShowInfluenceMap = b_show_influence_map;};
	bool GetShowInfluenceMap(){return m_bShowInfluenceMap;};
    void PheromoneMapLog(const char* logsPath, const char* run, const char*configID);
    void InitPheromoneGranularityMap();
    void UpdateSquare(int i, int j, float value);
    AntMap* GetPheromoneMap() { return pheromoneMap; };
    
    float GetStrogestPheromoneDirection(AntAgent* agentPosition, int pPheromoneType);
    
    void TakeScreenshot();
	
private:
	virtual std::string GetInfoText();
	
	int m_nFoodCount;
	AntConfig m_Config;
	BBCSVFileLog m_AntDeathLog;
	std::vector<float> m_DynamicLogFieldValues;
	ofstream m_BrainLog;
    AntBrainConfig customBrainConfig;

	vector< vector<float> >* m_pPheromoneMap;
	float m_fPheromoneEvaporationRate;
	bool m_bShowInfluenceMap;
    
    AntMap *pheromoneMap; //Pheromone map with granularity
};

#endif //ANTWORLD_H

