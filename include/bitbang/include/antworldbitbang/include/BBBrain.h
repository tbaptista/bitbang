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
#if !defined(EA_9FCD575C_962B_4a82_ACD4_C6D1EA4E8193__INCLUDED_)
#define EA_9FCD575C_962B_4a82_ACD4_C6D1EA4E8193__INCLUDED_

#include "BBAction.h"
#include "BBPerception.h"

#include <list>
#include <string>

using namespace std; 

namespace bitbang
{
	
class BBObject;

/*!
 * \brief Abstract class that defines the base of agent brains.
 *
 * To accomodate several types of brains, this base class defines the minimum
 * interface requirements for the impletation classes.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2005-06-02
 *
 * \see BBRuleList
 *
 */
class BBBrain
{

public:
	BBBrain();
	virtual ~BBBrain();
	virtual BBBrain* Clone(BBActionList& target_action_list, BBPerceptionList& target_perception_list) = 0;
	/*!
	 * \brief Decide what actions to take.
	 *
	 * \return List of actions to execute.
	 *
	 */
	virtual list<BBAction*> Think() = 0;
	void SetAgent(BBObject* p_agent){m_pAgent = p_agent;};
	BBObject* GetAgent(){return m_pAgent;};
	virtual string HumanReadable();
	
protected:
	BBObject* m_pAgent;
};
}

#endif // !defined(EA_9FCD575C_962B_4a82_ACD4_C6D1EA4E8193__INCLUDED_)
