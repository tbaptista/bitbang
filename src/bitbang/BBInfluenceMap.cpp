/*!
 * 
 * Copyright (c) 2004-2005 by Telmo Menezes and Tiago Baptista. All rights reserved.
 */

#include "BBInfluenceMap.h"
#include <math.h>
#include <stdlib.h>

namespace bitbang
{

/*!
 * \brief Constructor.
 *
 * Creates the 3D array to hold the map using the values provided by the default
 * limits for the axis. 
 *
 */
BBInfluenceMap::BBInfluenceMap()
{
	m_nXLimit = nDEFAULT_X_LIMIT;
	m_nYLimit = nDEFAULT_Y_LIMIT;
	m_nZLimit = nDEFAULT_Z_LIMIT;
	
	m_pInfluenceMap = new int**[m_nXLimit];

	for (int x = 0; x < m_nXLimit; x++)
	{
		m_pInfluenceMap[x] = new int*[m_nYLimit];

		for (int y = 0; y < m_nYLimit; y++)
		{
			m_pInfluenceMap[x][y] = new int[m_nZLimit];
		}
	}

	for (int x = 0; x < m_nXLimit; x++)
	{
		for (int y = 0; y < m_nYLimit; y++)
		{
			for (int z = 0; z < m_nZLimit; z++)
			{
				m_pInfluenceMap[x][y][z] = 0;
			}
		}
	}
}


/*!
 * \brief Destructor.
 *
 * Deletes the 3D array. 
 *
 */
BBInfluenceMap::~BBInfluenceMap()
{
	for (int x = 0; x < m_nXLimit; x++)
	{
		for (int y = 0; y < m_nXLimit; y++)
		{
			delete[] m_pInfluenceMap[x][y];
		}

		delete[] m_pInfluenceMap[x];
	}

	delete[] m_pInfluenceMap;

	//delete all influences on the list m_InfluenceList?
}


/*!
 * \brief Place an influence in the map.
 *
 * \param influence The influence to be placed.
 *
 */
void BBInfluenceMap::PlaceInfluence(BBInfluence& influence)
{
	if ((influence.GetX() < m_nXLimit)
		&& influence.GetY() < m_nYLimit
		&& influence.GetZ() < m_nZLimit
		&& influence.GetX() >= 0
		&& influence.GetY() >= 0
		&& influence.GetZ() >= 0)
	{
		m_InfluenceList.push_back(&influence);
		AddInfluence(influence);
	}
}

/*!
 * \brief Get the value for the [x,y,z] location in the influence map.
 *
 * \param x The x axis location.
 * \param y The y axis location.
 * \param z The z axis location.
 * \return The value of the influence at the specified location.
 *
 */
int BBInfluenceMap::GetValue(int x, int y, int z)
{
	return m_pInfluenceMap[x][y][z];
}

/*!
 * \brief Upadte the values of the map.
 *
 * Calculate the values of the affected cells on the map when adding this
 * influence updating the map accordingly. 
 *
 * \param influence The influence that is beeing placed.
 *
 */
void BBInfluenceMap::AddInfluence(BBInfluence& influence)
{
	int nX = influence.GetX();
	int nY = influence.GetY();
	int nZ = influence.GetZ();
	int nLayer = 0;
	int nValue = 0;

	nValue = influence.CalculateValue(nLayer);
	m_pInfluenceMap[nX][nY][nZ] += nValue;
	nLayer = nLayer + 1;
	nValue = influence.CalculateValue(nLayer);

	while (nValue > 0)
	{
		for (int nSlice = (nLayer * -1); nSlice <= nLayer; nSlice++)
		{
			if (abs(nSlice) ==  nLayer) //one of the caps
			{
				AddCap(nSlice, nLayer, nValue, influence);
			}
			else
			{
				AddSlice(nSlice, nLayer, nValue, influence);
			}
		}

		nLayer = nLayer + 1;
		nValue = influence.CalculateValue(nLayer);
	}
}

/*!
 * \brief Update the value of a slice in the influence map.
 *
 * This method is used as a helper to the \ref
 * BBInfluenceMap::AddInfluence(BBInfluence& influence) method to calculate the
 * updated values of a slice.
 *
 * \param n_slice The number of the slice to calculate.
 * \param n_layer The layer this slice belongs to.
 * \param n_value The value of the influence for this slice.
 * \param influence The influence being placed.
 */
void BBInfluenceMap::AddSlice(int n_slice, int n_layer, int n_value, BBInfluence& influence)
{
	int nOriginX = influence.GetY();
	int nOriginY = influence.GetX();
	int nZ = influence.GetZ() + n_slice;
	int x = 0;
	int y = 0;

	if (nZ < 0 || nZ >= m_nZLimit)
	{
		return;
	}

	y = nOriginY + n_layer;
	if (y >= 0 && y < m_nYLimit)
	{
		for (x = nOriginX - n_layer; x <= nOriginX + n_layer; x++)
		{
			if (x >= 0 && x < m_nXLimit)
			{
				m_pInfluenceMap[x][y][nZ] += n_value;
			}
		}
	}

	x = nOriginX + n_layer;
	if (x >= 0 && x < m_nXLimit)
	{
		for (y = nOriginY + n_layer - 1; y >= nOriginY - n_layer; y--)
		{
			if (y >= 0 && y < m_nXLimit)
			{
				m_pInfluenceMap[x][y][nZ] += n_value;
			}
		}
	}

	y = nOriginY - n_layer;
	if (y >= 0 && y < m_nYLimit)
	{
		for (x = nOriginX + n_layer - 1; x >= nOriginX - n_layer; x--)
		{
			if (x >= 0 && x < m_nXLimit)
			{
				m_pInfluenceMap[x][y][nZ] += n_value;
			}
		}
	}

	x = nOriginX - n_layer;
	if (x >= 0 && x < m_nXLimit)
	{
		for (y = nOriginY - n_layer + 1; y <= nOriginY + n_layer - 1; y++)
		{
			if (y >= 0 && y < m_nXLimit)
			{
				m_pInfluenceMap[x][y][nZ] += n_value;
			}
		}
	}
}

/*!
 * \brief Update the value of a cap in the influence map.
 *
 * This method is used as a helper to the \ref
 * BBInfluenceMap::AddInfluence(BBInfluence& influence) method to calculate the
 * updated values of a cap. A cap is a special version of a slice at the edges
 * of the layer.
 *
 * \param n_slice The number of the slice to calculate.
 * \param n_layer The layer the slice belongs to.
 * \param n_value The value of the influence for this cap. 
 * \param influence The influence being placed.
 *
 */
void BBInfluenceMap::AddCap(int n_slice, int n_layer, int n_value, BBInfluence& influence)
{
	int nOriginX = influence.GetX();
	int nOriginY = influence.GetY();
	int nZ = influence.GetZ() + n_slice;

	if (nZ < 0 || nZ >= m_nZLimit)
	{
		return;
	}

	for (int y = nOriginY + n_layer; y >= nOriginY - n_layer; y--)
	{
		if (y >= 0 && y < m_nYLimit)
		{
			for (int x = nOriginX - n_layer; x <= nOriginX + n_layer; x++)
			{
				if (x >= 0 && x < m_nXLimit)
				{
					m_pInfluenceMap[x][y][nZ] += n_value;
				}
			}
		}
	}
}

}
