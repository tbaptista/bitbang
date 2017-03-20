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
#ifndef _BBRANDOMRULELIST_H
#define _BBRANDOMRULELIST_H

#include <list>

#include "BBRuleList.h"

using namespace std;

namespace bitbang
{


/*!
 * \brief This class defines a rule list brain.
 *
 * It is a simple list of rules that are evaluated and from those that return true
 * a random one is selected as the action to activate. Other than that, it is
 * similar to the \ref BBRuleList class.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2007-04-26
 *
 * \see BBRule | BBRuleList
 */
class BBRandomRuleList : public BBRuleList
{
public:
	BBRandomRuleList();
	BBRandomRuleList(int n_max_rules, int n_min_rules, int n_max_conditions, BBActionList& action_list, BBPerceptionList& perception_list);
	virtual ~BBRandomRuleList();
	virtual list<BBAction*> Think();
};
}



#endif // _BBRANDOMRULELIST_H
