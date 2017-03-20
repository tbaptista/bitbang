/*!
 * Copyright (c) 2004-2009 by Tiago Baptista. All rights reserved.
 */

#ifndef _BBACTIONTURNLEFT_H_
#define _BBACTIONTURNLEFT_H_

#include "BBAction.h"

using namespace bitbang;

/*!
 * \brief
 * This class represents an action that makes the agent turn to the left by a
 * small angle.
 *
 * \version 1.0
 *
 * \date 2005-10-10
 *
 * \see
 * BBAction
 */
class BBActionTurnLeft : public BBAction
{
public:
	BBActionTurnLeft();
	virtual ~BBActionTurnLeft();
	void OnActivate(BBObject* p_agent);
	void OnDeactivate(BBObject* p_agent);
	void OnExecute(BBObject* p_agent);
};


#endif //_BBACTIONTURNLEFT_H_
