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

#ifdef __APPLE__

#include "BBOS.h"
#include <sys/time.h>
#include <time.h>

namespace bitbang
{

/*!
 * \brief Gets the current time in the bitbang format.
 *
 * Unit is seconds, but precision is microseconds.
 *
 * \returns time
 *
 */

BBTime BBOS::GetTime()
{
	timeval time;
	gettimeofday(&time, NULL);
	
	BBTime fTime = (BBTime)time.tv_sec;
	fTime += ((BBTime)time.tv_usec) / 1000000.0f;
	return fTime;
}

/*!
 * \brief Extract seed for the random number generator from time.
 *
 * \returns seed
 *
 */
unsigned int BBOS::GetRandomSeed()
{
	timeval time;
	gettimeofday(&time, NULL);
	
	return time.tv_usec;
}

}
#endif
