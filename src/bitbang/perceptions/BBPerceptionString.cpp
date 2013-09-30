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

#include "BBPerceptionString.h"
#include "BBPerceptionFixedString.h"

namespace bitbang
{	
	/*!
	 * \brief Constructor.
	 *
	 * The default constructor sets the name of the perception to "unnamed".
	 *
	 */
	BBPerceptionString::BBPerceptionString()
	{
		m_strName = "unnamed";
		m_nOpCount = 1;
		m_nType = BBPerception::nTYPESTRING;
	}
	
	/*!
	 * \brief Destructor.
	 *
	 */
	BBPerceptionString::~BBPerceptionString()
	{
	}
	
	/*!
	 * \brief Get the human readable string for this perception.
	 *
	 * \return The string with the value of the perception. No conversion is
	 * done.
	 *
	 */
	string BBPerceptionString::HumanReadable()
	{
		return m_strValue;
	}
	
	/*!
	 * \brief Get the human readable string for this perception's operators.
	 *
	 * \param n_op The operator to use.
	 * \return The string with the human readable form for the specified
	 *         operator.
	 *
	 */
	string BBPerceptionString::HumanReadable(int n_op)
	{
		string strReturn;
		
		switch(n_op)
		{
			case nOPEQUAL:
				strReturn = "=";
				break;
				
			case nOPSTARTSWITH:
				strReturn = "STARTSWITH";
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
	bool BBPerceptionString::Eval(int n_op)
	{
		//ASSERT: no unary operators exist for this perception.
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
	bool BBPerceptionString::Eval(int n_op, BBPerception& c_perception)
	{
		if (c_perception.IsType(BBPerception::nTYPESTRING))
		{
			string strOtherValue = ((BBPerceptionString*)&c_perception)->GetValue();
			
			switch(n_op)
			{
				case nOPEQUAL:
					return (m_strValue == strOtherValue);
					
				case nOPSTARTSWITH:
					return (m_strValue.compare(0, strOtherValue.size(), strOtherValue) == 0);
					
				default:
					//ASSERT: invalid operator
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
	bool BBPerceptionString::IsOpUnary(int n_op)
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
	string BBPerceptionString::GetValue()
	{
		return m_strValue;
	}
	
	/*!
	 * Currently, this method returns a perception of type BBPerceptionFixedString
	 * with the value "". There is no randomization process implemented for strings
	 * at the moment.
	 *
	 * \return The perception created.
	 *
	 */
	BBPerception& BBPerceptionString::CreateRandomTypePerception()
	{
		BBPerceptionFixedString* pPerception = new BBPerceptionFixedString("");
		return *pPerception;
	}
}
