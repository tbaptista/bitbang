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

#include "BBRuleListEditype.h"

#include "BBRule.h"
#include "BBRuleListEditor.h"
#include "BBRandomGenerator.h"

namespace bitbang
{
	BBRuleListEditype::BBRuleListEditype()
	{
	}
	
	BBRuleListEditype::BBRuleListEditype(int n_min_editors, int n_max_editors, int n_max_rules, int n_min_rules, int n_max_conditions, BBActionList& action_list, BBPerceptionList& perception_list)
	: BBRuleList(n_max_rules, n_min_rules, n_max_conditions, action_list, perception_list)
	{
		//Generate Random editors
		int nSpan = n_max_editors - n_min_editors + 1;
		int nEditors = n_min_editors + g_RandomGenerator.RandInt(nSpan);
		
		for (int i = 0; i < nEditors; i++)
		{
			BBRuleListEditor* pEditor = new BBRuleListEditor(perception_list);
			AddEditor(pEditor);
		}
		
		//Save Base
		SaveBase();
	}
	
	BBRuleListEditype::~BBRuleListEditype()
	{
		BBRuleListEditorList::iterator iEditor;
		for (iEditor = m_EditorList.begin(); iEditor != m_EditorList.end(); iEditor++)
		{
			delete (*iEditor);
		}
		m_EditorList.clear();
		
		BBRuleListType::iterator iRule;
		for (iRule = m_BaseRuleList.begin(); iRule != m_BaseRuleList.end(); iRule++)
		{
			delete (*iRule);
		}
		m_BaseRuleList.clear();
	}
	
	void BBRuleListEditype::AddEditor(BBRuleListEditor* p_editor)
	{
		m_EditorList.push_back(p_editor);
	}
	
	BBBrain* BBRuleListEditype::Clone(BBActionList& target_action_list, BBPerceptionList& target_perception_list)
	{
		BBRuleListEditype* pNewRuleList = new BBRuleListEditype();
		BBRuleListType::iterator iRule;
		BBRule* pNewRule;
		
		for (iRule = m_BaseRuleList.begin(); iRule != m_BaseRuleList.end(); iRule++)
		{
			pNewRule = (*iRule)->Clone(target_action_list, target_perception_list);
			if (pNewRule != NULL)
			{
				pNewRuleList->AddRule(pNewRule);
			}
			else
			{
				delete pNewRuleList;
				cout << "Error cloning a rule." << endl;
				return NULL;
			}
		}
		
		BBRuleListEditor* pNewEditor;
		BBRuleListEditorList::iterator iEditor;
		for (iEditor = m_EditorList.begin(); iEditor != m_EditorList.end(); iEditor++)
		{
			pNewEditor = (*iEditor)->Clone(target_perception_list);
			if (pNewEditor != NULL)
			{
				pNewRuleList->AddEditor(pNewEditor);
			}
			else
			{
				delete pNewRuleList;
				cout << "Error cloning an editor." << endl;
				return NULL;
			}
		}
		
		return pNewRuleList;
	}
	
	void BBRuleListEditype::MutateEditype(float f_probability)
	{
		BBRuleListEditorList::iterator iEditor;
		
		for (iEditor = m_EditorList.begin(); iEditor != m_EditorList.end(); iEditor++)
		{
			(*iEditor)->Mutate(f_probability);
		}
	}
	
	void BBRuleListEditype::SaveBase()
	{
		BBRuleListType::iterator iRule;
		
		for (iRule = m_RuleList.begin(); iRule != m_RuleList.end(); iRule++)
		{
			BBRule* pNewRule = new BBRule(*(*iRule));
			m_BaseRuleList.push_back(pNewRule);
		}
	}
	
	int BBRuleListEditype::Edit()
	{
		int nEditions = 0;
		BBRuleListEditorList::iterator iEditor;
		
		for (iEditor = m_EditorList.begin(); iEditor != m_EditorList.end(); iEditor++)
		{
			nEditions += (*iEditor)->Edit(m_RuleList);
		}
		
		return nEditions;
	}
}
