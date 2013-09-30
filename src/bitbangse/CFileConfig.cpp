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

#include "CFileConfig.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

CFileConfig::CFileConfig()
{
	m_strFileName = "";
}

CFileConfig::~CFileConfig()
{
	if (m_ConfigFile.is_open())
	{
		m_ConfigFile.close();
	}
}

bool CFileConfig::ReadConfig()
{
	m_ConfigFile.open(m_strFileName.c_str(), ifstream::in);
	if (m_ConfigFile.fail())
	{
		cerr << "Error opening config file: " << m_strFileName << endl;
		return false;
	}
	
	string strName;
	
	while (m_ConfigFile.good())
	{
		getline(m_ConfigFile, strName, '=');
		if (strName.size() > 0)
		{
			if (!ReadValue(strName) || !CheckRead(strName))
			{
				m_ConfigFile.close();
				return false;
			}
			m_ConfigFile.ignore(256, '\n');
			if (m_ConfigFile.gcount() == 256)
			{
				cerr << "End of line not found after reading value for " << strName << endl;
				m_ConfigFile.close();
				return false;
			}
		}
	}
	
	m_ConfigFile.close();
	
	return true;
}

void CFileConfig::SetFileName(string str_file_name)
{
	m_strFileName = str_file_name;
}

bool CFileConfig::CheckRead(string str_name)
{
	if (m_ConfigFile.fail())
	{
		cerr << "Error reading value for " << str_name << endl;
		return false;
	}
	
	return true;
}

void CFileConfig::SaveConfigLog(string str_base_path, string str_config_id, string str_run_id)
{
	ifstream ConfigFile(m_strFileName.c_str(), ifstream::in | ifstream::binary);
	
	if (!ConfigFile.fail())
	{
		//Set log file name
		stringstream strFileName;
		strFileName << str_base_path << "logs/" << str_config_id << "_" << str_run_id << "_" << "config" << ".txt";
		
		//Open log file
		ofstream LogFile(strFileName.str().c_str(), ifstream::out | ifstream::binary | ifstream::trunc);
		
		if (!LogFile.fail())
		{
			LogFile << ConfigFile.rdbuf();
		}
		else
		{
			cerr << "Error trying to open file for writing: " << strFileName.str() << endl;
		}
	}
	else
	{
		cerr << "Error opening config file " << m_strFileName.c_str() << ". Cannot save the log." << endl;
	}
}


