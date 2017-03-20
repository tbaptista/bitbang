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

#if !defined(EA_CF604AD1_62A2_4636_9DA2_872BA485DBD0__INCLUDED_)
#define EA_CF604AD1_62A2_4636_9DA2_872BA485DBD0__INCLUDED_

#include <iostream>

#include "BBPerception.h"

using namespace std;

namespace bitbang
{
	
class BBPerceptionNumber;
class BBPerceptionString;

/*!
 * \brief A rule condition.
 *
 * This class defines a condition to be used by the \ref BBRule class. A
 * condition has one or two perceptions and an operator to use on those
 * perceptions.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2005-06-07
 *
 * \see BBPerception | BBRule
 */
class BBRuleCondition
{
private:
	BBPerception* m_pPerception1;
	BBPerception* m_pPerception2;
	int m_nOp;
	
	void EditValue();
	void EditOperator();
	
public:
	static const int MAX_EDIT_FUNCTIONS = 2;
	static const int EDIT_VALUE = 1;
	static const int EDIT_OPERATOR = 2;
	
	BBRuleCondition();
	BBRuleCondition(BBPerception* p_perception1, int n_op);
	BBRuleCondition(BBPerception* p_perception1, BBPerception* p_perception2, int n_op);
	BBRuleCondition(BBPerceptionList& perception_list);
	BBRuleCondition(BBPerceptionNumber* p_perception1, double d_value2, int n_op);
	BBRuleCondition(BBPerceptionString* p_perception1, string str_value2, int n_op);
	BBRuleCondition(const BBRuleCondition& condition);
	BBRuleCondition* Clone(BBPerceptionList& target_perception_list);
	void Mutate(float f_probability);
	void SetCondition(BBPerception* p_perception1, int n_op);
	void SetCondition(BBPerception* p_perception1, BBPerception* p_perception2, int n_op);
	virtual ~BBRuleCondition();
	bool Eval();
	void Edit(int n_function);
	bool Matches(BBRuleCondition& condition_to_match);
	bool Matches(BBPerception& perception, int n_op);
	string HumanReadable();
};
}
#endif // !defined(EA_CF604AD1_62A2_4636_9DA2_872BA485DBD0__INCLUDED_)
