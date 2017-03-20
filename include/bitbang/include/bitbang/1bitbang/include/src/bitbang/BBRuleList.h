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
#ifndef _BBRULELIST_H_
#define _BBRULELIST_H_

#include <list>
#include <string>

#include "BBBrain.h"
#include "BBAction.h"
#include "BBPerception.h"

using namespace std;

namespace bitbang
{

class BBRule;
typedef list<BBRule*> BBRuleListType;

/*!
 * \brief This class derives from BBBrain to define a rule list brain.
 *
 * It is a simple list of rules that are evaluated and the first that is true
 * selects the action to activate.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2005-06-07
 *
 * \see BBRule | BBBrain
 */
class BBRuleList : public BBBrain
{
protected:
	BBRuleListType m_RuleList;
	int m_nMaxConditions;

public:
	BBRuleList();
	BBRuleList(int n_max_rules, int n_min_rules, int n_max_conditions, BBActionList& action_list, BBPerceptionList& perception_list);
	virtual ~BBRuleList();
	virtual BBBrain* Clone(BBActionList& target_action_list, BBPerceptionList& target_perception_list);
	virtual list<BBAction*> Think();
	virtual void AddRule(BBRule* p_rule);
	void MutateList(float f_probability, BBActionList& action_list, BBPerceptionList& perception_list);
	void MutateDelete(float f_probability);
	void MutateAdd(float f_probability, BBActionList& action_list, BBPerceptionList& perception_list);
	void MutateRules(float f_probability, BBActionList& action_list, BBPerceptionList& perception_list);
	void MutateOrder(float f_probability);
	void MutateOrder2(float f_probability);
    
    string HumanReadable();
	
    // Stats
    int GetSize();
	int GetSizeRules();
	int GetUsedRules();
    int GetRulesWithAction(const std::string& str_action_name);
    int GetRulesWithPerception(const std::string& str_perception_name);
};
}


#endif // _BBRULELIST_H_

