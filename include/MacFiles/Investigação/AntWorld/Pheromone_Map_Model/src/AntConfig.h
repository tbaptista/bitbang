/*!
 * 
 * Copyright (c) 2009 by Tiago Baptista. All rights reserved.
 *
 */

#ifndef ANTCONFIG_H
#define ANTCONFIG_H

#include <string>
#include "CFileConfig.h"
#include "BBTypes.h"

using namespace std;
using namespace bitbang;

class AntConfig : public CFileConfig
{
private:
	virtual bool ReadValue(string str_name);
	
public:
	//World
	static string ConfigID;
	static bool LogBrains;
	static BBTime TimeLimit;
	static bool RealTime;
	static double ComputationalTimeDelta;
	static int ThinkProbability;
	static int FieldSize;
	static int HomeX;
	static int HomeY;
	static int FeedingZones;
	static int MinAgents;
	static int PheromoneEvaporationRate;
	static int PheromoneGranularity;
	
	//Ant
	static bool UseTestBrain;
	static float VisionRange;
	static float VisionAngle;
	static float Reach;
	static double InitialEnergy;
	static double ReproductionCost;
	static bool ReproductionAction;
	static int EnergyRange;
	static double BaseMetabolicRate;
	static int MaxRules;
	static int MinRules;
	static int MaxConditions;
	static bool UseEditype;
	static int MinEditors;
	static int MaxEditors;
	static double MutationProbabilityEditype;
	static double MutationProbabilityRules;
	static double MutationProbabilityOrder;
	static double MutationProbabilityOrder2;
	static double MutationProbabilityList;
	static double WalkSpeed;
	static double RotateSpeed;
	static BBTime MaxAge;
	static int PheromoneDeposit;
	static int RandomRange;
	
	//Feeding Zone
	static int MinFood;
	static double FoodEnergy;
	static double FeedingZoneRadius;
};


#endif //ANTCONFIG_H

