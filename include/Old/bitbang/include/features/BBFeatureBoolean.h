/*
 * BitBang (http://www.bitbang.org)
 * Copyright (C) 2004-2008 Tiago Baptista
 *						   Telmo Menezes
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

#ifndef _BBFEATUREBOOLEAN_H_
#define _BBFEATUREBOOLEAN_H_

#include "BBFeature.h"
#include <string>

using namespace std;

namespace bitbang
{
/*!
 * \brief An agent's feature of boolean type.
 *
 * A feature represents a defined characteristic of an agent. BBFeatureBoolean
 * derives from the generic BBFeature and implements features of the boolean
 * kind (ex: is food).
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2006-03-04
 *
 * \todo Complete the class. This is just the skeleton
 *
 */
class BBFeatureBoolean : public BBFeature
{
public:
	BBFeatureBoolean();
	virtual ~BBFeatureBoolean();
	
	bool GetValue(){return m_bValue;}
	void SetValue(bool b_value){m_bValue = b_value;}
	string HumanReadable();
	
private:
	bool m_bValue;
};
}

#endif //_BBFEATUREBOOLEAN_H_
