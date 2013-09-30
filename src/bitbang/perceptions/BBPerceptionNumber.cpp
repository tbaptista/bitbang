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
#include "BBPerceptionNumber.h"
#include "BBPerceptionFixedNumber.h"
#include "BBRandomGenerator.h"

#include <math.h>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

namespace bitbang
{
//Operations
const int BBPerceptionNumber::nOPEQUAL = 0;
const int BBPerceptionNumber::nOPGREATER = 1;
const int BBPerceptionNumber::nOPLESS = 2;

/*!
 * \brief Constructor.
 *
 * The default constructor sets the name of the perception to "unnamed".
 *
 */
BBPerceptionNumber::BBPerceptionNumber()
{
	m_strName = "unnamed";
	m_nOpCount = 3;
	m_nType = BBPerception::nTYPENUMBER;
	m_dRange = std::numeric_limits<unsigned int>::max();
	m_bInt =  false;
}


/*!
 * \brief Destructor.
 *
 */
BBPerceptionNumber::~BBPerceptionNumber()
{

}

/*!
 * \brief Get the human readable string for this perception.
 *
 * \return The string with the human readable form of the value.
 *
 */
string BBPerceptionNumber::HumanReadable()
{
	ostringstream strReturn;

	strReturn << m_dValue;

	return strReturn.str();
}

/*!
 * \brief Get the human readable string for this perception.
 *
 * \param n_op The operator to use.
 * \return The string with the human readable form for the specified
 *         operator.
 *
 */
string BBPerceptionNumber::HumanReadable(int n_op)
{
	string strReturn;

	switch(n_op)
	{
		case nOPEQUAL:
			strReturn = "=";
			break;

		case nOPGREATER:
			strReturn = ">";
			break;
			
		case nOPLESS:
			strReturn = "<";

		default:
			//ASSERT: Invalid operator.
			string strReturn = "unknown_operator " + m_strName;
			break;
	}

	return strReturn;
}

/*!
 * \brief Evaluate the perception.
 *
 * This is the unary version. Returns the current value of the perception using
 * the supplied operator. This method does not update the perception. Use the
 * Update method for that. As this version of the class has no unary operators,
 * this version of the method should not be used. It will always return false.
 *
 * \param n_op The operator to use.
 * \return True if op(value) is true, false otherwise.
 *
 */
bool BBPerceptionNumber::Eval(int n_op)
{
	//ASSERT: format not supported by operator.
	return false;
}

/*!
 * \brief Evaluate the perception.
 *
 * This is the binary version. Returns the current value of the perception using
 * the supplied operator and applying it to the perpection received. The
 * perception received must be of this class or a derived one. This method does
 * not update the perception. Use the Update method for that.
 *
 * \param n_op The operator to use.
 * \param c_perception The perception for the second part of the evaluation.
 * \return True if (this perception) op (receive perception) is true, false
 *         otherwise.
 *
 */
bool BBPerceptionNumber::Eval(int n_op, BBPerception& c_perception)
{
	if (c_perception.IsType(BBPerception::nTYPENUMBER))
	{
		double nOtherValue = ((BBPerceptionNumber*)&c_perception)->GetValue();

		switch(n_op)
		{
		case nOPEQUAL:
			return (m_dValue == nOtherValue);

		case nOPGREATER:
			return (m_dValue > nOtherValue);

		case nOPLESS:
			return (m_dValue < nOtherValue);

		default:
			//ASSERT: Invalid operator.
			return false;			
		}
	}
	else
	{
		//ASSERT: The perception passed is not of a valid type.
		return false;
	}
}

/*!
 * \brief Check if a determined operator is unary.
 *
 * \param n_op The operator to check.
 * \return True is the operator is unary, false otherwise.
 *
 */
bool BBPerceptionNumber::IsOpUnary(int n_op)
{
	//There are no unary operators defined
	return false;
}

/*!
 * \brief Get the value of this perception.
 *
 * \return The current value of the perception.
 *
 */
double BBPerceptionNumber::GetValue()
{
	return m_dValue;
}

/*!
 * \brief Create a perception of type BBPerceptionFixedNumber with a random value.
 *
 * \return The Perception created.
 *
 */
BBPerception& BBPerceptionNumber::CreateRandomTypePerception()
{
	BBPerceptionFixedNumber* pPerception;
	
	if (m_bInt)
	{
		double dValue = g_RandomGenerator.RandInt((int)m_dRange + 1);
		pPerception = new BBPerceptionFixedNumber(dValue);
	}
	else
	{
		pPerception = new BBPerceptionFixedNumber(g_RandomGenerator.RandProb() * m_dRange);
		pPerception->SetRange(m_dRange);
	}
	
	return *pPerception;
}

void BBPerceptionNumber::SetRange(double d_range)
{
	m_dRange = d_range;
}

}
