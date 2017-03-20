/*!
 * Copyright (c) 2009 by Tiago Baptista. All rights reserved.
 */

#ifndef _BBACTIONRANDOMWALK_H_
#define _BBACTIONRANDOMWALK_H_

#include "BBAction.h"

using namespace bitbang;


class BBActionRandomWalk : public BBAction
{
public:
	static const int STATE_GOFRONT = 0;
	static const int STATE_TURNLEFT = 1;
	static const int STATE_TURNRIGHT = 2;
	static const int NUMSTATES = 3;
	
	BBActionRandomWalk();
	virtual ~BBActionRandomWalk();
	void OnActivate(BBObject* p_agent);
	void OnDeactivate(BBObject* p_agent);
	void OnExecute(BBObject* p_agent);

private:
	double m_dSpeed;
	double m_dRotateSpeed;
	int m_nState;
};



#endif //_BBACTIONRANDOMWALK_H_
