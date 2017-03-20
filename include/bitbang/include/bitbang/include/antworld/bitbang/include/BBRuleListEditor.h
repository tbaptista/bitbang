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

#ifndef _BBRULELISTEDITOR_H
#define _BBRULELISTEDITOR_H

#include "BBPerception.h"
#include "BBRuleList.h"

namespace bitbang
{
class BBRuleCondition;

class BBRuleListEditor
{
public:
	BBRuleListEditor();
	BBRuleListEditor(float f_concentration, int n_function, BBRuleCondition& condition);
	BBRuleListEditor(BBPerceptionList& perception_list);
	virtual ~BBRuleListEditor();
	
	virtual int Edit(BBRuleListType& rule_list);
	virtual BBRuleListEditor* Clone(BBPerceptionList& target_perception_list);
	virtual void Mutate(float f_probability);
	
private:
	float m_fConcentration;
	int m_nFunction;
	BBRuleCondition* m_pRuleRuleCondition;
};
}

#endif //_BBRULELISTEDITOR_H


