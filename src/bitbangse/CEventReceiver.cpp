/*
 * BitBang (http://www.bitbang.org)
 * Copyright (C) 2004-2014 Tiago Baptista
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

#include "CEventReceiver.h"
#include "CEventHandler.h"

CEventReceiver::CEventReceiver(CEventHandler* pHandler)
{
    m_pEventHandler = pHandler;
}

bool CEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        if (event.KeyInput.PressedDown)
        {
            return m_pEventHandler->OnKeyDown(event.KeyInput.Key,
                             event.KeyInput.Char,
                             event.KeyInput.Control,
                             event.KeyInput.Shift);
        }
        else
        {
            return m_pEventHandler->OnKeyUp(event.KeyInput.Key,
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
                return m_pEventHandler->OnLeftMouseDown(event.MouseInput.X, event.MouseInput.Y);
                break;
            case irr::EMIE_RMOUSE_PRESSED_DOWN:
                return m_pEventHandler->OnRightMouseDown(event.MouseInput.X, event.MouseInput.Y);
                break;
            case irr::EMIE_MMOUSE_PRESSED_DOWN:
                return m_pEventHandler->OnMiddleMouseDown(event.MouseInput.X, event.MouseInput.Y);
                break;
            case irr::EMIE_LMOUSE_LEFT_UP:
                return m_pEventHandler->OnLeftMouseUp(event.MouseInput.X, event.MouseInput.Y);
                break;
            case irr::EMIE_RMOUSE_LEFT_UP:
                return m_pEventHandler->OnRightMouseUp(event.MouseInput.X, event.MouseInput.Y);
                break;
            case irr::EMIE_MMOUSE_LEFT_UP:
                return m_pEventHandler->OnMiddleMouseUp(event.MouseInput.X, event.MouseInput.Y);
                break;
            case irr::EMIE_MOUSE_MOVED:
                return m_pEventHandler->OnMouseMove(event.MouseInput.X, event.MouseInput.Y);
                break;
            case irr::EMIE_MOUSE_WHEEL:
                return m_pEventHandler->OnMouseWheel(event.MouseInput.Wheel);
                break;
            default:
                return false;
                break;
        }
    }
    
    return false;
}

