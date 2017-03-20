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

#ifndef C_TIMED_LABEL_H
#define C_TIMED_LABEL_H

#include "CObjectLabel.h"
#include <BBTypes.h>

#include <string>

namespace irr{
namespace scene{
	class ISceneNode;
	class ISceneManager;
	class IBillboardTextSceneNode;
}	
}

class CTimedLabel : public CObjectLabel
{
public:
	CTimedLabel(irr::scene::ISceneManager* p_smgr, irr::scene::ISceneNode* p_parent_node, bitbang::BBTime current_time, bitbang::BBTime timeout, std::string str_text);
	virtual ~CTimedLabel();
	
	virtual bool Update(bitbang::BBTime current_time);
	
private:
	bitbang::BBTime m_EndTime;
	std::string m_strText;
	
	irr::scene::IBillboardTextSceneNode* m_pNode;
};

#endif //C_TIMED_LABEL_H


