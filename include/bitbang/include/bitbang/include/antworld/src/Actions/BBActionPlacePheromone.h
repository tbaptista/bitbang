/*!
 * 
 * Copyright (c) 2009 by Tiago Baptista. All rights reserved.
 *
 */

#ifndef _BBACTIONPLACEPHEROMONE_H_
#define _BBACTIONPLACEPHEROMONE_H_

#include "BBAction.h"

using namespace bitbang;


class BBActionPlacePheromone : public BBAction
{
public:
	BBActionPlacePheromone(string pPerceptionName, int pPheromoneType);
	virtual ~BBActionPlacePheromone();
	void OnActivate(BBObject* p_agent);
	void OnDeactivate(BBObject* p_agent);
	void OnExecute(BBObject* p_agent);
    
private:
    int pheromoneType;
    string featureName;
};


#endif //_BBACTIONPLACEPHEROMONE_H_
