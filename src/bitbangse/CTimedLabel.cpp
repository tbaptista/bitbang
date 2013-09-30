/*
 * BitBang (http://www.bitbang.org)
 * Copyright (C) 2004-2009 Tiago Baptista
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

#include "CTimedLabel.h"
#include "CWorld.h"

#include "irrlicht.h"

using namespace bitbang;

CTimedLabel::CTimedLabel(irr::scene::ISceneManager* p_smgr, irr::scene::ISceneNode* p_parent_node, BBTime current_time, BBTime timeout, string str_text) : CObjectLabel(p_smgr)
{
	m_EndTime = current_time + timeout;
	m_strText = str_text;
	
	//Create Graphics
	m_pNode = p_smgr->addBillboardTextSceneNode(NULL, CWorld::String2wchar(str_text), p_parent_node);
}

CTimedLabel::~CTimedLabel()
{
	if (m_pNode != NULL)
	{
		m_pNode->remove();
	}
}

bool CTimedLabel::Update(BBTime current_time)
{
	if (current_time >= m_EndTime)
	{
		return false;
	}
	else
	{
		return true;
	}
}
