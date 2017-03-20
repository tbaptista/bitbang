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

#ifndef _BBWORLDINTERFACE_H
#define _BBWORLDINTERFACE_H

#include "BBTypes.h"
#include "BBObject.h"

namespace bitbang
{
class BBWorldInterface
{
public:
	virtual void RegisterObject(BBObject& object) = 0;
	virtual void RemoveObject(int n_id) = 0;
	virtual BBObject* GetObject(int n_id) = 0;
	virtual BBTime GetTime() = 0;
	virtual void LogDynamicStats() = 0;
};
}

#endif //_BBWORLDINTERFACE_H


