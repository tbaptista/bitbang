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

#ifndef _BBFILELOG_H
#define _BBFILELOG_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;

#include "BBLog.h"

namespace bitbang
{
class BBFileLog : public BBLog
{
public:
	BBFileLog();
	virtual ~BBFileLog();
	
	void SetFileName(string str_file_name){m_strFileName = str_file_name;};
	void SetFileName(string str_base_path, string str_log_name);
	
	virtual bool Init();
	
protected:
	string m_strFileName;
	ofstream m_File;
};
}

#endif //_BBFILELOG_H

