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

#ifndef CEVENTHANDLER_H_
#define CEVENTHANDLER_H_

#include <irrlicht.h>

/*!
 * \brief This class defines the interface for a keyboard / mouse event handler.
 *
 * \version 1.0
 * BitBang Simulation Engine
 *
 * \date 2005-10-28
 *
 */
class CEventHandler : public irr::IEventReceiver
{
public:
	CEventHandler();
	virtual ~CEventHandler();
	
	bool OnEvent(const irr::SEvent& event);
	
	virtual bool OnKeyDown(int n_key_code, int c_char, bool b_control, bool b_shift){return false;};
	virtual bool OnKeyUp(int n_key_code, int c_char, bool b_control, bool b_shift){return false;};
	virtual bool OnLeftMouseDown(int n_x, int n_y){return false;};
	virtual bool OnRightMouseDown(int n_x, int n_y){return false;};
	virtual bool OnMiddleMouseDown(int n_x, int n_y){return false;};
	virtual bool OnLeftMouseUp(int n_x, int n_y){return false;};
	virtual bool OnRightMouseUp(int n_x, int n_y){return false;};
	virtual bool OnMiddleMouseUp(int n_x, int n_y){return false;};
	virtual bool OnMouseMove(int n_x, int n_y){return false;};
	virtual bool OnMouseWheel(float f_wheel){return false;};
};

#endif /*CEVENTHANDLER_H_*/
