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

#include <stdlib.h>
#include <string.h>
#include "BBPerceptionBoolean.h"
#include "BBPerceptionRandom.h"

namespace bitbang
{

const int BBPerceptionBoolean::nOPTRUE = 0;
const int BBPerceptionBoolean::nOPNOT = 1;

/*!
 * \brief
 * Constructor
 * 
 * Constructor with no paramenters.
 *
 */
BBPerceptionBoolean::BBPerceptionBoolean()
{
	m_nOpCount = 2;
	m_bValue = false;
	m_strName = "unnamed";
	m_nType = BBPerception::nTYPEBOOLEAN;
}

/*!
 * \brief
 * Destructor
 * 
 */
BBPerceptionBoolean::~BBPerceptionBoolean()
{
}

/*!
 * \brief Returns a human readable representation of the value of the
 * BBPerceptionBoolean.
 * 
 * \return human readable representation as a string
 * 
 * This method overrides the abstract HumanReadable() method of the parent 
 * object (BBPerception) and creates a human readable form for the specific case
 * of BBPerceptionBoolean.
 *
 */
string BBPerceptionBoolean::HumanReadable()
{
 string strReturn;

 if (m_bValue)
 {
	 strReturn = "true";
 }
 else
 {
	 strReturn = "false";
 }

 return strReturn;
}

/*!
 * \brief
 * Returns a human readable representation of the BBPerceptionBoolean and
 * one of its operators.
 * 
 * \param n_op Operator code
 * \return human readable representation as a string
 * 
 * This method overrides the abstract HumanReadable() method of the parent 
 * object (BBPerception) and creates a human readable form for the specific
 * case of BBPerceptionBoolean.
 *
 */
string BBPerceptionBoolean::HumanReadable(int n_op)
{
	string strReturn;

	switch(n_op)
	{
		case nOPTRUE:
			strReturn = "istrue(";
			strReturn += m_strName;
			strReturn += ")";
			break;

		case nOPNOT:
			strReturn = "not(";
			strReturn += m_strName;
			strReturn += ")";
			break;

		default:
			//ASSERT: Invalid operator.
			strReturn = "unknown_operator ";
			strReturn += m_strName;
			break;
	}

	return strReturn;
}

/*!
 * \brief
 * Evaluates the result of the application of an unary operator to the current
 * value of this perception.
 * 
 * \param n_op Operator code
 * \return boolean result of the evaluation
 * 
 * This method overrides the abstract Eval() method of the parent object 
 * (BBPerception) and performs unary evaluation for the specific case of 
 * BBPerceptionBoolean. It is called by derivates of the BBBrain
 * class during the cognition process.
 *
 * \see
 * BBBrain
 *
 */
bool BBPerceptionBoolean::Eval(int n_op)
{
	switch(n_op)
	{

		case nOPTRUE:
			return m_bValue;

		case nOPNOT:
			return !m_bValue;

		default:
			//ASSERT: Invalid operator.
			return false;			
			break;
	}
}

/*!
 * \brief
 * Evaluates the result of the application of a binary operator to the current
 * value of this perception and another value provided.
 * 
 * \param n_op Operator code
 * \param c_perception Perception instance to use as the second parameter
 * \return boolean result of the evaluation
 * 
 * This method overrides the abstract Eval() method of the parent object 
 * (BBPerception) and performs binary evaluation for the specific case of 
 * BBPerceptionBoolean. It is called by derivates of the BBBrain
 * class during the cognition process.
 *
 * \see
 * BBBrain
 *
 */
bool BBPerceptionBoolean::Eval(int n_op, BBPerception& c_perception)
{
	//ASSERT: format not supported by operator.
	return false;
}

/*!
 * \brief
 * This metod reports if a given operator is unary.
 * 
 * \param n_op Operator code
 * \return true if unary, false otherwise
 * 
 * This method overrides the abstract IsOpUnary() method of the parent object 
 * (BBPerception) and reports if a given operator is unary.
 *
 * \see
 * BBCognition
 *
 */
bool BBPerceptionBoolean::IsOpUnary(int n_op)
{
	switch(n_op)
	{
	case nOPTRUE:
		return true;
		break;
	case nOPNOT:
		return true;
		break;
	default:
		//ASSERT: Invalid operator.
		return true;
		break;
	}
}

/*!
 * \brief Creates a BBPerceptionRandom.
 *
 * \return The perception created.
 *
 */
BBPerception& BBPerceptionBoolean::CreateRandomTypePerception()
{
	BBPerceptionRandom* pPerception = new BBPerceptionRandom();
	return *pPerception;	
}

}
