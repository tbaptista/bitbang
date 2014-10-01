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

#ifndef __BitBangSE__CEventReceiver__
#define __BitBangSE__CEventReceiver__

#include "irrlicht.h"

using namespace irr;

class CEventHandler;

class CEventReceiver: public IEventReceiver
{
public:
    CEventReceiver(CEventHandler* pHandler);
    
    virtual bool OnEvent(const SEvent& event);
    
    void SetEventHandler(CEventHandler* pHandler) {m_pEventHandler = pHandler;};
    
private:
    CEventHandler* m_pEventHandler;
};

#endif /* defined(__BitBangSE__CEventReceiver__) */
