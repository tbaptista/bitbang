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
#ifndef _BBPOINT_H_
#define _BBPOINT_H_

#include <sstream>
#include <string>
#include <iostream>

namespace bitbang
{

/*!
 * \brief This class represents a 3D point.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2005-06-07
 *
 */
class BBPoint
{
	public:
	
		/*!
		 * \brief Constructor.
		 *
		 * Initializes a BBPoint with default values of 0 to all coordinates.
		 *
		 */
		BBPoint(){
			m_fX = 0;
			m_fY = 0;
			m_fZ = 0;
		};
	
		/*!
		 * \brief Constructor.
		 *
		 * Initializes a BBPoint with the specified values for x, y and z.
		 *
		 * \param f_x The x axis position.
		 * \param f_y The y axis position.
		 * \param f_z The z axis position.
		 *
		 */
		BBPoint(float f_x, float f_y, float f_z){
			
			m_fX = f_x;
			m_fY = f_y;
			m_fZ = f_z;
		};
		
		/*!
		 * \brief Set the x axis position.
		 *
		 * \param f_x The x axis position.
		 *
		 */
		void SetX(float f_x){m_fX = f_x;};

		/*!
		 * \brief Set the y axis position.
		 *
		 * \param f_y The y axis position.
		 *
		 */
		void SetY(float f_y){m_fY = f_y;};

		/*!
		 * \brief Set the z axis position.
		 *
		 * \param f_z The z axis position.
		 *
		 */
		void SetZ(float f_z){m_fZ = f_z;};

		/*!
		 * \brief Set the postition of this point.
		 *
		 * \param f_x The x axis position.
		 * \param f_y The y axis position.
		 * \param f_z The z axis position.
		 *
		 */
		void Set(float f_x, float f_y, float f_z){
			
			m_fX = f_x;
			m_fY = f_y;
			m_fZ = f_z;
		};

		/*!
		 * \brief Get the x axis position.
		 *
		 * \return The x axis position.
		 *
		 */
		float GetX(){return m_fX;};

		/*!
		 * \brief Get the y axis position.
		 *
		 * \return The y axis position
		 *
		 */
		float GetY(){return m_fY;};

		/*!
		 * \brief Get the z axis position.
		 *
		 * \return The z axis position.
		 *
		 */
		float GetZ(){return m_fZ;};
		
		std::string HumanReadable() {
			std::ostringstream oss;
			oss << GetX() << " " << GetY() << " " << GetZ();
			return oss.str();
		};
	
	private:
	
		float m_fX;
		float m_fY;
		float m_fZ;		
};
}
#endif //_BBPOINT_H_
