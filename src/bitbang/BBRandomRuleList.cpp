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
#include "BBRandomRuleList.h"
#include "BBRandomGenerator.h"
#include "BBRule.h"

namespace bitbang
{

/*!
 * \brief Constructor.
 *
 */
BBRandomRuleList::BBRandomRuleList()
{
}

/*!
 * \brief Constructor with random initialization.
 *
 * This constructor will initialize the rule list with a random collection of
 * rules, based on the parameters passed.
 *
 * \param n_max_rules The maximum number of rules to create.
 * \param n_max_conditions The maximum number of conditions for each rule.
 * \param action_list The action list.
 * \param perception_list The perception list.
 *
 */
	BBRandomRuleList::BBRandomRuleList(int n_max_rules, int n_min_rules, int n_max_conditions, BBActionList& action_list, BBPerceptionList& perception_list) :
		BBRuleList(n_max_rules, n_min_rules, n_max_conditions, action_list, perception_list)
{
	
}


/*!
 * \brief Destructor.
 *
 */
BBRandomRuleList::~BBRandomRuleList()
{

}


/*!
 * \brief Decide what actions to take.
 *
 * This method implements the abstract method of the class that returns the
 * action to take. In this cognition the action returned is randomly chosen from all the
 * rules evaluated to true.
 *
 * \return List of actions to take.
 */
list<BBAction*> BBRandomRuleList::Think()
{
	list<BBAction*> outputList;
	vector<BBAction*> vectorActions;
	
	BBRuleListType::iterator iRule;

	for (iRule = m_RuleList.begin(); iRule != m_RuleList.end(); iRule++)
	{				
		if ((*iRule)->Eval())
		{
			vectorActions.push_back(&((*iRule)->GetAction()));
		}
	}
	if (vectorActions.size() > 0)
	{
		int nAction = g_RandomGenerator.RandInt((int)vectorActions.size());
		outputList.push_back(vectorActions[nAction]);
	}

	return outputList;
}

}
