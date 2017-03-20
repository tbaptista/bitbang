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
#if !defined(EA_EAFBD028_1A5B_4388_8CF6_CF15FAB68EBF__INCLUDED_)
#define EA_EAFBD028_1A5B_4388_8CF6_CF15FAB68EBF__INCLUDED_

#include <iostream>
#include <string>

using namespace std;

namespace bitbang
{
/*!
 * \brief An agent's feature.
 *
 * A feature represents a defined characteristic of an agent. For example the
 * feature "color". This class is just the base generic class. The child classes
 * will then actualy define an actual feature.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2005-06-02
 *
 */
class BBFeature
{

public:
	BBFeature();
	virtual ~BBFeature();
	
	void SetName(string str_name){m_strName = str_name;};
	string GetName(){return m_strName;};
	virtual string HumanReadable() = 0;
	
private:
	string m_strName;
};
}

#endif // !defined(EA_EAFBD028_1A5B_4388_8CF6_CF15FAB68EBF__INCLUDED_)
