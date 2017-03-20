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
#ifndef BBACTION_H
#define BBACTION_H

#include <iostream>
#include <vector>

#include "BBTypes.h"

namespace bitbang
{

class BBObject;
	
/*!
 * \brief This class defines an Action.
 *
 * This class defines an action that is available to an agent to execute. This
 * is the base class for all the actions.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2005-06-01
 *
 * \see BBObject | BBCognition
 */
class BBAction
{
protected:
	std::string m_strName;
	bool m_bIsTimeable;
	bool m_bIsFlaggable;
	bool m_bIsRuleBound;
	int m_nTimeout;
	bool m_bActive;
	bool m_bStarted;
	bool m_bOwnedByList;
	bool m_bOwnedByAgent;

private:
	BBTime m_StartTime;

public:
	BBAction();
	virtual ~BBAction();
	virtual BBAction* Clone(){return NULL;};
	std::string GetName();
	void SetName(std::string str_new_val);
	virtual void UpdateName(){};
	bool IsTimeable();
	bool IsFlaggable();
	bool IsRuleBound();
	int GetTimeout();
	bool IsActive();
	void Activate();
	void Activate(BBTime cur_time);
	void DeActivate();
	void UpdateTime(BBTime cur_time);
	bool Equals(BBAction& c_action);
	void Execute(BBObject* p_agent);
	bool IsOwnedByList() {return m_bOwnedByList;};
	bool IsOwnedByAgent() {return m_bOwnedByAgent;};
	void SetOwnedByList(bool b_owned_by_list) {m_bOwnedByList = b_owned_by_list;};
	void SetOwnedByAgent(bool b_owned_by_agent) {m_bOwnedByAgent = b_owned_by_agent;};

	/*!
	 * \brief Virtual method to be executed when the action is started.
	 *
	 * \param p_agent_int The agent that is calling this action.
	 *
	 */
	virtual void OnActivate(BBObject* p_agent) = 0;

	/*!
	 * \brief Virtual method to be executed when the action is stopped.
	 *
	 * \param p_agent_int The agent that is calling this action.
	 *
	 */
	virtual void OnDeactivate(BBObject* p_agent) = 0;

	/*!
	 * \brief Virtual method to be executed when the action is continuing the execution.
	 *
	 * \param p_agent_int The agent that is calling this action.
	 *
	 */
	virtual void OnExecute(BBObject* p_agent) = 0;
};
	
typedef vector<BBAction*> BBActionList;
}

#endif // BBACTION_H
