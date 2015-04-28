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
#include "BBRule.h"
#include "BBWorld.h"
#include "BBRandomGenerator.h"
#include "BBRuleCondition.h"

#include <stdlib.h>

namespace bitbang
{

/*!
 * \brief Constructor.
 *
 */
BBRule::BBRule()
{
	m_pAction = NULL;
	m_bDeleteAction = false;
	m_bUsed = false;
}

/*!
 * \brief Constructor with random initialization.
 *
 * This constructor will initialize the rule with random values.
 *
 * \param n_max_conditions The maximum number of conditions for this rule.
 * \param action_list The action list.
 * \param perception_list The perception list.
 *
 * \todo Implement case for binary conditions.
 */
BBRule::BBRule(int n_max_conditions, BBActionList& action_list, BBPerceptionList& perception_list)
{
	m_pAction = NULL;
	m_bDeleteAction = false;
	m_bUsed = false;
	
	int nConditions = g_RandomGenerator.RandInt(n_max_conditions) + 1;
	int nSelectedAction = 0;

	for (int i = 0; i < nConditions; i++)
	{
		BBRuleCondition* pCondition = new BBRuleCondition(perception_list);
		AddCondition(*pCondition);
	}

	nSelectedAction = g_RandomGenerator.RandInt((int)action_list.size());
	BBAction* pAction = action_list[nSelectedAction];
	SetAction(pAction);
}
	

/*!
 * \brief Copy Constructor
 *
 */
BBRule::BBRule(const BBRule& rule)
{
	m_bUsed = false;
	m_bDeleteAction = false;
	m_pAction = rule.m_pAction;
	
	BBRuleConditionList::const_iterator iCondition;
	
	for (iCondition = rule.m_RuleConditionList.begin(); iCondition != rule.m_RuleConditionList.end(); iCondition++)
	{
		BBRuleCondition* pNewCondition = new BBRuleCondition(*(*iCondition));
		AddCondition(*pNewCondition);
	}
}

/*!
 * \brief Destructor.
 *
 */
BBRule::~BBRule()
{
	if (m_bDeleteAction)
	{
		if (!m_pAction->IsOwnedByList())
		{
			delete m_pAction;
		}
	}
	
	BBRuleConditionList::iterator iCondition;
	for (iCondition = m_RuleConditionList.begin(); iCondition != m_RuleConditionList.end(); iCondition++)
	{
		delete (*iCondition);
	}	
}

/*!
* \brief Clone the rule.
*
* Clone this rule.
*
* \return Pointer to the cloned rule, NULL if an error occurs.
*
*/
BBRule* BBRule::Clone(BBActionList& target_action_list, BBPerceptionList& target_perception_list)
{
	BBRule* pNewRule = new BBRule();
	BBRuleConditionList::iterator iCondition;
	BBRuleCondition* pNewRuleCondition;
	
	string strActionName = m_pAction->GetName();
	BBAction* pNewAction = NULL;
	BBActionList::iterator iAction;
	for (iAction = target_action_list.begin(); iAction != target_action_list.end(); iAction++)
	{
		
		if ((*iAction)->GetName() == strActionName)
		{
			pNewAction = (*iAction);
		}
	}
	if (pNewAction == NULL)
	{
		//Action is not on the agent action list, so clone the source action
		pNewAction = m_pAction->Clone();
		if (pNewAction == NULL)
		{
			delete pNewRule;
			return NULL;
		}
		pNewRule->SetDeleteAction(true);
	}
	pNewRule->SetAction(pNewAction);
	
	for (iCondition = m_RuleConditionList.begin(); iCondition != m_RuleConditionList.end(); iCondition++)
	{
		pNewRuleCondition = (*iCondition)->Clone(target_perception_list);
		if (pNewRuleCondition != NULL)
		{
			pNewRule->AddCondition(*pNewRuleCondition);
		}
		else
		{
			delete pNewRule;
			return NULL;
		}
	}
	
	return pNewRule;
}

void BBRule::Mutate(float f_probability, BBActionList& action_list, BBPerceptionList& perception_list)
{
	BBRuleConditionList::iterator iCondition;
	for (iCondition = m_RuleConditionList.begin(); iCondition != m_RuleConditionList.end(); iCondition++)
	{
		if (g_RandomGenerator.RandProb() <= f_probability)
		{
			BBRuleCondition* pOldCondition =  (*iCondition);
			iCondition = m_RuleConditionList.erase(iCondition);
			delete pOldCondition;
			BBRuleCondition* pNewCondition = new BBRuleCondition(perception_list);
			m_RuleConditionList.insert(iCondition, pNewCondition);
			if (iCondition != m_RuleConditionList.begin())
			{
				iCondition--;
			}
		}
		else
		{
			(*iCondition)->Mutate(f_probability);
		}
	}
	
	if (g_RandomGenerator.RandProb() <= f_probability)
	{
		int nSelectedAction = g_RandomGenerator.RandInt((int)action_list.size());
		BBAction* pAction = action_list[nSelectedAction];
		SetAction(pAction);
	}
}

/*!
 * \brief Evaluate the rule.
 *
 * If all the condition in the condition list evaluate to true, then the rule is
 * also true.
 *
 * \return True if this rule is true, false otherwise.
 *
 */
bool BBRule::Eval()
{
	bool bResult = true;
	int nConditionCount = (int) m_RuleConditionList.size(); 

	if (nConditionCount > 0)
	{
		BBRuleConditionList::iterator iCondition;
		for (iCondition = m_RuleConditionList.begin(); iCondition != m_RuleConditionList.end(); iCondition++)
		{
			bResult = bResult && (*iCondition)->Eval();
		}
	}
	else
	{
		bResult = true;
	}
	
	if (bResult)
	{
		m_bUsed = true;
	}

	return bResult;
}
	
int BBRule::Edit(int n_funtion, BBRuleCondition& condition_match)
{
	int nEditions = 0;
	BBRuleConditionList::iterator iCondition;
	
	for (iCondition = m_RuleConditionList.begin(); iCondition != m_RuleConditionList.end(); iCondition++)
	{
		BBRuleCondition* pCondition = (*iCondition);
		if (pCondition->Matches(condition_match))
		{
			pCondition->Edit(n_funtion);
			nEditions++;
		}
	}
	
	return nEditions;
}

/*!
 * \brief Get the action for this rule.
 *
 * \return The action for this rule.
 *
 */
BBAction& BBRule::GetAction()
{
	return *m_pAction;
}

/*!
 * \brief Add a condition to this rule.
 *
 * \param c_condition The condition to add.
 *
 * \see BBRuleCondition
 *
 */
void BBRule::AddCondition(BBRuleCondition& c_condition)
{
	m_RuleConditionList.push_back(&c_condition);
}

/*!
 * \brief Return a human readable string representing the rule.
 *
 * \return The rule as a string.
 *
 */
string BBRule::HumanReadable()
{
	string strResult = "IF ";
	
	int nConditionCount = (int) m_RuleConditionList.size(); 
	
	if (nConditionCount > 0)
	{
		int i = 1;
		BBRuleConditionList::iterator iCondition;
		for (iCondition = m_RuleConditionList.begin(); iCondition != m_RuleConditionList.end(); iCondition++, i++)
		{
			strResult += (*iCondition)->HumanReadable();
			strResult += " ";
			if ((nConditionCount > 1) && (i < nConditionCount))
			{
				strResult += "AND ";
			}
		}
	}
	else
	{
		strResult += "true ";
	}
	
	strResult += "THEN ";
	strResult += m_pAction->GetName();
	
	if (m_bUsed)
	{
		strResult += " *";
	}
	
	return strResult;
}
	
/*!
 * \brief Get the size of the rule.
 * The size of a rule is defined as the number of conditions it has.
 *
 * \return The size of the rule.
 *
 */
int BBRule::GetSize()
{
	return (int)m_RuleConditionList.size();
}
    
bool BBRule::HasAction(const std::string& str_action_name)
{
    if (str_action_name.compare(m_pAction->GetName()) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool BBRule::HasPerception(const std::string& str_perception_name)
{
    bool bResult = false;
    
    BBRuleConditionList::iterator iCondition;
    for (iCondition = m_RuleConditionList.begin(); iCondition != m_RuleConditionList.end(); iCondition++)
    {
        if ((*iCondition)->HasPerception(str_perception_name))
        {
            bResult = true;
        }
    }
    
    return bResult;
}

}
