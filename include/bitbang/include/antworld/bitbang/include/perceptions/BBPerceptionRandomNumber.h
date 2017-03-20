/*
 * BitBang (http://www.bitbang.org)
 * Copyright (C) 2004-2011 Tiago Baptista
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

#ifndef _BBPERCEPTIONRANDOMNUMBER_H
#define _BBPERCEPTIONRANDOMNUMBER_H

#include "BBPerceptionNumber.h"

namespace bitbang
{
	class BBPerceptionRandomNumber : public BBPerceptionNumber
	{
	public:
		BBPerceptionRandomNumber();
		BBPerceptionRandomNumber(int n_range);
		virtual ~BBPerceptionRandomNumber();
		virtual BBPerception* Clone();
		
		virtual void Update(BBObject& c_agent);
	};
}

#endif //_BBPERCEPTIONRANDOMNUMBER_H
