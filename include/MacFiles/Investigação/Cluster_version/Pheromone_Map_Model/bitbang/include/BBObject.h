/*
 * BitBang (http://www.bitbang.org)
 * Copyright (C) 2004-2011 Tiago Baptista
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
#ifndef _BBOBJECT_H_
#define _BBOBJECT_H_

#include <list>
#include <map>
#include <vector>
#include <string>
#include <fstream>

#include "BBTypes.h"
#include "BBAction.h"
#include "BBPerception.h"

using namespace std;

namespace bitbang
{

class BBBrain;
class BBFeature;
class BBWorldInterface;
class BBPerceptionSphere;
class BBLog;
	
typedef list<int> BBObjectTypeList;
typedef map<string, BBFeature*> BBFeatureMap;
typedef vector<BBPerceptionSphere*> BBPerceptionSphereVector;

/*!
 * \brief This class represents a generic Bit Bang object.
 *
 * It can either be a thing or an agent.
 *
 * \version 1.0
 * Big Bong
 *
 * \date 2005-06-07
 *
 */
class BBObject
{
public:
	static int const CLASSID = 0;
	static int const NULL_ID = -1;
	
	static int const TYPE_THING = 1;
	static int const TYPE_AGENT = 2;
	
	BBObject();
	BBObject(int n_id);
	virtual ~BBObject();
	
	//Base
	bool TypeOf(int n_class_id);
	virtual void SetPosition(float f_x, float f_y, float f_z);
	BBPoint& GetPosition(){return m_Position;};
	virtual void SetRotation(float f_x, float f_y, float f_z);
	BBPoint& GetRotation(){return m_Rotation;};
	float GetX(){return m_Position.GetX();};
	float GetY(){return m_Position.GetY();};
	float GetZ(){return m_Position.GetZ();};
	float GetXRotation(){return m_Rotation.GetX();};
	float GetYRotation(){return m_Rotation.GetY();};
	float GetZRotation(){return m_Rotation.GetZ();};
	int GetID(){return m_nID;};
	void SetType(int n_type){m_nType = n_type;};
	bool IsType(int n_type){return (m_nType == n_type);};
	BBTime GetTime();
	
	virtual void OnObjectUpdate(){};
	
	BBFeature* GetFeature(string str_name);
	
	double GetFeatureNumber(string str_name);
	void CreateFeatureNumber(string str_name, double d_feature);
	bool SetFeatureNumber(string str_name, double d_feature);
	
	bool GetFeatureBoolean(string str_name);
	void CreateFeatureBoolean(string str_name, bool b_feature);
	bool SetFeatureBoolean(string str_name, bool b_feature);
	
	string GetFeatureString(string str_name);
	void CreateFeatureString(string str_name, string str_value);
	bool SetFeatureString(string str_name, string str_value);
	
	BBPoint GetRelativePosition(BBObject& c_obj);
	
	//Agent
	bool Execute();
	void Think();
	void MandatoryThink();
	
	void SetName(string str_name){m_strName = str_name;};
	string GetName(){return m_strName;};
	void SetBrain(BBBrain* p_brain);
	BBBrain* GetBrain(){return m_pBrain;};
	void SetWorld(BBWorldInterface* p_world){m_pWorld = p_world;};
	void SetDeathLog(BBLog& c_log){m_pDeathLog = &c_log;};
	void SetBrainLog(ofstream* p_brain_log){m_pBrainLog = p_brain_log;};
	
	void AddPerception(BBPerception& c_perception);
	void AddAction(BBAction& c_action);
	BBAction* GetAction(string str_name);
	BBPerception* GetPerception(string str_name);
	BBActionList* GetActionList() {return &m_ActionList;};
	BBPerceptionList* GetPerceptionList() {return &m_PerceptionList;};
	BBPerception* GetRandomPerception();
	BBAction* GetRandomAction();
	
	virtual void Die();
	bool IsDead(){return m_bDead;};
	
	unsigned int AddPerceptionSphere(BBPerceptionSphere& c_perception_sphere);
	BBPerceptionSphere& GetPerceptionSphere(unsigned int n_index);

protected:
	//Base
	void AddFeature(string str_name, BBFeature& c_feature);
	
	int m_nID;
	int m_nClassID;
	int m_nType;
	BBPoint m_Position;
	BBPoint m_Rotation;
	
	//Agent
	BBWorldInterface* m_pWorld;
	BBLog* m_pDeathLog;
	ofstream* m_pBrainLog;
	
	
	virtual void LogDeath();
	
private:
	//Base
	static int m_nCurrentID;
	BBFeatureMap m_FeatureMap;
	
	//Agent
	void UpdatePerceptionSpheres();
	
	BBActionList m_ActionList;
	BBPerceptionList m_PerceptionList;
	BBPerceptionSphereVector m_PerceptionSphereVector;
	string m_strName;
	BBBrain* m_pBrain;
	bool m_bDead;
};
}

#endif //_BBOBJECT_H_
