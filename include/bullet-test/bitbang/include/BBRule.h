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
#if !defined(EA_B30FD4F6_FEA1_436b_9EAF_76D39AC5F820__INCLUDED_)
#define EA_B30FD4F6_FEA1_436b_9EAF_76D39AC5F820__INCLUDED_

#include <list>
#include <iostream>

#include "BBAction.h"
#include "BBPerception.h"

using namespace std;

namespace bitbang
{

class BBRuleCondition;
typedef list<BBRuleCondition*> BBRuleConditionList;


/*!
 * \brief This class represents a rule.
 *
 * This class is used by the \ref BBRuleList cognition. A rule is defined here
 * as a list of conditions linked by ANDs. The rule also defines the action that
 * should be executed when the rule evaluates to true.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2005-06-07
 *
 * \see BBRuleCondition | BBRuleList
 */
class BBRule
{
private:
	BBRuleConditionList m_RuleConditionList;
	BBAction* m_pAction;
	bool m_bDeleteAction;
	bool m_bUsed;

public:
	BBRule();
	BBRule(int n_max_conditions, BBActionList& action_list, BBPerceptionList& perception_list);
	BBRule(const BBRule& rule);
	virtual ~BBRule();
	BBRule* Clone(BBActionList& target_action_list, BBPerceptionList& target_perception_list);
	void Mutate(float f_probability, BBActionList& action_list, BBPerceptionList& perception_list);
	bool Eval();
	int Edit(int n_function, BBRuleCondition& condition_match);
	BBAction& GetAction();
	void SetAction(BBAction* p_action){m_pAction = p_action;};
	void AddCondition(BBRuleCondition& c_condition);
	void SetDeleteAction(bool b_set) {m_bDeleteAction = b_set;};
	string HumanReadable();
	int GetSize();
    
    // Stats
	bool IsUsed() {return m_bUsed;};
    bool HasAction(const std::string& str_action_name);
    bool HasPerception(const std::string& str_perception_name);
};
}

#endif // !defined(EA_B30FD4F6_FEA1_436b_9EAF_76D39AC5F820__INCLUDED_)
