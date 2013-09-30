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

#include "BBPerceptionFeatureString.h"

#include "features/BBFeatureString.h"

namespace bitbang
{
	BBPerceptionFeatureString::BBPerceptionFeatureString()
	{
	}
	
	BBPerceptionFeatureString::BBPerceptionFeatureString(BBFeatureString& c_feature)
	{
		m_strName = "Feature ";
		m_strName += c_feature.GetName();
		m_pFeature = &c_feature;
		m_strValue = c_feature.GetValue();
	}
	
	BBPerceptionFeatureString::~BBPerceptionFeatureString()
	{
	}
	
	BBPerception* BBPerceptionFeatureString::Clone()
	{
		return new BBPerceptionFeatureString(*m_pFeature);
	}
	
	void BBPerceptionFeatureString::SetFeature(BBFeatureString& c_feature)
	{
		m_strName = "Feature ";
		m_strName += c_feature.GetName();
		m_pFeature = &c_feature;
		m_strValue = c_feature.GetValue();
	}
	
	void BBPerceptionFeatureString::Update(BBObject& c_agent)
	{
		m_strValue = m_pFeature->GetValue();
	}
}
