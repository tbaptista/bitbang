/*
 * BitBang (http://www.bitbang.org)
 * Copyright (C) 2004-2009 Tiago Baptista
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
#ifndef CPHYSICSOBJECT15867321vgds2r31_H_
#define CPHYSICSOBJECT15867321vgds2r31_H_

#include <iostream>
#include <string>

#ifdef GetObject
#undef GetObject
#endif

#include "CSimObject.h"

class btRigidBody;

/*!
 * \brief This class implements a simulation object that uses physics.
 *
 * \version 1.0
 * Bit Bang Simulation Engine
 *
 * \date 2006-01-26
 *
 */
class CPhysicsObject : public CSimObject
{
public:
	CPhysicsObject(irr::IrrlichtDevice* p_device);
	virtual ~CPhysicsObject();
	
	virtual bool Init();
	
	btRigidBody* GetRigidBody(){return m_pRigidBody;};
	double GetMass(){return m_dMass;};
	void SetMass(double d_mass){m_dMass = d_mass;};

	
private:
	btRigidBody* m_pRigidBody;
	
	double m_dMass;
};

#endif /*CPHYSICSOBJECT15867321vgds2r31_H_*/
