/*!
 * 
 * Copyright (c) 2004-2009 by Tiago Baptista. All rights reserved.
 *
 */

#ifndef _BBACTIONREPRODUCE_H_
#define _BBACTIONREPRODUCE_H_

#include "BBAction.h"

using namespace bitbang;

	
class BBActionReproduce : public BBAction
{
public:
	BBActionReproduce();
	virtual ~BBActionReproduce();
	void OnActivate(BBObject* p_agent);
	void OnDeactivate(BBObject* p_agent);
	void OnExecute(BBObject* p_agent);
	
private:
	double m_dTotalReproductionCost;
};


#endif //_BBACTIONREPRODUCE_H_
