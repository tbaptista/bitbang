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
#include "BBRuleCondition.h"
#include "perceptions/BBPerceptionNumber.h"
#include "perceptions/BBPerceptionString.h"
#include "perceptions/BBPerceptionFixedNumber.h"
#include "perceptions/BBPerceptionFixedString.h"
#include "BBRandomGenerator.h"
#include <stdlib.h>
#include <math.h>
#include <sstream>

using namespace std;

namespace bitbang
{

/*!
 * \brief Constructor.
 *
 * The default constructor sets the perceptions and op to NULL. If you use this
 * constructor, you need to call SetCondition to initialize before use.
 *
 */
BBRuleCondition::BBRuleCondition()
{
	m_pPerception1 = NULL;
	m_pPerception2 = NULL;
	m_nOp = 0;
}

/*!
 * \brief Constructor.
 *
 * This constructor takes two perceptions and one operator that must be valid
 * for those perceptions. 
 *
 * \param p_perception1 The first perception.
 * \param p_perception2 The second perception.
 * \param n_op The operator.
 *
 */
BBRuleCondition::BBRuleCondition(BBPerception* p_perception1, 
									BBPerception* p_perception2,
									int n_op)
{
	m_pPerception1 = p_perception1;
	m_pPerception2 = p_perception2;
	m_nOp = n_op;
}

/*!
 * \brief Constructor.
 *
 * This constructor takes one perception and one operator. The operator must be unary. 
 *
 * \param p_perception1 The first perception.
 * \param n_op The operator.
 *
 */
BBRuleCondition::BBRuleCondition(BBPerception* p_perception1, int n_op)
{
	m_pPerception1 = p_perception1;
	m_pPerception2 = NULL;
	m_nOp = n_op;
}

BBRuleCondition::BBRuleCondition(BBPerceptionList& perception_list)
{
	int nPerceptions = (int) perception_list.size();
	int nSelectedPerception1 = 0;
	int nSelectedPerception2 = 0;
	BBPerception* pPerception1 = NULL;
	BBPerception* pPerception2 = NULL;
	int nOp = 0;
	
	
	if (nPerceptions > 0)
	{
	nSelectedPerception1 = g_RandomGenerator.RandInt(nPerceptions);
	pPerception1 = perception_list[nSelectedPerception1];
	nOp = g_RandomGenerator.RandInt(pPerception1->GetOpCount());
	if (pPerception1->IsOpUnary(nOp))
	{
		m_pPerception1 = pPerception1;
		m_pPerception2 = NULL;
		m_nOp = nOp;
	}
	else
	{
		if (g_RandomGenerator.RandInt(2) == 0)
		{
			nSelectedPerception2 = g_RandomGenerator.RandInt(nPerceptions);
			pPerception2 = perception_list[nSelectedPerception2];
			if (!(pPerception2->IsType(pPerception1->GetType())))
			{
				pPerception2 = &pPerception1->CreateRandomTypePerception();
				pPerception2->SetOwnedByList(false);
			}
		}
		else
		{
			pPerception2 = &pPerception1->CreateRandomTypePerception();
			pPerception2->SetOwnedByList(false);
		}
		
		m_pPerception1 = pPerception1;
		m_pPerception2 = pPerception2;
		m_nOp = nOp;
	}
	}
	else
	{
		cerr << "Error: Perception list is empty. Cannot create random rule condition";
		m_pPerception1 = NULL;
		m_pPerception2 = NULL;
		m_nOp = 0;
	}
}
	
/*!
 * \brief Constructor.
 * This constructor creates a condition from one perception and a fixed value of type number.
 *
 * \param p_perception1 The first perception.
 * \param d_value2 The value to create a fixed perception from.
 * \param n_op The operator to use.
 *
 */
BBRuleCondition::BBRuleCondition(BBPerceptionNumber* p_perception1, double d_value2, int n_op)
{		
	m_pPerception1 = p_perception1;
	BBPerceptionFixedNumber* pPerception2 = new BBPerceptionFixedNumber(d_value2);
	pPerception2->SetOwnedByList(false);
	m_pPerception2 = pPerception2;
	m_nOp = n_op;
}
	
/*!
 * \brief Constructor.
 * This constructor creates a condition from one perception and a fixed value of type string.
 *
 * \param p_perception1 The first perception.
 * \param str_value2 The value to create a fixed perception from.
 * \param n_op The operator to use.
 *
 */
BBRuleCondition::BBRuleCondition(BBPerceptionString* p_perception1, string str_value2, int n_op)
{
	m_pPerception1 = p_perception1;
	BBPerceptionFixedString* pPerception2 = new BBPerceptionFixedString(str_value2);
	pPerception2->SetOwnedByList(false);
	m_pPerception2 = pPerception2;
	m_nOp = n_op;
}
	
/*!
 * \brief Copy Constructor
 *
 */
BBRuleCondition::BBRuleCondition(const BBRuleCondition& condition)
{
	m_nOp = condition.m_nOp;
	
	if (condition.m_pPerception1->IsOwnedByList())
	{
		m_pPerception1 = condition.m_pPerception1;
	}
	else
	{
		m_pPerception1 = condition.m_pPerception1->Clone();
	}
	
	if (condition.m_pPerception2 != NULL)
	{
		if (condition.m_pPerception2->IsOwnedByList())
		{
			m_pPerception2 = condition.m_pPerception2;
		}
		else
		{
			m_pPerception2 = condition.m_pPerception2->Clone();
		}
	}
	else
	{
		m_pPerception2 = NULL;
	}
}	

/*!
 * \brief Destructor.
 *
 */
BBRuleCondition::~BBRuleCondition()
{
	if (!m_pPerception1->IsOwnedByList())
	{
		delete m_pPerception1;
	}
	if (m_pPerception2 != NULL)
	{
		if (!m_pPerception2->IsOwnedByList())
		{
			delete m_pPerception2;
		}
	}
}

/*!
* \brief Clone the Rule Condition.
*
* \param n_target_id The ID of the target agent.
*
* \return A pointer to the new Rule Condition, NULL if an error occurs.
*/
BBRuleCondition* BBRuleCondition::Clone(BBPerceptionList& target_perception_list)
{
	BBRuleCondition* pNewCondition = new BBRuleCondition();
	string strPerception1Name = m_pPerception1->GetName();
	BBPerception* pNewPerception1 = NULL;
	BBPerceptionList::iterator iPerception;
	for (iPerception = target_perception_list.begin(); iPerception != target_perception_list.end(); iPerception++)
	{
		
		if ((*iPerception)->GetName() == strPerception1Name)
		{
			pNewPerception1 = (*iPerception);
		}
	}
	
	if (pNewPerception1 == NULL)
	{
		pNewPerception1 = m_pPerception1->Clone();
		if (pNewPerception1 == NULL)
		{
			delete pNewCondition;
			return NULL;
		}
	}
	
	BBPerception* pNewPerception2 = NULL;
	if (m_pPerception2 != NULL)
	{
		string strPerception2Name = m_pPerception2->GetName();
		pNewPerception2 = NULL;
		for (iPerception = target_perception_list.begin(); iPerception != target_perception_list.end(); iPerception++)
		{
			
			if ((*iPerception)->GetName() == strPerception2Name)
			{
				pNewPerception2 = (*iPerception);
			}
		}
		
		if (pNewPerception2 == NULL)
		{
			pNewPerception2 = m_pPerception2->Clone();
			if (pNewPerception2 == NULL)
			{
				delete pNewCondition;
				return NULL;
			}
		}
	}
	
	pNewCondition->SetCondition(pNewPerception1, pNewPerception2, m_nOp);
	return pNewCondition;
}

void BBRuleCondition::Mutate(float f_probability)
{
	if (g_RandomGenerator.RandProb() <= f_probability)
	{
		if (m_pPerception1 != NULL)
		{
			int nOpCount = m_pPerception1->GetOpCount();
			int nOp = g_RandomGenerator.RandInt(nOpCount);
			m_nOp = nOp;
		}
		else
		{
			cout << "Error: Perception 1 of condition is NULL! Can't mutate." << endl;
		}
	}
	
	if (g_RandomGenerator.RandProb() <= f_probability)
	{
		if (m_pPerception2 != NULL)
		{
			if (!m_pPerception2->IsOwnedByList())
			{
				delete m_pPerception2;
			}
			m_pPerception2 = &m_pPerception1->CreateRandomTypePerception();
		}
	}
}

/*!
 * \brief Set the condition parameters.
 *
 * This version of the method takes two perceptions and one operator.
 *
 * \param p_perception1 The first perception.
 * \param p_perception2 The second perception.
 * \param n_op The operator. Must be a valid operator for the perceptions and
 *        not unary.
 *
 */
void BBRuleCondition::SetCondition(BBPerception* p_perception1, 
									BBPerception* p_perception2,
									int n_op)
{
	m_pPerception1 = p_perception1;
	m_pPerception2 = p_perception2;
	m_nOp = n_op;
}

/*!
 * \brief Set the condition parameters.
 *
 * This version of the method takes one perception and one operator.
 *
 * \param p_perception1 The first perception.
 * \param n_op The operator.
 *
 */
void BBRuleCondition::SetCondition(BBPerception* p_perception1, int n_op)
{
	m_pPerception1 = p_perception1;
	m_pPerception2 = NULL;
	m_nOp = n_op;
}

/*!
 * \brief Avaluate this condition.
 *
 * Evaluates the perceptions of this condition using the operator.
 *
 * \return True if the perception eval returns true, false otherwise.
 *
 */
bool BBRuleCondition::Eval()
{
	
	bool bReturn;

	if (m_pPerception1 == NULL)
	{
		return true;
	}

	if (m_pPerception1->IsOpUnary(m_nOp))
	{
		bReturn = m_pPerception1->Eval(m_nOp);
	}
	else
	{
		if (m_pPerception2 == NULL)
		{
			return false;
		}
		bReturn = m_pPerception1->Eval(m_nOp, (*m_pPerception2));
	}

	return bReturn;
}
	
void BBRuleCondition::Edit(int n_function)
{
	switch (n_function)
	{
		case EDIT_VALUE:
			EditValue();
			break;
			
		case EDIT_OPERATOR:
			EditOperator();
			break;
			
		default:
			cerr << "Warning: Tried to use a non-existant editing function on BBRuleCondition." << endl;
	}
}
	
void BBRuleCondition::EditValue()
{
	if (m_pPerception2 != NULL)
	{
		if (!m_pPerception2->IsOwnedByList())
		{
			delete m_pPerception2;
		}
		m_pPerception2 = &m_pPerception1->CreateRandomTypePerception();
	}
}

void BBRuleCondition::EditOperator()
{
	if (m_pPerception1 != NULL)
	{
		int nOpCount = m_pPerception1->GetOpCount();
		int nOp = g_RandomGenerator.RandInt(nOpCount);
		m_nOp = nOp;
	}
}
	
bool BBRuleCondition::Matches(BBRuleCondition& condition_to_match)
{
	if (condition_to_match.Matches(*m_pPerception1, m_nOp))
	{
		return true;
	}
	else
	{
		return false;
	}
}
	
bool BBRuleCondition::Matches(BBPerception& perception, int n_op)
{
	if ((m_pPerception1 == &perception) && (m_nOp == n_op))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*!
 * \brief Return a human readable string representing the rule condition.
 *
 * \return The rule condition as a string.
 *
 */
string BBRuleCondition::HumanReadable()
{
	ostringstream strResult;
	
	if (m_pPerception1->IsOpUnary(m_nOp))
	{
		strResult << m_pPerception1->HumanReadable(m_nOp);
	}
	else
	{
		strResult << m_pPerception1->GetName() << " " << m_pPerception1->HumanReadable(m_nOp) << " " << m_pPerception2->GetName();
	}
	
	return strResult.str();
}
    
bool BBRuleCondition::HasPerception(const std::string& str_perception_name)
{
    if (str_perception_name.compare(m_pPerception1->GetName()) == 0)
    {
        return true;
    }
    else if (m_pPerception2 != NULL && str_perception_name.compare(m_pPerception2->GetName()) == 0)
    {
        return true;
    }
    
    return false;
}

}
