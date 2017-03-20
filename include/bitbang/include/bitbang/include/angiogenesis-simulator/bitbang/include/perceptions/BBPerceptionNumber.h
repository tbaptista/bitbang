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
#ifndef _BBPERCEPTIONNUMBER_H
#define _BBPERCEPTIONNUMBER_H

#include "BBPerception.h"

namespace bitbang
{
/*!
 * \brief Perception of type number base class.
 *
 * Defines the generic perception whose value is a number. This class cannot be
 * instatiated as it has purely virtual methods. To use, derive a class.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2005-06-14
 *
 */
class BBPerceptionNumber : public BBPerception
{
public:
	//Operations
	const static int nOPEQUAL;
	const static int nOPGREATER;
	const static int nOPLESS;

protected:
	double m_dValue;
	double m_dRange;
	bool m_bInt;

public:
	BBPerceptionNumber();
	virtual ~BBPerceptionNumber();

	string HumanReadable();
	string HumanReadable(int n_op);
	bool Eval(int n_op);
	bool Eval(int n_op, BBPerception& c_perception);
	bool IsOpUnary(int n_op);
	double GetValue();
	virtual BBPerception& CreateRandomTypePerception();
	void SetRange(double d_range);
};
}



#endif // _BBPERCEPTIONNUMBER_H
