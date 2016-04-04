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
#include "BBObject.h"

#include "BBWorldInterface.h"
#include "BBBrain.h"
#include "features/BBFeatureNumber.h"
#include "features/BBFeatureBoolean.h"
#include "features/BBFeatureString.h"
#include "BBRandomGenerator.h"
#include "BBPerceptionSphere.h"
#include "BBLog.h"

#include <math.h>
#include <stdlib.h>

namespace bitbang
{

int BBObject::m_nCurrentID = 0;

/*!
 * \brief Constructor.
 *
 * Initializes the object and assigns an ID. The default object type is THING.
 *
 */
BBObject::BBObject()
{
	m_nID = m_nCurrentID++;
	m_nClassID = CLASSID;
	m_nType = TYPE_THING;
	m_pBrain = NULL;
	m_bDead = false;
	m_pWorld = NULL;
	m_pDeathLog = NULL;
	m_pBrainLog = NULL;
}

/*!
 * \brief Constructor with specified id
 *
 * Creates a new BBObject and uses the specified ID. It is the responsability of
 * the caller to make sure the IDs are unique.
 *
 * \param n_id The ID to use.
 *
 */
BBObject::BBObject(int n_id)
{
	m_nClassID = CLASSID;
	m_nType = TYPE_THING;
	m_pBrain = NULL;
	m_bDead = false;
	m_pWorld = NULL;
	m_pDeathLog = NULL;
	m_nID = n_id;
}
	
/*!
 * \brief Destructor.
 *
 * Destroys the brain, all the perceptions and all the actions of this
 * agent, if any exist.
 *
 */
BBObject::~BBObject()
{	
	BBFeatureMap::iterator iFeature;
	for (iFeature = m_FeatureMap.begin(); iFeature != m_FeatureMap.end(); iFeature++)
	{
		delete iFeature->second;
	}
	
	if (m_pBrain != NULL) {
		
		delete(m_pBrain);
		m_pBrain = NULL;
	}
	
	BBPerceptionList::iterator iPerception;
	for (iPerception = m_PerceptionList.begin(); iPerception != m_PerceptionList.end(); iPerception++)
	{
		if ((*iPerception)->IsOwnedByList())
		{
			delete (*iPerception);
		}
	}
	m_PerceptionList.clear();
	
	BBActionList::iterator iAction;
	for (iAction = m_ActionList.begin(); iAction != m_ActionList.end(); iAction++)
	{		
		if ((*iAction)->IsOwnedByList())
		{
			delete (*iAction);
		}
	}
	m_ActionList.clear();
	
	BBPerceptionSphereVector::iterator iSphere;
	for (iSphere = m_PerceptionSphereVector.begin(); iSphere != m_PerceptionSphereVector.end(); iSphere++)
	{
		delete (*iSphere);
	}
	m_PerceptionSphereVector.clear();
}
	
/*!
 * \brief Check the class of the object.
 *
 * \param n_class_id The ClassID to verify.
 *
 */
bool BBObject::TypeOf(int n_class_id)
{
	return (m_nClassID == n_class_id);
}

/*!
 * \brief Set the position of the object in the world.
 *
 * \param f_x The x axis position.
 * \param f_y The y axis position.
 * \param f_z The z axis position.
 *
 */
void BBObject::SetPosition(float f_x, float f_y, float f_z)
{
	m_Position.Set(f_x, f_y, f_z);
}

/*!
 * \brief Set the rotation of the object.
 *
 * \param f_x The x axis rotation.
 * \param f_y The y axis rotation.
 * \param f_z The z axis rotation.
 *
 */
void BBObject::SetRotation(float f_x, float f_y, float f_z)
{
	m_Rotation.Set(f_x, f_y, f_z);
}

/*!
 * \brief Returns the current time in the object's world.
 *
 * \return The current time.
 *
 */	
BBTime BBObject::GetTime()
{
	if (m_pWorld != NULL)
	{
		return m_pWorld->GetTime();
	}
	else 
	{
		cout << "Error: World has not been set for this object. Can't Call GetTime()." << endl;
		exit(1);
	}

}
	
/*!
 * \brief Returns a feature object stored in the internal feature list, by its
 * name.
 *
 * \param str_name the name of the feature
 * \return pointer to BBFeature object
 *
 */
BBFeature* BBObject::GetFeature(string str_name)
{
	BBFeatureMap::iterator iFeature;

	iFeature = m_FeatureMap.find(str_name);

	if (iFeature != m_FeatureMap.end())
	{
		return iFeature->second;
	}
	else
	{
		return NULL;
	}
}

/*!
 * \brief Inserts a feature in the internal feature list by its name. If a 
 * feature with the name provided already exists, it is replaced.
 *
 * \param str_name the name of the feature
 * \param c_feature feature to insert
 * \return nothing
 *
 */
void BBObject::AddFeature(string str_name, BBFeature& c_feature)
{
	m_FeatureMap.insert(BBFeatureMap::value_type(str_name, &c_feature));
}

/*!
 * \brief Returns the value of a feature object of type number stored in the 
 * internal feature list, by its name.
 *
 * \param str_name the name of the feature
 * \return double feature value
 *
 */
double BBObject::GetFeatureNumber(string str_name)
{
	BBFeatureNumber* p_feature;
	p_feature = (BBFeatureNumber*)(GetFeature(str_name));
	
	if (p_feature != NULL)
	{
		return p_feature->GetValue();
	}
	else
	{
		// What should we return when the feature is not defined?
		return 0;
	}
}

/*!
 * \brief Inserts a feature of type number in the internal feature list by its 
 * name. If a feature with the name provided already exists, it is replaced.
 *
 * \param str_name the name of the feature
 * \param d_feature value of the number feature
 * \return nothing
 *
 */
void BBObject::CreateFeatureNumber(string str_name, double d_feature)
{
	BBFeatureNumber* pFeature;
		
	pFeature = new BBFeatureNumber();
	pFeature->SetName(str_name);
	pFeature->SetValue(d_feature);
	AddFeature(str_name, (BBFeature&)(*pFeature));
}

/*!
 * \brief Changes the value of a number feature. If the feature does not exist,
 * 			does nothing and returns with a failure code (false).
 *
 * \param str_name the name of the feature
 * \param d_feature value of the number feature
 * \return true on success, false on failure
 *
 */
bool BBObject::SetFeatureNumber(string str_name, double d_feature)
{
	BBFeatureNumber* pFeature = (BBFeatureNumber*)(GetFeature(str_name));
	
	if (pFeature == NULL)
	{
		
		return false;
	}
	
	pFeature->SetValue(d_feature);	
	
	return true;
}

/*!
 * \brief Returns the value of a feature object of type boolean stored in the 
 * internal feature list, by its name.
 *
 * \param str_name the name of the feature
 * \return bool feature value
 *
 */
bool BBObject::GetFeatureBoolean(string str_name)
{
	BBFeatureBoolean* p_feature;
	p_feature = (BBFeatureBoolean*)(GetFeature(str_name));
	
	if (p_feature != NULL)
	{
		return p_feature->GetValue();
	}
	else
	{
		// Undefined feature is the same as false. But output a warning
		cerr << "Warning: Trying to get a non-existent boolean feature: " << str_name << "." << endl;
		return false;
	}
}

/*!
 * \brief Inserts a feature of type boolean in the internal feature list by its 
 * name. If a feature with the name provided already exists, it is replaced.
 *
 * \param str_name the name of the feature
 * \param b_feature value of the number feature
 * \return nothing
 *
 */
void BBObject::CreateFeatureBoolean(string str_name, bool b_feature)
{
	BBFeatureBoolean* pFeature;
		
	pFeature = new BBFeatureBoolean();
	pFeature->SetName(str_name);
	pFeature->SetValue(b_feature);
	AddFeature(str_name, (BBFeature&)(*pFeature));
}

/*!
 * \brief Changes the value of a boolean feature. If the feature does not exist,
 * 			does nothing and returns with a failure code (false).
 *
 * \param str_name the name of the feature
 * \param b_feature value of the boolean feature
 * \return true on success, false on failure
 *
 */
bool BBObject::SetFeatureBoolean(string str_name, bool b_feature)
{
	BBFeatureBoolean* pFeature = (BBFeatureBoolean*)(GetFeature(str_name));
	
	if (pFeature == NULL)
	{
		cerr << "Trying to set the value of a non existent feature: " << str_name << "." << endl;
		return false;
	}
	
	pFeature->SetValue(b_feature);
	
	return true;
}
	
string BBObject::GetFeatureString(string str_name)
{
	BBFeatureString* p_feature;
	p_feature = (BBFeatureString*)(GetFeature(str_name));
	
	if (p_feature != NULL)
	{
		return p_feature->GetValue();
	}
	else
	{
		// What should we return when the feature is not defined?
		return "";
	}
}
	
void BBObject::CreateFeatureString(string str_name, string str_value)
{
	BBFeatureString* pFeature;
	
	pFeature = new BBFeatureString();
	pFeature->SetName(str_name);
	pFeature->SetValue(str_value);
	AddFeature(str_name, (BBFeature&)(*pFeature));	
}
	
bool BBObject::SetFeatureString(string str_name, string str_value)
{
	BBFeatureString* pFeature = (BBFeatureString*)(GetFeature(str_name));
	
	if (pFeature == NULL)
	{
		return false;
	}
	
	pFeature->SetValue(str_value);
	
	return true;
}

/*!
 * \brief Calculates relative position of another BBObject from
 *        point of view of this one. Takes into account both position
 *        and rotation of the observing object.
 * 
 * \param c_obj BBObject to obtain relative position of
 * \return BBPoint with the relative position
 */
BBPoint BBObject::GetRelativePosition(BBObject& c_obj)
{	
	double dDegreesToRadians = 3.1415926535897932384626433832795f / 180.0f;
	double M0, M1, M2, M3, M4, M5, M6, M7, M8;
		
	double dx = c_obj.GetX() - GetX();
	double dy = c_obj.GetY() - GetY();
	double dz = c_obj.GetZ() - GetZ();

	double dAngleX = GetXRotation() * dDegreesToRadians;
	double dAngleY = GetYRotation() * dDegreesToRadians;
	double dAngleZ = GetZRotation() * dDegreesToRadians;
								
	double cr = cos(dAngleX);
	double sr = sin(dAngleX);
	double cp = cos(dAngleY);
	double sp = sin(dAngleY);
	double cy = cos(dAngleZ);
	double sy = sin(dAngleZ);

	M0 = cp * cy;
	M1 = cp * sy;
	M2 = -sp;

	double srsp = sr * sp;
	double crsp = cr * sp;

	M3 = srsp * cy - cr * sy;
	M4 = srsp * sy + cr * cy;
	M5 = sr * cp;

	M6 = crsp * cy + sr * sy;
	M7 = crsp * sy - sr * cy;
	M8 = cr * cp;
				
	double dPosX = (M0 * dx) + (M1 * dy) + (M2 * dz);
	double dPosY = (M3 * dx) + (M4 * dy) + (M5 * dz);
	double dPosZ = (M6 * dx) + (M7 * dy) + (M8 * dz);
	
	BBPoint cPoint((float)dPosX, (float)dPosY, (float)dPosZ);
	return cPoint;
}
	
/*!
 * \brief Executes this agents active actions.
 *
 * If there are any active actions, this method will execute them. If any
 * timeable actions are active, it will update the time passed.
 * 
 * \return True if there were any active actions, false otherwise.
 */
bool BBObject::Execute()
{	
	if (m_nType != TYPE_AGENT)
	{
		cerr << "Error: Trying to call execute on an object of type Thing!" << endl;
		return false;
	}
	
	if (m_bDead)
	{
		return false;
	}
	
	bool bActiveActions = false;
	
	BBActionList::iterator iAction;
	BBAction* pAction;
	for (iAction = m_ActionList.begin() ; iAction != m_ActionList.end(); iAction++)
	{
		pAction = *iAction;
		if (pAction->IsActive())
		{
			bActiveActions = true;
			
			if (pAction->IsTimeable())
			{
				pAction->UpdateTime(m_pWorld->GetTime());
			}
			
			pAction->Execute(this);
		}
	}
	
	return bActiveActions;
}

/*!
 * \brief Do cognition.
 * 
 * This method will first update the value of the perceptions and then call the
 * think of the brain. After receiving the new action from the think it will
 * also treat any actions that are flaggable accordingly. This version of the
 * method assumes only one action is returned by the think of the brain.
 *
 * \see BBBrain
 *
 * \todo Allow the brain to return several actions.
 */
void BBObject::Think()
{
	if (m_nType != TYPE_AGENT)
	{
		cerr << "Error: Trying to call think on an object of type Thing!" << endl;
		return;
	}
	
	if (m_bDead)
	{
		return;
	}
	
	//Update perception spheres
	UpdatePerceptionSpheres();
	
	//Update perceptions
	if (m_PerceptionList.size() != 0)
	{
		BBPerceptionList::iterator iPerception;
		for (iPerception = m_PerceptionList.begin(); iPerception != m_PerceptionList.end(); iPerception++)
		{
			(*iPerception)->Update(*this);
		}
	}
	
	if (!m_pBrain)
	{
		return;
	}

	if (m_bDead)
	{
		return;
	}
	
	list<BBAction*> actionList = m_pBrain->Think();
	list<BBAction*>::iterator iAction;
	
	for (iAction = actionList.begin(); iAction != actionList.end(); iAction++)
	{
		if ((*iAction) != NULL)
		{
			if (!(*iAction)->IsActive())
			{
				if ((*iAction)->IsFlaggable())
				{
					if ((*iAction)->IsTimeable())
					{
						(*iAction)->Activate(m_pWorld->GetTime());
					}
					else
					{
						(*iAction)->Activate();
						(*iAction)->Execute(this);
					}
				}
				else
				{
					(*iAction)->Execute(this);
				}
			}
			
			if (!(*iAction)->IsOwnedByAgent())
			{
				delete (*iAction);
			}
		}
	}
	
	if (m_bDead)
	{
		return;
	}
	
	BBActionList::iterator iAction2;
	BBAction* pAction2;
	for (iAction2 = m_ActionList.begin(); iAction2 != m_ActionList.end(); iAction2++)
	{
		pAction2 = *iAction2;
		if (pAction2->IsRuleBound())
		{
			if (pAction2->IsActive())
			{
				if (actionList.empty())
				{
					pAction2->DeActivate();
					pAction2->Execute(this);
				}
				
				for (iAction = actionList.begin(); iAction != actionList.end(); iAction++)
				{
					if (!pAction2->Equals(*(*iAction)))
					{
						pAction2->DeActivate();
						pAction2->Execute(this);
					}
				}
			}
		}
	}
}
	
/*!
 * \brief Add a perception to the perception list.
 *
 * \param c_perception The perception to add.
 *
 */
void BBObject::AddPerception(BBPerception& c_perception)
{
	m_PerceptionList.push_back(&c_perception);
	c_perception.SetOwnedByList(true);
}

/*!
 * \brief Add an action to the action list.
 *
 * \param c_action The action to add.
 *
 */
void BBObject::AddAction(BBAction& c_action)
{
	m_ActionList.push_back(&c_action);
	c_action.SetOwnedByList(true);
	c_action.SetOwnedByAgent(true);  //TODO: check why there are two of these settings
}
	
/*!
 * \brief Returns a pointer to an action from the agent's action list
 * 			by its name.
 * 
 * \param str_name action name
 * 
 * \return Pointer to BBAction on success, NULL on failure.
 *
 */
BBAction* BBObject::GetAction(string str_name)
{
	BBActionList::iterator iAction;
	for (iAction = m_ActionList.begin(); iAction != m_ActionList.end(); iAction++)
	{
		
		if ((*iAction)->GetName() == str_name)
		{
			return (*iAction);
		}
	}
	
	//No such action found.
	return NULL;
}
	
/*!
 * \brief Returns a pointer to a perception from the agent's perceptions list
 * 			by its name.
 * 
 * \param str_name perception name
 * 
 * \return Pointer to BBPerception on success, NULL on failure.
 *
 */
BBPerception* BBObject::GetPerception(string str_name)
{
	BBPerceptionList::iterator iPerception;
	for (iPerception = m_PerceptionList.begin(); iPerception != m_PerceptionList.end(); iPerception++)
	{
		
		if ((*iPerception)->GetName() == str_name)
		{
			return (*iPerception);
		}
	}
	
	//No such perception found.
	return NULL;
}
	
/*!
 * \brief Kill this agent.
 *
 */
void BBObject::Die()
{
	if (!m_bDead)
	{
		if (m_nType == TYPE_THING)
		{
			cout << "Error: Trying to kill an object of type thing!" << endl;
			return;
		}
		
		if (m_pDeathLog != NULL)
		{
			LogDeath();
		}
		
		if ((m_pBrainLog != NULL) && (m_pBrain != NULL))
		{
			(*m_pBrainLog) << "Agent " << m_nID << endl;
			(*m_pBrainLog) << m_pBrain->HumanReadable() << endl;
			(*m_pBrainLog) << "---------------------------------------------------" << endl;
		}
		
		m_bDead = true;
	}
	else
	{
		cerr << "Warning: Called Die() on an already dead agent." << endl;
	}
}
	
/*!
 * \brief Set the brain object of the agent.
 *
 * \param p_brain Ponter to brain object.
 *
 */
void BBObject::SetBrain(BBBrain* p_brain)
{
	m_pBrain = p_brain;
	m_pBrain->SetAgent(this);
}
	
/*!
 * \brief Returns a random perception from the agent's internal list.
 * 
 * \return BBPerception or NULL if no perceptions are registered.
 *
 */
BBPerception* BBObject::GetRandomPerception()
{
	int nSize = (int)m_PerceptionList.size();
	
	if (nSize <= 0)
	{
		return NULL;
	}
	
	int nPos = g_RandomGenerator.RandInt(nSize);
	return m_PerceptionList[nPos];
}
	
/*!
 * \brief Returns a random action from the agent's internal list.
 * 
 * \return BBAction or NULL if no actions are registered.
 *
 */
BBAction* BBObject::GetRandomAction()
{
	int nSize = (int)m_ActionList.size();
	
	if (nSize <= 0)
	{
		return NULL;
	}
	
	int nPos = g_RandomGenerator.RandInt(nSize);
	return m_ActionList[nPos];
}
	
/*!
 * \brief Adds a perception sphere to the agent.
 * 
 * \param c_perception_sphere Reference to BBPerceptionSphere object to add
 * \return unsigned int Index of the perception sphere that was added
 *
 */
unsigned int BBObject::AddPerceptionSphere(BBPerceptionSphere& c_perception_sphere)
{
	c_perception_sphere.SetOwnerID(GetID());
	m_PerceptionSphereVector.push_back(&c_perception_sphere);
	
	return (unsigned int)(m_PerceptionSphereVector.size() - 1);
}
	
/*!
 * \brief Gets a perception sphere object by index
 * 
 * \param n_index Index of perception sphere to return
 * \return BBPerceptionSphere& Reference to the perception sphere indicated by n_index
 *
 */
BBPerceptionSphere& BBObject::GetPerceptionSphere(unsigned int n_index)
{
	return *m_PerceptionSphereVector[n_index];
}
	
/*!
 * \brief Updates all registered perception spheres
 * 
 */
void BBObject::UpdatePerceptionSpheres()
{
	for (unsigned int i = 0; i < m_PerceptionSphereVector.size(); i++)
	{
		m_PerceptionSphereVector[i]->Update(m_Position, m_Rotation);
	}
}

void BBObject::UpdatePerceptionsInfluencedByNonTerminal()
{
    if (m_PerceptionList.size() != 0)
    {
        BBPerceptionList::iterator iPerception;
        for (iPerception = m_PerceptionList.begin(); iPerception != m_PerceptionList.end(); iPerception++)
        {
            if ((*iPerception)->IsModifiedByNonTerminalActions())
                (*iPerception)->Update(*this);
        }
    }
}
	
/*!
 * \brief Outputs stats to the death log.
 *
 * Automatically called upon agent death.
 * This virtual function should be overrided on the derived classes. The base
 * version is currently empty.
 *
 */
void BBObject::LogDeath()
{
}

}
