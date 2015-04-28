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
#include "BBRuleList.h"

#include "BBRule.h"
#include "BBWorld.h"
#include "BBRandomGenerator.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>

using namespace std;

namespace bitbang
{

/*!
 * \brief Constructor.
 *
 */
BBRuleList::BBRuleList()
{
	m_nMaxConditions = 1;
}

/*!
 * \brief Constructor with random initialization.
 *
 * This constructor will initialize the rule list with a random collection of
 * rules, based on the parameters passed.
 *
 * \param n_max_rules The maximum number of rules to create.
 * \param n_min_rules The minimum number of rules to create.
 * \param n_max_conditions The maximum number of conditions for each rule.
 * \param action_list The action list.
 * \param perception_list The perception list.
 *
 */
BBRuleList::BBRuleList(int n_max_rules, int n_min_rules, int n_max_conditions, BBActionList& action_list, BBPerceptionList& perception_list)
{
	m_nMaxConditions = n_max_conditions;
	
	int nSpan = n_max_rules - n_min_rules + 1;
	int nRules = n_min_rules + (g_RandomGenerator.RandInt(nSpan));
	
	for (int i = 0; i < nRules; i++)
	{
		BBRule* pRule = new BBRule(n_max_conditions, action_list, perception_list);
		AddRule(pRule);
	}
}


/*!
 * \brief Destructor.
 *
 * Deletes all the rules in the list.
 *
 */
BBRuleList::~BBRuleList()
{
	BBRuleListType::iterator iRule;

	for (iRule = m_RuleList.begin(); iRule != m_RuleList.end(); iRule++)
	{				
		delete *iRule;			
	}

	m_RuleList.clear();
}

BBBrain* BBRuleList::Clone(BBActionList& target_action_list, BBPerceptionList& target_perception_list)
{
	BBRuleList* pNewRuleList = new BBRuleList();
	BBRuleListType::iterator iRule;
	BBRule* pNewRule;
	
	for (iRule = m_RuleList.begin(); iRule != m_RuleList.end(); iRule++)
	{
		pNewRule = (*iRule)->Clone(target_action_list, target_perception_list);
		if (pNewRule != NULL)
		{
			pNewRuleList->AddRule(pNewRule);
		}
		else
		{
			//ERROR
			delete pNewRuleList;
			printf("\nError cloning a rule.");
			return NULL;
		}
	}
	
	return pNewRuleList;
}

/*!
 * \brief Decide what actions to take.
 *
 * This method implements the abstract method of the class that returns the
 * action to take. In this cognition the action returned is the one of the first
 * rule evaluated to true.
 *
 * \return List of actions to take.
 */
list<BBAction*> BBRuleList::Think()
{
	list<BBAction*> outputList;
	
	BBRuleListType::iterator iRule;

	for (iRule = m_RuleList.begin(); iRule != m_RuleList.end(); iRule++)
	{				
		if ((*iRule)->Eval())
		{
			outputList.push_back(&((*iRule)->GetAction()));
			return outputList;
		}
	}

	return outputList;
}

/*!
 * \brief Add a rule to the rule list.
 *
 * \param p_rule The rule to add.
 *
 */
void BBRuleList::AddRule(BBRule* p_rule)
{
	m_RuleList.push_back(p_rule);
}

void BBRuleList::MutateList(float f_probability, BBActionList& action_list, BBPerceptionList& perception_list)
{
	BBRuleListType::iterator iRule;
	iRule = m_RuleList.begin();
	while (iRule != m_RuleList.end())
	{
		if (g_RandomGenerator.RandProb() <= f_probability)
		{
			BBRule* pRule = *iRule;
			iRule = m_RuleList.erase(iRule);
			delete pRule;
			
			BBRule* pNewRule = new BBRule(m_nMaxConditions, action_list, perception_list);
			iRule = m_RuleList.insert(iRule, pNewRule);
		}
		
		iRule++;
	}		
}

void BBRuleList::MutateDelete(float f_probability)
{
	if (m_RuleList.size() <= 1)
	{
		return;
	}

	if (g_RandomGenerator.RandProb() <= f_probability)
	{
		int nRule = g_RandomGenerator.RandInt(m_RuleList.size());
		BBRuleListType::iterator iRule;
		iRule = m_RuleList.begin();
		for (int i = 0; i < nRule; i++)
		{
			iRule++;
		}
		BBRule* pRule = *iRule;
		iRule = m_RuleList.erase(iRule);
		delete pRule;
	}
}

void BBRuleList::MutateAdd(float f_probability, BBActionList& action_list, BBPerceptionList& perception_list)
{
	if (g_RandomGenerator.RandProb() <= f_probability)
	{
		BBRule* pNewRule = new BBRule(m_nMaxConditions, action_list, perception_list);
		
		BBRuleListType::iterator iRule;
		if (m_RuleList.size() > 0)
		{
			int nRule = g_RandomGenerator.RandInt(m_RuleList.size());
			iRule = m_RuleList.begin();
			for (int i = 0; i < nRule; i++)
			{
				iRule++;
			}
			m_RuleList.insert(iRule, pNewRule);
		}
		else
		{
			m_RuleList.push_back(pNewRule);	
		}
	}
}

void BBRuleList::MutateRules(float f_probability, BBActionList& action_list, BBPerceptionList& perception_list)
{
	BBRuleListType::iterator iRule;
	for (iRule = m_RuleList.begin(); iRule != m_RuleList.end(); iRule++)
	{
		(*iRule)->Mutate(f_probability, action_list, perception_list);
	}
}

void BBRuleList::MutateOrder(float f_probability)
{
	BBRuleListType::iterator iRule;
	for (iRule = m_RuleList.begin(); iRule != m_RuleList.end(); iRule++)
	{
		if (g_RandomGenerator.RandProb() <= f_probability)
		{
			BBRule* pRule = (*iRule);
			iRule = m_RuleList.erase(iRule);
			if (iRule != m_RuleList.begin())
			{
				iRule--;
			}
			m_RuleList.push_front(pRule);
		}
	}
}
	
void BBRuleList::MutateOrder2(float f_probability)
{
	BBRuleListType::iterator iRule;
	for (iRule = m_RuleList.begin(); iRule != m_RuleList.end(); iRule++)
	{
		if (g_RandomGenerator.RandProb() <= f_probability)
		{
			BBRule* pRule = (*iRule);
			iRule = m_RuleList.erase(iRule);
			if (iRule != m_RuleList.begin())
			{
				iRule--;
			}
			m_RuleList.insert(iRule, pRule);
		}
	}
}

/*!
 * \brief Get the size of the rule list.
 * The size of the Rule List brain is defined as the total number of conditions
 * that it has.
 *
 * \return The size of the brain (number of conditions).
 *
 */
int BBRuleList::GetSize()
{
	int nSize = 0;
	BBRuleListType::iterator iRule;
	
	for (iRule = m_RuleList.begin(); iRule != m_RuleList.end(); iRule++)
	{
		nSize += (*iRule)->GetSize();
	}
	
	return nSize;
}
	
/*!
 * \brief Get the size of the rule list in number of rules.
 *
 * \return The size of the brain (number of rules).
 *
 */
int BBRuleList::GetSizeRules()
{	
	return m_RuleList.size();
}

/*!
 * \brief Get the number of used rules.
 * A rule is considered used if it has evaluated to true at leats once.
 *
 * \return The number of used rules.
 *
 */	
int BBRuleList::GetUsedRules()
{
	int nRules = 0;
	BBRuleListType::iterator iRule;
	
	for (iRule = m_RuleList.begin(); iRule != m_RuleList.end(); iRule++)
	{
		if ((*iRule)->IsUsed())
		{
			nRules++;
		}
	}
	
	return nRules;
}
	

/*!
 * \brief Return a human readable string representing the brain.
 *
 * \return The brain as a string.
 *
 */
string BBRuleList::HumanReadable()
{
	ostringstream strReturn;
	
	BBRuleListType::iterator iRule;
	
	for (iRule = m_RuleList.begin(); iRule != m_RuleList.end(); iRule++)
	{
		strReturn << (*iRule)->HumanReadable() << endl;
	}
	
	return strReturn.str();
}
    

int BBRuleList::GetRulesWithAction(const std::string& str_action_name)
{
    int nCount = 0;
    
    BBRuleListType::iterator iRule;
    
    for (iRule = m_RuleList.begin(); iRule != m_RuleList.end(); iRule++)
    {
        if ((*iRule)->HasAction(str_action_name))
        {
            nCount++;
        }
    }
    
    return nCount;
}
    
    
int BBRuleList::GetRulesWithPerception(const std::string& str_perception_name)
{
    int nCount = 0;
    
    BBRuleListType::iterator iRule;
    
    for (iRule = m_RuleList.begin(); iRule != m_RuleList.end(); iRule++)
    {
        if ((*iRule)->HasPerception(str_perception_name))
        {
            nCount++;
        }
    }
    
    return nCount;
}

}
