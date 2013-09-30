/*
 * BitBang (http://www.bitbang.org)
 * Copyright (C) 2004-2008 Tiago Baptista
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

#include "BBRuleListEditor.h"

#include "BBRule.h"
#include "BBRuleCondition.h"
#include "BBRandomGenerator.h"

namespace bitbang
{
	BBRuleListEditor::BBRuleListEditor()
	{
		m_fConcentration = 0;
		m_pRuleRuleCondition = NULL;
		m_nFunction = 0;
	}
	
	BBRuleListEditor::BBRuleListEditor(float f_concentration, int n_function, BBRuleCondition& condition)
	{
		m_fConcentration = f_concentration;
		m_nFunction = n_function;
		m_pRuleRuleCondition = &condition;
	}
	
	BBRuleListEditor::BBRuleListEditor(BBPerceptionList& perception_list)
	{
		m_fConcentration = g_RandomGenerator.RandProb();
		m_nFunction = g_RandomGenerator.RandInt(BBRuleCondition::MAX_EDIT_FUNCTIONS) + 1;
		m_pRuleRuleCondition = new BBRuleCondition(perception_list);
	}
	
	BBRuleListEditor::~BBRuleListEditor()
	{
		if (m_pRuleRuleCondition != NULL)
		{
			delete m_pRuleRuleCondition;
			m_pRuleRuleCondition = NULL;
		}
	}
	
	int BBRuleListEditor::Edit(BBRuleListType& rule_list)
	{
		int nEditions = 0;
		
		if (g_RandomGenerator.RandProb() < m_fConcentration)
		{
			BBRuleListType::iterator iRule;
			for (iRule = rule_list.begin(); iRule != rule_list.end(); iRule++)
			{
				nEditions += (*iRule)->Edit(m_nFunction, *m_pRuleRuleCondition);
			}
		}
		
		return nEditions;
	}
	
	BBRuleListEditor* BBRuleListEditor::Clone(BBPerceptionList& target_perception_list)
	{
		BBRuleListEditor* pNewEditor;
		
		BBRuleCondition* pNewCondition = m_pRuleRuleCondition->Clone(target_perception_list);
		if (pNewCondition != NULL)
		{
			pNewEditor = new BBRuleListEditor(m_fConcentration, m_nFunction, *pNewCondition);
		}
		else
		{
			cout << "Error cloning condition on BBRuleListEditor." << endl;
			return NULL;
		}
		
		return pNewEditor;
	}
	
	void BBRuleListEditor::Mutate(float f_probability)
	{
		if (m_pRuleRuleCondition != NULL)
		{
			m_pRuleRuleCondition->Mutate(f_probability);
		}
	}
}
