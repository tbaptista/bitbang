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

#include "BBCSVFileLog.h"

#include <iostream>

namespace bitbang
{
	bool BBCSVFileLog::Init()
	{
		if (!m_bInitialised)
		{
			if (!BBFileLog::Init())
			{
				return false;
			}
			else
			{
				if (m_nNumFields > 0)
				{
					m_File << m_FieldNames[0];
					
					for (int i = 1; i < m_nNumFields; i++)
					{
						m_File << "," << m_FieldNames[i];
					}
					
					m_File << endl;
				}
				else
				{
					cerr << "Error: Trying to initialise the log with 0 fields!" << endl;
					m_bInitialised = false;
					return false;
				}
			}
		}
		else
		{
			cerr << "Warning: Trying to initialise an already initialised log." << endl;
		}
		
		return true;
	}
	
	void BBCSVFileLog::Output(vector<string>& field_values)
	{
		if (m_File.is_open())
		{
			if (field_values.size() == m_nNumFields)
			{
				m_File << field_values[0];
				
				for (int i = 1; i < m_nNumFields; i++)
				{
					m_File << "," << field_values[i];
				}
				
				m_File << endl;
			}
			else
			{
				cerr << "Error: Number of fields received differs from the initialisation! Nothing will be output." << endl;
			}
		}
		else
		{
			cerr << "Error: Cannot output to log because the file is not open!" << endl;
		}
	}
	
	void BBCSVFileLog::Output(vector<float>& field_values)
	{
		if (m_File.is_open())
		{
			if (field_values.size() == m_nNumFields)
			{
				m_File << fixed << field_values[0];
				
				for (int i = 1; i < m_nNumFields; i++)
				{
					m_File << "," << fixed << field_values[i];
				}
				
				m_File << endl;
			}
			else
			{
				cerr << "Error: Number of fields received differs from the initialisation! Nothing will be output." << endl;
			}
		}
		else
		{
			cerr << "Error: Cannot output to log because the file is not open!" << endl;
		}
	}
}
