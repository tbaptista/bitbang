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

#include "CDefaultEventHandler.h"

#include "CWorld.h"
#include "CSimObject.h"

#include "irrlicht.h"

#include <stdio.h>

using namespace bitbang;

CDefaultEventHandler::CDefaultEventHandler(CWorld* p_world)
{
	if (p_world != NULL)
	{
		m_pWorld = p_world;
	}
	else
	{
		cout << "Error: Tried to create CDefaultEventHandler with null CWorld" << endl;
		exit (1);
	}
}

CDefaultEventHandler::~CDefaultEventHandler()
{
}

bool CDefaultEventHandler::OnKeyDown(int n_key_code, int c_char, bool b_control, bool b_shift)
{
	cerr << "Executing!" << endl;
	switch (n_key_code)
	{
		case irr::KEY_SPACE:						//Pause the simulation
			if (m_pWorld->IsPaused())
			{
				m_pWorld->Resume();
			}
			else
			{
				m_pWorld->Pause();
			}
			return true;
			break;
		case irr::KEY_F2:						//Toggle real time
			if (m_pWorld->GetRealTime())
			{
				m_pWorld->SetRealTime(false);
			}
			else
			{
				m_pWorld->SetRealTime(true);
			}
			return true;
			break;
		case irr::KEY_F3:						//Toggle the drawing of graphics
			if (m_pWorld->GetDrawGraphics())
			{
				m_pWorld->SetDrawGraphics(false);
			}
			else
			{
				m_pWorld->SetDrawGraphics(true);
			}
			return true;
			break;
		case irr::KEY_F4:						//Toggle the drawing of the world info box
			if (m_pWorld->GetShowInfo())
			{
				m_pWorld->SetShowInfo(false);
			}
			else
			{
				m_pWorld->SetShowInfo(true);
			}
			return true;
			break;
		case irr::KEY_KEY_D:
			if (m_pWorld->GetDrawPhysicsDebug())
			{
				m_pWorld->SetDrawPhysicsDebug(false);
			}
			else
			{
				m_pWorld->SetDrawPhysicsDebug(true);
			}
			
		default:
			return false;
	}
	return false;
}

bool CDefaultEventHandler::OnLeftMouseDown(int n_x, int n_y)
{
	int nSelectedObjectID;
	CSimObject* pSelectedObject;
	
	nSelectedObjectID = m_pWorld->GetObjectFromScreenCoordinates(n_x, n_y);
	if (nSelectedObjectID != BBObject::NULL_ID)
	{
		pSelectedObject = dynamic_cast<CSimObject*>(m_pWorld->GetObject(nSelectedObjectID));
		if (pSelectedObject != NULL)
		{
			m_pWorld->SetSelectedObject(pSelectedObject);
			return true;
		}
		else
		{
			cerr << "Error in dynamic cast of selected object to CSimObject!" << endl;
			return false;
		}
	}
	else
	{
		m_pWorld->SetSelectedObject(NULL);
	}
	
	return false;
}

bool CDefaultEventHandler::OnMiddleMouseDown(int n_x, int n_y)
{
	if (m_pWorld->IsPaused())
	{
		m_pWorld->Resume();
	}
	else
	{
		m_pWorld->Pause();
	}
	return true;
}
