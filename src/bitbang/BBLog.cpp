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

#include "BBLog.h"
#include <iostream>

namespace bitbang
{
	BBLog::BBLog()
	{
		m_bInitialised = false;
		m_nNumFields = 0;
		m_strConfigID = "0000";
		m_strRunID = "00";
	}
	
	BBLog::~BBLog()
	{
		m_FieldNames.clear();
	}
	
	bool BBLog::Init()
	{
		m_nNumFields = m_FieldNames.size();
		
		m_bInitialised = true;
		
		return true;
	}
	
	void BBLog::SetIDs(string str_config_id, string str_run_id)
	{
		m_strConfigID = str_config_id;
		m_strRunID = str_run_id;
	}
	
	void BBLog::AddField(string str_field_name)
	{
		if (!m_bInitialised)
		{
			m_FieldNames.push_back(str_field_name);
		}
		else
		{
			cerr << "Warning: Cannot add a field to a log after initialisation!" << endl;
		}
	}
}
