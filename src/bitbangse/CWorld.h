/*
 * BitBang (http://www.bitbang.org)
 * Copyright (C) 2004-2012 Tiago Baptista
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

#ifndef C_WORLD_H
#define C_WORLD_H

#include <string>

#include "BBWorld.h"
#include "BBTypes.h"

#include "btBulletDynamicsCommon.h"

#ifdef GetObject
#undef GetObject
#endif

namespace irr{
	class IrrlichtDevice;
	namespace scene{
		class ISceneNode;
		class ISceneManager;
		class IMesh;
	}
	namespace video{
		class IVideoDriver;
		class SColor;
	}
	namespace gui{
		class IGUIEnvironment;
		class IGUIFont;
		class IGUIStaticText;
	}
}

class CEventHandler;
class CSimObject;
class CPhysicsObject;

/*!
 * \brief This class encapsulates the BitBang, Irrlicht and the Bullet worlds.
 *
 * \version 1.0
 * BitBang Simulation Engine
 *
 * \date 2005-10-28
 *
 */
class CWorld : public bitbang::BBWorld
{
public:
	CWorld();
	virtual ~CWorld();
	
	virtual void Init();
	void Run();
	virtual void DestroyWorld();
	virtual void RegisterObject(CSimObject& object);
	virtual void RegisterObject(CPhysicsObject& object);
	virtual void RemoveObject(int n_id);
	
	void SetEventHandler(CEventHandler* p_handler);
	void SetWindowSize(int n_width, int n_height);
	void SetSkyBox(std::string str_up, std::string str_down, std::string str_left, std::string str_right, std::string str_front, std::string str_back);
	void SetSkyDome(std::string str_skydome_file);
	void SetUsePhysics(bool b_use_physics) {m_bUsePhysics = b_use_physics;};
	void SetFont(std::string str_font_file);
	void SetDrawGraphics(bool b_draw){m_bDrawGraphics = b_draw;};
	void SetShowInfo(bool b_show_info);
	void SetConsole(bool b_console){m_bConsole = b_console;};
	void SetTimeLimit(bitbang::BBTime time_limit){m_TimeLimit = time_limit;};
	void SetSelectedObject(CSimObject* p_object);
	void SetRunID(std::string str_runid){m_strRunID = str_runid;};
	void SetConfigFile(std::string str_config_file){m_strConfigFile = str_config_file;};
	void SetBasePath(std::string str_base_path){m_strBasePath = str_base_path;};
	
	irr::IrrlichtDevice* GetDevice(){return m_pDevice;};
	irr::scene::ISceneManager* GetSceneManager(){return m_pSmgr;};
	irr::video::IVideoDriver* GetDriver(){return m_pDriver;};
	irr::gui::IGUIEnvironment* GetGUIEnvironment(){return m_pGuiEnv;};
	int GetObjectFromScreenCoordinates(int n_x, int n_y);
	static double GetElapsedTime() {return m_dElapsedTime;};	
	irr::gui::IGUIFont* GetFont(){return m_pFont;};
	bool GetDrawGraphics(){return m_bDrawGraphics;};
	bool GetShowInfo(){return m_bShowInfo;};
	bool GetConsole(){return m_bConsole;};
	CSimObject* GetSelectedObject(){return m_pSelectedObject;};
	bool IsObjectSelected();
	std::string GetRunID(){return m_strRunID;};
	std::string GetConfigFile(){return m_strConfigFile;};
	static std::string GetBasePath(){return m_strBasePath;};
	
	void CreateGroundPlane(float f_size_x, float f_size_y);
	
	bool ProcessArguments(int argc, char* argv[]);
	void ShowUsage();
	virtual void Pause();
	virtual void Resume();	
	void Stop(){m_bStop = true;};
	
	static wchar_t* String2wchar(string str_string);
	
	void SetGravity(float f_gravity){m_fGravity = f_gravity;};
	
private:
	virtual std::string GetInfoText();
	
	static double m_dElapsedTime;
	bool m_bStop;
	bool m_bPaused;
	bitbang::BBTime m_TimeLimit;
	bool m_bDrawGraphics;
	bool m_bShowInfo;
	bool m_bConsole;
	CSimObject* m_pSelectedObject;
	std::string m_strRunID;
	std::string m_strConfigFile;
	static std::string m_strBasePath;
	int m_nSeedIndex;
	
	irr::IrrlichtDevice *m_pDevice;
	irr::video::IVideoDriver* m_pDriver;
	irr::scene::ISceneManager* m_pSmgr;
	irr::gui::IGUIEnvironment* m_pGuiEnv;
	int m_nWindowWidth;
	int m_nWindowHeight;
	irr::gui::IGUIFont* m_pFont;
	irr::gui::IGUIStaticText* m_pInfoBox;
	bool m_bUseSkyBox;
	std::string m_strSkyBoxUp;
	std::string m_strSkyBoxDown;
	std::string m_strSkyBoxLeft;
	std::string m_strSkyBoxRight;
	std::string m_strSkyBoxFront;
	std::string m_strSkyBoxBack;
	bool m_bUseSkyDome;
	string m_strSkyDome;
	CEventHandler* m_pDefaultEventHandler;
	
	bool m_bUsePhysics;
	btDefaultCollisionConfiguration* m_pCollisionConfiguration;
	btDispatcher* m_pDispatcher;
	btBroadphaseInterface* m_pPairCache;
	btConstraintSolver* m_pConstraintSolver;
	btDiscreteDynamicsWorld* m_pDynamicsWorld;
	float m_fGravity;
};
#endif
