/*!
 * Copyright (c) 2004-2005 by Telmo Menezes and Tiago Baptista. All rights reserved.
 */

#include "BBInfluence.h"

namespace bitbang
{

/*!
 * \brief Default Constructor.
 */
BBInfluence::BBInfluence()
{
	m_nDegradeRate = nDEFAULT_DEGRADE_RATE;
	m_nStrength = nDEFAULT_STRENGTH;
	m_nSpreadLoss = nDEFAULT_SPREAD_LOSS;
}

/*!
 * \brief Constructor.
 *
 * \param n_x The x axis position for the influence.
 * \param n_y The y axis position for the influence.
 * \param n_z The z axis position for the influence.
 * \param n_degrade_rate The rate of degradation over time.
 * \param n_strength The strength at the origin.
 * \param n_spread_loss The loss of strength with spread.
 *
 */
BBInfluence::BBInfluence(int n_x, int n_y, int n_z, int n_degrade_rate, int n_strength, int n_spread_loss)
{
	m_nX = n_x;
	m_nY = n_y;
	m_nZ = n_z;
	m_nDegradeRate = n_degrade_rate;
	m_nStrength = n_strength;
	m_nSpreadLoss = n_spread_loss;
}

/*!
 * \brief Destructor
 */
BBInfluence::~BBInfluence()
{

}

int BBInfluence::GetX()
{
	return m_nX;
}

int BBInfluence::GetY()
{
	return m_nY;
}

int BBInfluence::GetZ()
{
	return m_nZ;
}

/*!
 * \brief Calculate the value of the influence at a specified layer.
 *
 * \param n_layer The layer where to calculate. The layer n surrounds the influence at n units of distance from the origin.
 * \return The value of the influence.
 *
 */
int BBInfluence::CalculateValue(int n_layer)
{
	return (m_nStrength - (m_nSpreadLoss * n_layer));
}

}
