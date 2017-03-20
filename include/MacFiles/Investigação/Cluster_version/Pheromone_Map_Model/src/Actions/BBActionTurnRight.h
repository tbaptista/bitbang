/*!
 * Copyright (c) 2004-2009 by Tiago Baptista. All rights reserved.
 */

#ifndef _BBACTIONTURNRIGHT_H_
#define _BBACTIONTURNRIGHT_H_

#include "BBAction.h"

using namespace bitbang;

/*!
 * \brief
 * This class represents an action that makes the agent turn to the right by a
 * small angle.
 *
 * \version 1.0
 *
 * \date 2006-09-10
 *
 * \see
 * BBAction
 */
class BBActionTurnRight : public BBAction
{
public:
	BBActionTurnRight();
	virtual ~BBActionTurnRight();
	void OnActivate(BBObject* p_agent);
	void OnDeactivate(BBObject* p_agent);
	void OnExecute(BBObject* p_agent);
};

#endif //_BBACTIONTURNRIGHT_H_
