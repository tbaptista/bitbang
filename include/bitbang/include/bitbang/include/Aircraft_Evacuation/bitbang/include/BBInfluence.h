/*!
 * 
 * Copyright (c) 2004-2005 by Telmo Menezes and Tiago Baptista. All rights reserved.
 */
#if !defined(EA_D0E7465B_9FE3_4d06_B040_7F2299DEF506__INCLUDED_)
#define EA_D0E7465B_9FE3_4d06_B040_7F2299DEF506__INCLUDED_

namespace bitbang
{

/*!
 * \brief An influence in a 3D influence map.
 *
 * This class represents an influence that can be placed in the influence map
 * supplied by the BBInfluenceMap class.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2005-06-02
 *
 * \see BBInfluenceMap
 *
 */
class BBInfluence
{
public:
	static const int nDEFAULT_DEGRADE_RATE = 1;
	static const int nDEFAULT_STRENGTH = 10;
	static const int nDEFAULT_SPREAD_LOSS = 1;

private:
	/**
	 * The rate of degradation over time of this influence.
	 */
	int m_nDegradeRate;
	/**
	 * The current influence strength at the origin.
	 */
	int m_nStrength;
	/**
	 * The loss of strength over space (as the influence spreads it looses strength).
	 */
	int m_nSpreadLoss;
	/**
	 * The x location for this influence in the 3D map
	 */
	int m_nX;
	/**
	 * The y location for this influence in the 3D map
	 */
	int m_nY;
	/**
	 * The z location for this influence in the 3D map
	 */
	int m_nZ;

public:
	BBInfluence();
	BBInfluence(int n_x, int n_y, int n_z, int n_degrade_rate, int n_strength, int n_spread_loss);
	virtual ~BBInfluence();
	int GetX();
	int GetY();
	int GetZ();
	int CalculateValue(int n_layer);
};

}

#endif // !defined(EA_D0E7465B_9FE3_4d06_B040_7F2299DEF506__INCLUDED_)
