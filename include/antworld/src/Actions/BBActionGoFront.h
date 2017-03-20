/*!
 * Copyright (c) 2004-2009 by Tiago Baptista. All rights reserved.
 */

#ifndef _BBACTIONGOFRONT1234_H_
#define _BBACTIONGOFRONT1234_H_

#include "BBAction.h"

using namespace bitbang;


/*!
 * \brief
 * This class represents an action that makes the agent go in the direction it
 * is facing.
 *
 * \version 1.0
 *
 * \date 2005-10-10
 *
 * \see
 * BBAction
 */
class BBActionGoFront : public BBAction
{
public:
	BBActionGoFront();
	virtual ~BBActionGoFront();
	void OnActivate(BBObject* p_agent);
	void OnDeactivate(BBObject* p_agent);
	void OnExecute(BBObject* p_agent);

private:
	double m_dSpeed;
};



#endif //_BBACTIONGOFRONT1234_H_
