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

#ifndef _BBFEATURENUMBER_H_
#define _BBFEATURENUMBER_H_

#include "BBFeature.h"
#include <string>

using namespace std;

namespace bitbang
{
/*!
 * \brief An agent's feature of numeric type.
 *
 * A feature represents a defined characteristic of an agent. BBFeatureNumber
 * derives from the generic BBFeature and implements features of the numeric
 * kind (ex: energy level).
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2005-07-02
 *
 * \todo Complete the class. This is just the skeleton
 *
 */
class BBFeatureNumber : public BBFeature
{
public:
	BBFeatureNumber();
	virtual ~BBFeatureNumber();
	
	double GetValue(){return m_dValue;};
	void SetValue(double d_value){m_dValue = d_value;};
	string HumanReadable();
	
private:
	double m_dValue;
};
}

#endif //_BBFEATURENUMBER_H_
