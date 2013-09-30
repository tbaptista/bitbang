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

#include "BBFileLog.h"

#include <iostream>
#include <sstream>

namespace bitbang
{
	BBFileLog::BBFileLog()
	{
		m_strFileName = "";
	}
	
	BBFileLog::~BBFileLog()
	{
		if (m_File.is_open())
		{
			m_File.close();
		}
	}
	
	void BBFileLog::SetFileName(string str_base_path, string str_log_name)
	{
		stringstream strFileName;
		
		strFileName << str_base_path << "logs/" << m_strConfigID << "_" << m_strRunID << "_" << str_log_name << ".txt";
		m_strFileName = strFileName.str();
	}
	
	bool BBFileLog::Init()
	{
		if (!BBLog::Init())
		{
			cerr << "Error initialising BBLog!" << endl;
			return false;
		}
		else
		{
			if (m_strFileName.empty())
			{
				cerr << "Error: Trying to initialise the log without setting the file name!" << endl;
				m_bInitialised = false;
				return false;
			}
			else
			{
				m_File.open(m_strFileName.c_str(), ofstream::out | ofstream::trunc);
				if (m_File.fail())
				{
					cerr << "Error opening the file " << m_strFileName << " for writing!" << endl;
					m_bInitialised = false;
					return false;
				}
			}
		}
		return true;
	}
}
