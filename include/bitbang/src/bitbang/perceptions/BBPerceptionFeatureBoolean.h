/*
 * BitBang (http://www.bitbang.org)
 * Copyright (C) 2004-2008 Tiago Baptista
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the version 2 of the GNU General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _BBPERCEPTIONFEATUREBOOLEAN_H
#define _BBPERCEPTIONFEATUREBOOLEAN_H

#include "perceptions/BBPerceptionBoolean.h"

namespace bitbang
{
class BBFeatureBoolean;

/*!
 * \brief This class represents a perception that takes the value of a feature
 * of type boolean.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2008-12-11
 *
 * \see BBPerception
 */
class BBPerceptionFeatureBoolean : public BBPerceptionBoolean
{
private:
	BBFeatureBoolean* m_pFeature;
	
public:
	BBPerceptionFeatureBoolean(BBFeatureBoolean& c_feature);
	virtual ~BBPerceptionFeatureBoolean();
	virtual BBPerception* Clone();
	
	void SetFeature(BBFeatureBoolean& c_feature);
	
	virtual void Update(BBObject& c_agent);
};
}

#endif //_BBPERCEPTIONFEATUREBOOLEAN_H

