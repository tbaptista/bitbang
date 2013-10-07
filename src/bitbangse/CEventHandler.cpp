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

#include "CEventHandler.h"

using namespace irr;

CEventHandler::CEventHandler()
{
}

CEventHandler::~CEventHandler()
{
}

bool CEventHandler::OnEvent(const SEvent& event)
{			
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		if (event.KeyInput.PressedDown)
		{
			return OnKeyDown(event.KeyInput.Key,
									event.KeyInput.Char,
									event.KeyInput.Control,
									event.KeyInput.Shift);
		}
		else
		{
			return OnKeyUp(event.KeyInput.Key,
									event.KeyInput.Char,
									event.KeyInput.Control,
									event.KeyInput.Shift);
		}
	}
	else if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		switch (event.MouseInput.Event)
		{
			case irr::EMIE_LMOUSE_PRESSED_DOWN:
				return OnLeftMouseDown(event.MouseInput.X, event.MouseInput.Y);
				break;
			case irr::EMIE_RMOUSE_PRESSED_DOWN:
				return OnRightMouseDown(event.MouseInput.X, event.MouseInput.Y);
				break;
			case irr::EMIE_MMOUSE_PRESSED_DOWN:
				return OnMiddleMouseDown(event.MouseInput.X, event.MouseInput.Y);
				break;
			case irr::EMIE_LMOUSE_LEFT_UP:
				return OnLeftMouseUp(event.MouseInput.X, event.MouseInput.Y);
				break;
			case irr::EMIE_RMOUSE_LEFT_UP:
				return OnRightMouseUp(event.MouseInput.X, event.MouseInput.Y);
				break;
			case irr::EMIE_MMOUSE_LEFT_UP:
				return OnMiddleMouseUp(event.MouseInput.X, event.MouseInput.Y);
				break;
			case irr::EMIE_MOUSE_MOVED:
				return OnMouseMove(event.MouseInput.X, event.MouseInput.Y);
				break;
			case irr::EMIE_MOUSE_WHEEL:
				return OnMouseWheel(event.MouseInput.Wheel);
				break;
            default:
                return false;
                break;
		}
	}
	
	return false;
}

