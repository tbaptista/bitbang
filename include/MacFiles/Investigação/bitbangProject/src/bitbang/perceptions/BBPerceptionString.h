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
#ifndef _BBPERCEPTIONSTRING_H
#define _BBPERCEPTIONSTRING_H

#include "BBPerception.h"
#include <string>

using namespace std;

namespace bitbang
{
/*!
 * \brief Perception of type string base class.
 *
 * Defines the generic perception whose value is a string. This class cannot be
 * instatiated as it has purely virtual methods. To use, derive a class.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2008-06-02
 *
 */
class BBPerceptionString : public BBPerception
{
public:
	//Operations
	const static int nOPEQUAL = 0;
	const static int nOPSTARTSWITH = 1;
	
protected:
	string m_strValue;
	
public:
	BBPerceptionString();
	virtual ~BBPerceptionString();
	
	string HumanReadable();
	string HumanReadable(int n_op);
	bool Eval(int n_op);
	bool Eval(int n_op, BBPerception& c_perception);
	bool IsOpUnary(int n_op);
	string GetValue();
	virtual BBPerception& CreateRandomTypePerception();
};
}

#endif //_BBPERCEPTIONSTRING_H

