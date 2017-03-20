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
#include "AntWorldVisualMap.h"
#include "AntWorldEventHandler.h"
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
	void CreateAnt(bool b_test, float f_x, float f_y, float f_z);
	virtual void LogDynamicStats();
	
	//Pheromone Map
	void UpdatePheromoneMap();
	void PlacePheromone(float f_x, float f_y, float f_strength);
	float GetPheromone(float f_x, float f_y);
	void ToggleShowInfluenceMap() {m_bShowInfluenceMap = !m_bShowInfluenceMap;};
	
private:
	virtual std::string GetInfoText();
	
	int m_nFoodCount;
	AntConfig m_Config;
	BBCSVFileLog m_AntDeathLog;
	std::vector<float> m_DynamicLogFieldValues;
	ofstream m_BrainLog;

	vector< vector<float> >* m_pPheromoneMap;
	float m_fPheromoneEvaporationRate;
	bool m_bShowInfluenceMap;
	AntWorldVisualMap *m_pVisualMap;
};

#endif //ANTWORLD_H

