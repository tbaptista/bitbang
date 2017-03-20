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

#ifndef _BBRULELISTEDITYPE_H
#define _BBRULELISTEDITYPE_H

#include "BBRuleList.h"
#include <list>

using namespace std;

namespace bitbang
{
class BBRuleListEditor;
typedef list<BBRuleListEditor*> BBRuleListEditorList;

class BBRuleListEditype : public BBRuleList
{
public:
	BBRuleListEditype();
	BBRuleListEditype(int n_min_editors, int n_max_editors, int n_max_rules, int n_min_rules, int n_max_conditions, BBActionList& action_list, BBPerceptionList& perception_list);
	virtual ~BBRuleListEditype();
	
	virtual void AddEditor(BBRuleListEditor* p_editor);
	virtual BBBrain* Clone(BBActionList& target_action_list, BBPerceptionList& target_perception_list);
	virtual void MutateEditype(float f_probability);
	void SaveBase();
	
	int Edit();
	
private:
	BBRuleListType m_BaseRuleList;
	BBRuleListEditorList m_EditorList;
};
}

#endif //_BBRULELISTEDITYPE_H

