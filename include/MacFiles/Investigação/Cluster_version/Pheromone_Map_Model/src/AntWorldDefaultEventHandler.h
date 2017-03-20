/*
 * BitBang (http://www.bitbang.org)
 * Copyright (C) 2004-2013 Tiago Baptista and António Lima
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

#ifndef AntWorldDefaultEventHandler_H_
#define AntWorldDefaultEventHandler_H_

#include "CDefaultEventHandler.h"

#include <stdio.h>

class AntWorld;

class AntWorldDefaultEventHandler : public CDefaultEventHandler
{
public:
	AntWorldDefaultEventHandler(AntWorld* p_world);
	virtual ~AntWorldDefaultEventHandler();
	
	virtual bool OnKeyDown(int n_key_code, int c_char, bool b_control, bool b_shift);
	
private:
	AntWorld* m_pAntWorld;
};

#endif //AntWorldDefaultEventHandler_H_