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
#include "BBAction.h"

namespace bitbang
{

/*!
 * \brief Constructor.
 *
 */
BBAction::BBAction()
{
	m_bIsTimeable = false;
	m_bIsFlaggable = false;
	m_bIsRuleBound = false;
	m_bActive = false;
	m_nTimeout = 0;
	m_StartTime = 0;
	m_bStarted = false;
	m_bOwnedByAgent = false;
}


/*!
 * \brief Destructor.
 * 
 */
BBAction::~BBAction()
{

}


/*!
 * \brief Get the name of the action.
 * 
 * \return 
 * A string with the name of the action.
 *
 */
string BBAction::GetName()
{
	return m_strName;
}

/*!
 * \brief Sets the name of the action.
 * 
 * \param str_new_val 
 * A string with the new value for the name.
 *
 */
void BBAction::SetName(string str_new_val)
{
	m_strName = str_new_val;
}

/*!
 * \brief Is this action timeable?
 * 
 * \return 
 * True if the action is timeable, false otherwise.
 *
 */
bool BBAction::IsTimeable()
{
	return m_bIsTimeable;
}

/*!
 * \brief IS this action flaggable?
 * 
 * \return 
 * True if the action is flaggable, false otherwise.
 *
 */
bool BBAction::IsFlaggable()
{
	return m_bIsFlaggable;
}

/*!
 * \brief Is this action rule bound?
 * 
 * An action is rule bound if it remains active while the cognition keeps
 * returning the action.
 *
 * \return 
 * True is the action is rule bound, false otherwise.
 *
 */
bool BBAction::IsRuleBound()
{
	return m_bIsRuleBound;
}

/*!
 * \brief Get the timeout for this action.
 * 
 * \return 
 * The timeout for this action.
 *
 */
int BBAction::GetTimeout()
{
	return m_nTimeout;
}

/*!
 * \brief Is this action active?
 * 
 * \return True if the action is active, false otherwise.
 *
 */
bool BBAction::IsActive()
{
	return m_bActive;
}
	
/*!
 * \brief Activate the action.
 * 
 * This version can only be used for non-timeable actions.
 * For timeable actions please use the \ref BBAction::Activate(BBTime cur_time)
 * method.
 */
void BBAction::Activate()
{
	m_bActive = true;
}

/*!
 * \brief Activate the action.
 *
 * This version of the method is used for timeable actions.
 * 
 * \param cur_time The current time. Used for timeable actions.
 *
 */
void BBAction::Activate(BBTime cur_time)
{
	if (m_bIsTimeable)
	{
		m_StartTime = cur_time;
	}
	
	m_bActive = true;
}

/*!
 * \brief De-activate the action.
 *
 */
void BBAction::DeActivate()
{
	m_bActive = false;
}

/*!
 * \brief Update the time for the action.
 * If the time passed since the action was activated, this method de-activates
 * the action by calling \ref BBAction::DeActivate().
 * 
 * \param cur_time The current time.
 *
 */
void BBAction::UpdateTime(BBTime cur_time)
{
	if (cur_time - m_StartTime >= m_nTimeout)
	{
		DeActivate();
	}
}

/*!
 * \brief Compares this action to another.
 * Two actions are considered equal if they point to the same object.
 *
 * \param c_action The action to compare to.
 * \return True if the actions are the same.
 *
 */
bool BBAction::Equals(BBAction& c_action)
{
	if (this == &c_action)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*!
 * \brief The action execute function.
 * 
 * This is the entry point to the action. This method will treat the flaggable,
 * timeable, and rule bound states of the action and call the OnActivate,
 * OnDeactivate, or OnExecute methods where applicable
 * 
 * \param p_agent 
 * The pointer to the agent that is executing this action.
 *
 */
void BBAction::Execute(BBObject* p_agent)
{
	if (m_bActive)
	{
		if (m_bStarted)
		{
			//continue action
			OnExecute(p_agent);
		}
		else
		{
			//start the action
			OnActivate(p_agent);
			m_bStarted = true;
		}
	}
	else
	{
		if (m_bIsFlaggable)
		{
			//stop the action
			OnDeactivate(p_agent);
			m_bStarted = false;
		}
		else
		{
			//execute atomic action
			OnExecute(p_agent);
		}
	}
}

}
