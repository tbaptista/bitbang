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

#ifndef _BBLOG_H
#define _BBLOG_H

#include <vector>
#include <string>

using namespace std;

namespace bitbang
{
class BBLog
{
public:
	BBLog();
	virtual ~BBLog();
	
	virtual bool Init();
	virtual void Output(vector<string>& field_values) = 0;
	virtual void Output(vector<float>& field_values) = 0;
	
	bool IsInitialised(){return m_bInitialised;};
	
	void SetIDs(string str_config_id, string str_run_id);
	void AddField(string str_field_name);
	
protected:
	bool m_bInitialised;
	int m_nNumFields;
	vector<string> m_FieldNames;
	string m_strConfigID;
	string m_strRunID;
};
}

#endif //_BBLOG_H

