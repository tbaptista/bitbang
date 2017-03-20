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

#ifndef C_FILE_CONFIG_H
#define C_FILE_CONFIG_H

#include <string>
#include <fstream>

/*!
 * \brief This class can be used to read a configuration from a text file.
 *
 * This is an abstract class and as such must be derived and mapped to a specific configuration file.
 *
 * \version 1.0
 * Bit Bang Simulation Engine
 *
 * \date 2007-04-09
 *
 */
class CFileConfig
{
public:
	CFileConfig();
	virtual ~CFileConfig();
	bool ReadConfig();
	void SetFileName(std::string str_file_name);
	void SaveConfigLog(std::string str_base_path, std::string str_config_id, std::string str_run_id);
	
private:
	virtual bool ReadValue(std::string str_name);
	bool CheckRead(std::string str_name);
	
	std::string m_strFileName;
	
protected:
	std::ifstream m_ConfigFile;
};

#endif //C_FILE_CONFIG_H

