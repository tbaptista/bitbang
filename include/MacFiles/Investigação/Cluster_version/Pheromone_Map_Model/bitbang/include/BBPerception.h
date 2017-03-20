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
#ifndef BBPERCEPTION_H
#define BBPERCEPTION_H

#include <iostream>
#include <vector>

using namespace std;

namespace bitbang
{
	
class BBObject;
		
/*!
 * \brief Perception base class.
 *
 * Defines the generic perception. This class cannot be instatiated as it has
 * purely virtual methods. To use, derive a class.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2005-06-07
 *
 */
class BBPerception
{
public:
	static const int nTYPEBOOLEAN;
	static const int nTYPENUMBER;
	static const int nTYPESTRING;

protected:
	int m_nType;
	int m_nOpCount;
	string m_strName;
	bool m_bOwnedByList;

public:
	BBPerception();
	virtual ~BBPerception();
	virtual BBPerception* Clone(){return NULL;};
	void SetName(string str_name);
	string GetName();
	int GetOpCount();
	bool IsType(int n_type);
	int GetType() {return m_nType;};
	bool IsOwnedByList() {return m_bOwnedByList;};
	void SetOwnedByList(bool b_owned_by_list) {m_bOwnedByList = b_owned_by_list;};
	virtual void UpdateName(){};

	
	/*!
	 * \brief Get the human readable string for this perception.
	 *
	 * This version of the method returns the human readable format for the
     * value of this perception.
	 *
	 * \return The string with the human readable form for the value of the
     *         perception.
	 *
     */
	virtual string HumanReadable() = 0;
	
	/*!
	 * \brief Get the human readable string for this perception.
	 *
	 * This version of the method uses the specified operator to produce the
     * human readable format.
	 *
	 * \param n_op The operator to use.
	 * \return The string with the human readable form for the specified
     *         operator.
	 *
     */
	virtual string HumanReadable(int n_op) = 0;

	/*!
	 * \brief Updates the value of the perception. 
	 *
	 * \param c_agent The agent interface this perception belongs to.
	 *
     */
	virtual void Update(BBObject& c_agent) = 0;

	/*!
	 * \brief Evaluate the perception.
	 *
	 * This is the unary version. Returns the current value of the perception
     * using the supplied operator. This method does not update the perception.
     * Use the Update method for that. The possible operators are defined in the
     * derived classes.
	 *
	 * \param n_op The operator to use. The possible operators are defined in
     *        the derived classes.
	 * \return True if op(value) is true, false otherwise.
	 *
	 */
	virtual bool Eval(int n_op) = 0;

	/*!
	 * \brief Evaluate the perception.
	 *
	 * This is the binary version. Returns the current value of the perception
     * using the supplied operator and applying it to the perpection received.
     * The perception received must be of the same derived class as the calling
     * one. This method does not update the perception. Use the Update method
     * for that. The possible operators are defined in the derived classes.
	 *
	 * \param n_op The operator to use. The possible operators are defined in
     *        the derived classes.
	 * \param c_perception The perception for the second part of the evaluation.
	 * \return True if (this perception) op (receive perception) is true, false
     *         otherwise.
	 *
     */
	virtual bool Eval(int n_op, BBPerception& c_perception) = 0;

	/*!
	 * \brief Check if a determined operator is unary.
	 *
	 * \param n_op The operator to check.
	 * \return True is the operator is unary, false otherwise.
	 *
	 */
	virtual bool IsOpUnary(int n_op) = 0;

	/*!
	 * \brief Creates a perception of the same type with a random value.
	 *
	 * Each actual perception implementation will provide the proper perception
     * and randomize its value.
	 *
	 * \return The created perception. This new perception must be freed by the
     *         user of this method.
     */
	virtual BBPerception& CreateRandomTypePerception() = 0;
};
	
typedef vector<BBPerception*> BBPerceptionList;

}

#endif // BBPERCEPTION_H
