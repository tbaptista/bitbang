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
#include "BBPerceptionFeatureNumber.h"

#include "features/BBFeatureNumber.h"

#include <string>

namespace bitbang
{

/*!
 * \brief Constructor
 *
 * This constructor receives a pointer to the feature assigned to this
 * perception. 
 *
 * \param p_feature A feature of type number.
 * \return 
 *
 * \see Separate items with the '|' character.
 *
 */
BBPerceptionFeatureNumber::BBPerceptionFeatureNumber(BBFeatureNumber& c_feature)
{
	m_strName = "Feature ";
	m_strName += c_feature.GetName();
	m_pFeature = &c_feature;
	m_dValue = c_feature.GetValue();
}

/*!
 * \brief
 * Destructor
 * 
 */
BBPerceptionFeatureNumber::~BBPerceptionFeatureNumber()
{
}

BBPerception* BBPerceptionFeatureNumber::Clone()
{
	return new BBPerceptionFeatureNumber(*m_pFeature);
}

void BBPerceptionFeatureNumber::SetFeature(BBFeatureNumber& c_feature)
{
	m_strName = "Feature ";
	m_strName += c_feature.GetName();
	m_pFeature = &c_feature;
	m_dValue = c_feature.GetValue();
}

/*!
 * \brief Updates the current value of this perception.
 * 
 * \param c_agent Interface instance of the owner agent.
 * \return nothing
 * 
 * This method overrides the abstract Update() method of the parent object 
 * (BBPerceptionNumber) and updates the current value of the perception using
 * the value of the assigned feature.
 *
 */
void BBPerceptionFeatureNumber::Update(BBObject& c_agent)
{
	m_dValue = m_pFeature->GetValue();
}

}
