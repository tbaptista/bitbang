/*!
 * 
 * Copyright (c) 2004-2005 by Telmo Menezes and Tiago Baptista. All rights reserved.
 */
#if !defined(EA_02141E28_58D0_4cd5_8AD4_480F9A68611F__INCLUDED_)
#define EA_02141E28_58D0_4cd5_8AD4_480F9A68611F__INCLUDED_

#include "BBInfluence.h"

#include <list>

namespace bitbang
{
/*!
 * \brief 3D Influence map.
 *
 * This class implements a 3D influence map. The three axis start at 0 and end
 * at m_n?Limit (? is X, Y or Z). This can only be used with small values as the
 * memory requirements for a 3D map soon become big.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2005-06-02
 *
 * \todo Create a constructor that receives the limits for the axis.
 *
 * \see
 * BBInfluence
 */
class BBInfluenceMap
{
public:
	static const int nDEFAULT_X_LIMIT = 400;
	static const int nDEFAULT_Y_LIMIT = 400;
	static const int nDEFAULT_Z_LIMIT = 10;

private:
	/**
	 * The maximum value of the x axis.
	 */
	int m_nXLimit;
	/**
	 * The maximum value of the y axis.
	 */
	int m_nYLimit;
	/**
	 * The maximum value of the z axis.
	 */
	int m_nZLimit;
	/**
	 * The 3D array for the actual influence map.
	 */
	int*** m_pInfluenceMap;
	/**
	 *
	 */
    std::list<BBInfluence*> m_InfluenceList;

public:
	BBInfluenceMap();
	virtual ~BBInfluenceMap();
	void PlaceInfluence(BBInfluence& influence);
	int GetValue(int x, int y, int z);

private:
	void AddInfluence(BBInfluence& influence);
	void AddSlice(int n_slice, int n_layer, int n_value, BBInfluence& influence);
	void AddCap(int n_slice, int n_layer, int n_value, BBInfluence& influence);

};

}
#endif // !defined(EA_02141E28_58D0_4cd5_8AD4_480F9A68611F__INCLUDED_)
