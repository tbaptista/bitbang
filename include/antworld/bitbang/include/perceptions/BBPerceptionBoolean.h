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

#ifndef _BBPERCEPTIONBOOLEAN_H
#define _BBPERCEPTIONBOOLEAN_H

#include "BBPerception.h"

namespace bitbang
{
/*!
 * \brief This class represents a boolean perception.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2005-06-15
 *
 * \see BBPerception
 */
class BBPerceptionBoolean : public BBPerception
{

public:
	const static int nOPTRUE;
	const static int nOPNOT;

protected:
	bool m_bValue;

public:
	BBPerceptionBoolean();
	~BBPerceptionBoolean();

	void SetValue(bool b_value){m_bValue = b_value;}

	string HumanReadable();
	string HumanReadable(int n_op);
	bool Eval(int n_op);
	bool Eval(int n_op, BBPerception& c_perception);
	bool IsOpUnary(int n_op);
	BBPerception& CreateRandomTypePerception();

};
}
#endif //_BBPERCEPTIONBOOLEAN_H
