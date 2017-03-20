/*!
 * Copyright (c) 2004-2009 by Tiago Baptista. All rights reserved.
 */

#ifndef _BBPERCEPTIONRESOURCELOCATION_H
#define _BBPERCEPTIONRESOURCELOCATION_H

#include "perceptions/BBPerceptionNumber.h"

using namespace bitbang;


class BBPerceptionResourceLocation : public BBPerceptionNumber
{
public:
	BBPerceptionResourceLocation(void);
	virtual ~BBPerceptionResourceLocation(void);
	virtual BBPerception* Clone();
	virtual void Update(BBObject& c_agent);
};

#endif //_BBPERCEPTIONRESOURCELOCATION_H
