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

#include "BBWorld.h"
#include "BBObject.h"
#include "BBOS.h"
#include "BBRandomGenerator.h"
#include "BBSchedule.h"
#include "BBObject.h"

#include <math.h>
#include <stdlib.h>
#include <time.h>

namespace bitbang
{

/*!
 * \brief Constructor.
 *
 * The world's timer is created paused. Resume should be called to start the
 * simulation.
 *
 */
BBWorld::BBWorld()
{
	m_nThinkProbability = 1;
}

/*!
 * \brief Destructor.
 *
 * Terminates the scripting engine and deletes all schedules and interactions
 * registered.
 *
 */
BBWorld::~BBWorld()
{	
	BBScheduleList::iterator iSchedule;
	for (iSchedule = m_ScheduleList.begin(); iSchedule != m_ScheduleList.end(); ++iSchedule)
	{
		if ((*iSchedule)->GetOwnedByLib())
		{
			delete *iSchedule;
		}
	}
	
	m_ScheduleList.clear();
}

/*!
 * \brief Register an object in the world.
 *
 * \param object The object to register.
 *
 */
void BBWorld::RegisterObject(BBObject& object)
{
	if (object.IsType(BBObject::TYPE_AGENT))
	{
		object.SetWorld(this);
	}
	
	m_ObjectMap.insert(BBObjectMap::value_type(object.GetID(), &object));
}

/*!
 * \brief Get a Bit Bang object by ID.
 *
 * \param n_id The ID of the object to search.
 * \return The pointer to the BBObject, or NULL if the object does not exist.
 *
 */
BBObject* BBWorld::GetObject(int n_id)
{

	BBObjectMap::iterator iObject;

	iObject = m_ObjectMap.find(n_id);

	if (iObject != m_ObjectMap.end())
	{
		return iObject->second;	
	}
	else
	{
		//should we do assert or return NULL?
		return NULL;
	}
}

/*!
 * \brief Add a schedule to the schedule list.
 *
 * \param p_schedule The schedule to add.
 *
 */
void BBWorld::AddSchedule(BBSchedule* p_schedule)
{
	p_schedule->SetWorld(this);
	m_ScheduleList.push_back(p_schedule);
}

/*!
 * \brief Pause the World. Time will not advance.
 *
 * \seealse BBWorld::Resume()
 */
void BBWorld::Pause()
{
	m_Timer.Pause();
}

/*!
 * \brief Resume the World.
 *
 * \seealso BBWorld::Pause()
 */
void BBWorld::Resume()
{
	m_Timer.Resume();
}

/*!
 * \brief Checks the schedule list for schedules to execute.
 *
 * This method should be called regularly to enable scheduling system.
 *
 */
void BBWorld::Scheduler()
{
	//Check Schedules
	BBScheduleList::iterator iSchedule;
	for (iSchedule = m_ScheduleList.begin(); iSchedule != m_ScheduleList.end(); iSchedule++)
	{
		if ((*iSchedule)->Check(m_Timer.GetTime()))
		{
			(*iSchedule)->Execute();
			if ((*iSchedule)->IsRepeatable())
			{
				(*iSchedule)->ReSchedule();
			}
			else
			{
				delete (*iSchedule);
				iSchedule = m_ScheduleList.erase(iSchedule);
				if (iSchedule != m_ScheduleList.begin())
				{
					iSchedule--;
				}
			}
		}
	}
}

/*!
 * \brief Process the list of agents and let them think and execute.
 *
 */
void BBWorld::ProcessAgents()
{	
	
	//Agents are not processed when the timer is stopped
	//Removed to keep experiments consistent with previous ones
	/*if (m_Timer.IsPaused())
	{
		return;
	}*/
	
	BBObjectMap::iterator iObject;

	for (iObject = m_ObjectMap.begin(); iObject != m_ObjectMap.end(); iObject++)
	{
		BBObject* pObject = iObject->second;
		if (pObject->IsType(BBObject::TYPE_AGENT))
		{
			if (!pObject->IsDead())
			{
				if (g_RandomGenerator.RandInt(100) < m_nThinkProbability)
				{
					pObject->Think();
				}
				else
				{
					if (!pObject->Execute())
					{
						pObject->Think();
					}
				}
			}
			else
			{
				m_DeadAgentsList.push_back(pObject->GetID());
			}
		}
	}
}

/*!
 * \brief Remove an object from the world.
 *
 * This method will remove the object from the world's object list and also
 * destroy the corresponding engine object. If the agent is not found, then we do
 * nothing and return.
 *
 * \param n_id The ID of the object to remove.
 *
 */
void BBWorld::RemoveObject(int n_id)
{
	BBObjectMap::iterator iObject;

	iObject = m_ObjectMap.find(n_id);

	if (iObject == m_ObjectMap.end())
	{
		//Should we return an error?
		printf("\nERROR: Cannot find object to be removed!");
		return;
	}
	
	BBObject* pObject;
	pObject = (BBObject*) iObject->second;
	m_ObjectMap.erase(iObject);
	delete pObject;
}
	
/*!
 * Removes all dead agents from the world.
 *
 */
void BBWorld::RemoveDeadAgents()
{
	BBObjectIDList::iterator iObjectID;
	
	for (iObjectID = m_DeadAgentsList.begin(); iObjectID != m_DeadAgentsList.end(); iObjectID++)
	{
		RemoveObject(*iObjectID);
	}
	
	m_DeadAgentsList.clear();
}

/*!
 * \brief Returns pointer to the world's object list.
 *
 * \return Pointer to object list.
 *
 */
BBObjectMap* BBWorld::GetObjectMap()
{
	return &m_ObjectMap;
}

/*!
 * \brief Calls OnObjectUpdate on every object registered.
 *
 * \see BBObject::OnObjectUpdate
 */
void BBWorld::UpdateObjects()
{
	BBObjectMap::iterator iObject;
	
	for (iObject = m_ObjectMap.begin(); iObject != m_ObjectMap.end(); iObject++)
	{
		BBObject* pObject = iObject->second;
		pObject->OnObjectUpdate();
	}
}


}
