/*!
 * 
 * Copyright (c) 2004-2009 by Tiago Baptista. All rights reserved.
 */

#ifndef _BBACTIONEAT_H_
#define _BBACTIONEAT_H_

#include "BBAction.h"
#include "BBWorldInterface.h"

using namespace bitbang;
	
class BBActionEat : public BBAction
{
public:
	BBActionEat(BBWorldInterface* p_world);
	virtual ~BBActionEat();
	void OnActivate(BBObject* p_agent);
	void OnDeactivate(BBObject* p_agent);
	void OnExecute(BBObject* p_agent);
	
private:
	BBWorldInterface* m_pWorld;
};


#endif //_BBACTIONEAT_H_


