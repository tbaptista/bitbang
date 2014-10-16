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

#include "CWorld.h"
#include <stdio.h>
#include <sstream>
#include "BBOS.h"
#include "SimpleOpt.h"
#include "CDefaultEventHandler.h"
#include "CEventReceiver.h"
#include "CPhysicsObject.h"
#include "BBRandomGenerator.h"

#include "irrlicht.h"
#include "btBulletDynamicsCommon.h"

using namespace bitbang;

double CWorld::m_dElapsedTime = 0;
string CWorld::m_strBasePath = "./";

/*!
 * \brief Constructor.
 *
 */
CWorld::CWorld()
{
	m_pDevice = NULL;
	m_pDriver = NULL;
	m_pSmgr = NULL;
	m_pGuiEnv = NULL;
	m_nWindowWidth = 800;
	m_nWindowHeight = 600;
	m_bUseSkyBox = false;
	m_bUseSkyDome = false;
	m_pFont = NULL;
	m_pInfoBox = NULL;
	m_bDrawGraphics = true;
	m_bShowInfo = false;
	m_bStop = false;
	m_bPaused = false;
	m_bConsole = false;
	m_pSelectedObject = NULL;
	m_strRunID = "00";
	m_strConfigFile = "Resources/config.txt";
	m_TimeLimit = 0;
	m_pDefaultEventHandler = NULL;
    m_pEventReceiver = NULL;
	m_nSeedIndex = -1;
	
	m_bUsePhysics = false;
	m_pCollisionConfiguration = NULL;
	m_pDispatcher = NULL;
	m_pPairCache = NULL;
	m_pConstraintSolver = NULL;
	m_pDynamicsWorld = NULL;
	m_fGravity = 0;
}

/*!
 * \brief Destructor.
 *
 */
CWorld::~CWorld()
{
	if (m_pDefaultEventHandler != NULL)
	{
		delete m_pDefaultEventHandler;
	}
}

/*!
 * \brief Initializes the Irrlicht and Bullet worlds.
 *
 */
void CWorld::Init()
{	
	//Re-seed random number generator
	if (m_nSeedIndex != -1)
	{
		g_RandomGenerator.SetSeedbyIndex(m_nSeedIndex);
	}
	
	//Irrlicht init
	irr::video::E_DRIVER_TYPE eDevice = irr::video::EDT_OPENGL;
	if (m_bConsole)
	{
		eDevice = irr::video::EDT_NULL;
	}
	m_pDevice = irr::createDevice(eDevice, irr::core::dimension2d<irr::u32>(m_nWindowWidth, m_nWindowHeight), 16, false, false, false, 0);

	m_pDevice->setWindowCaption(L"BitBang Simulation Engine");

	m_pDriver = m_pDevice->getVideoDriver();
	m_pSmgr = m_pDevice->getSceneManager();
	m_pGuiEnv = m_pDevice->getGUIEnvironment();
 
	m_pSmgr->addCameraSceneNodeMaya();
	m_pSmgr->addLightSceneNode(0, irr::core::vector3df(0, 10000.0f, 0), irr::video::SColorf(1.0f, 1.0f, 1.0f), 50000.0f);
	
	// create skybox
	if (m_bUseSkyBox)
	{
		m_pDriver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);

		m_pSmgr->addSkyBoxSceneNode(
			m_pDriver->getTexture(m_strSkyBoxUp.c_str()),
			m_pDriver->getTexture(m_strSkyBoxDown.c_str()),
			m_pDriver->getTexture(m_strSkyBoxLeft.c_str()),
			m_pDriver->getTexture(m_strSkyBoxRight.c_str()),
			m_pDriver->getTexture(m_strSkyBoxFront.c_str()),
			m_pDriver->getTexture(m_strSkyBoxBack.c_str()));

		m_pDriver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);
	}
	
	// create skydome
	if (m_bUseSkyDome)
	{
		m_pSmgr->addSkyDomeSceneNode(m_pDriver->getTexture(m_strSkyDome.c_str()), 16, 16, 0.5f, 1.0f);
	}
	
	//Set default event handler
	m_pDefaultEventHandler = new CDefaultEventHandler(this);
    m_pEventReceiver = new CEventReceiver(m_pDefaultEventHandler);
    m_pDevice->setEventReceiver(m_pEventReceiver);
	
	//Bullet init
	if (m_bUsePhysics)
	{
		m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
		m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);
		m_pPairCache = new btDbvtBroadphase();
		m_pConstraintSolver = new btSequentialImpulseConstraintSolver();
		m_pDynamicsWorld = new btDiscreteDynamicsWorld(m_pDispatcher, m_pPairCache, m_pConstraintSolver, m_pCollisionConfiguration);
		
		//Set gravity
		m_pDynamicsWorld->setGravity(btVector3(0, m_fGravity, 0));
	}
}

/*!
 * \brief Run the simulation.
 *
 */
void CWorld::Run()
{	
	BBTime nLastTime = m_Timer.GetTime();
	BBTime nCurrentTime = 0;
	BBTime dStartTime = BBOS::GetTime();
	
	while(m_pDevice->run() && !m_bStop)
	{	
		m_Timer.UpdateTime();

		//Calculate elapsed time
		nCurrentTime = m_Timer.GetTime();	
		m_dElapsedTime = (nCurrentTime - nLastTime);
		nLastTime = nCurrentTime;

		RemoveDeadAgents();
		Scheduler();
		ProcessAgents();
		
		if (m_bUsePhysics)
		{
			m_pDynamicsWorld->stepSimulation(m_dElapsedTime * 0.001f);
		}
		
		if (m_pDevice->isWindowActive() && m_bDrawGraphics)
		{
			if (m_bShowInfo)
			{
				if (m_pInfoBox != NULL)
				{
					m_pInfoBox->setText(String2wchar(GetInfoText()));
				}
			}
			
			m_pDriver->beginScene(true, true, irr::video::SColor(101, 100, 101, 101));
			
			m_pSmgr->drawAll();
			m_pGuiEnv->drawAll();
			
			m_pDriver->endScene();
		}

		UpdateObjects(m_dElapsedTime);
		
		//Stop the simulation if the time limit was reached
		if (m_TimeLimit != 0)
		{
			if (m_Timer.GetTime() >= m_TimeLimit)
			{
				m_bStop = true;
			}
		}
	}
	
	DestroyWorld();
	
	BBTime dTotalTime = BBOS::GetTime() - dStartTime;
	double dRate = m_Timer.GetTime() / dTotalTime;
	cout << "Total time for simulation: " << dTotalTime << " seconds" << endl;
	cout << "Rate of simulation / real time: " << dRate << endl;
}

/*!
 * \brief Destroys the Irrlicht and Bullet worlds.
 *
 */
void CWorld::DestroyWorld()
{	
	if (m_bUsePhysics)
	{
		if (m_pCollisionConfiguration != NULL)
		{
			delete m_pCollisionConfiguration;
		}
		
		if (m_pDispatcher != NULL)
		{
			delete m_pDispatcher;
		}
		
		if (m_pPairCache != NULL)
		{
			delete m_pPairCache;
		}
		
		if (m_pConstraintSolver != NULL)
		{
			delete m_pConstraintSolver;
		}
		
		if (m_pDynamicsWorld != NULL)
		{
			delete m_pDynamicsWorld;
		}
	}
	
	if (m_pInfoBox != NULL)
	{
		m_pInfoBox->remove();
		m_pInfoBox = NULL;
	}
	
	m_pDevice->drop();
}



/*!
 * \brief Get an object by its position on the screen
 *
 * \param n_x The x screen coordinate
 * \param n_y The y screen coordinate
 * \return The ID of the object, or CSimObject::NULL_ID if no object is present at the specified coordinates.
 *
 */
int CWorld::GetObjectFromScreenCoordinates(int n_x, int n_y)
{
	irr::scene::ISceneNode* pSelectedNode;
	
	pSelectedNode = m_pSmgr->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(irr::core::position2d<irr::s32>(n_x, n_y));
	if (pSelectedNode != NULL)
	{
		return pSelectedNode->getID();
	}
	else
	{
		return BBObject::NULL_ID;
	}
}

void CWorld::RegisterObject(CSimObject& object)
{
	BBWorld::RegisterObject(object);
	
	object.SetConsole(m_bConsole);
	object.SetDrawGraphics(m_bDrawGraphics);
}

void CWorld::RegisterObject(CPhysicsObject& object)
{
	RegisterObject((CSimObject&)object);
	
	if (m_bUsePhysics)
	{
		m_pDynamicsWorld->addRigidBody(object.GetRigidBody());
	}
}

/*!
 * \brief Delete an object from the World.
 *
 * \param n_id The ID of the object to delete.
 *
 */
void CWorld::RemoveObject(int n_id)
{
	if (m_pSelectedObject != NULL)
	{
		if (m_pSelectedObject->GetID() == n_id)
		{
			SetSelectedObject(NULL);
		}
	}
	
	BBWorld::RemoveObject(n_id);	
}

/*!
 * \brief Set the window size.
 *
 * \param n_width The window width.
 * \param n_height The window height.
 *
 */
void CWorld::SetWindowSize(int n_width, int n_height)
{
	m_nWindowWidth = n_width;
	m_nWindowHeight = n_height;
}

/*!
 * \brief Set the sky box.
 *
 * \param str_up The texture for the up face.
 * \param str_down The texture for the down face.
 * \param str_left The texture for the left face.
 * \param str_right The texture for the right face.
 * \param str_front The texture for the front face.
 * \param str_back The texture for the back face.
 *
 */
void CWorld::SetSkyBox(std::string str_up, std::string str_down, std::string str_left, std::string str_right, std::string str_front, std::string str_back)
{
	m_bUseSkyBox = true;
	m_strSkyBoxUp = str_up;
	m_strSkyBoxDown = str_down;
	m_strSkyBoxLeft = str_left;
	m_strSkyBoxRight = str_right;
	m_strSkyBoxFront = str_front;
	m_strSkyBoxBack = str_back;
}

/*!
 * \brief Set the sky dome.
 *
 * \param str_skydome_file The file name of the texture for sky dome.
 *
 */
void CWorld::SetSkyDome(std::string str_skydome_file)
{
	m_bUseSkyDome = true;
	m_strSkyDome = str_skydome_file;
}

/*!
 * \brief Sets the system font from a image file.
 *
 * \param str_font_file Path to image file.
 *
 */
void CWorld::SetFont(std::string str_font_file)
{
	m_pFont = m_pDevice->getGUIEnvironment()->getFont(str_font_file.c_str());
	
	if (m_pFont != NULL)
	{
		m_pGuiEnv->getSkin()->setFont(m_pFont);
	}
	else
	{
		cerr << "Error loading font!" << endl;
	}
}

/*!
 * \brief Sets a new event receiver.
 *
 * \param p_er pointer to event receiver
 *
 */
void CWorld::SetEventHandler(CEventHandler* p_handler)
{
    m_pEventReceiver->SetEventHandler(p_handler);
}

/*!
 * \brief Sets the currently selected object.
 *
 * The method will set the selected object to the one passed. In the process,
 * if an object was previously selected, OnDeselect for that object is called.
 * Also, OnSelect is called for the new selected object.
 *
 * \param p_object The pointer to the object to be selected. If set to NULL, all
 * objects are de-selected
 *
 */
void CWorld::SetSelectedObject(CSimObject* p_object)
{
	if (m_pSelectedObject != NULL)
	{
		m_pSelectedObject->OnDeselect();
	}
	
	m_pSelectedObject = p_object;
	if (m_pSelectedObject != NULL)
	{
		m_pSelectedObject->OnSelect();
	}
}

/*!
 * \brief Is an object selected?
 *
 * \return True if an object is selected, false otherwise.
 *
 */
bool CWorld::IsObjectSelected()
{
	if (m_pSelectedObject == NULL)
	{
		return false;
	}
	else
	{
		return  true;
	}
}

bool CWorld::ProcessArguments(int argc, char* argv[])
{
	enum { OPT_HELP, OPT_FLAG, OPT_ARG };
	
	CSimpleOpt::SOption g_rgOptions[] = {
		{ OPT_FLAG, "-console",   SO_NONE    },
		{ OPT_ARG,  "-seedindex", SO_REQ_SEP },
		{ OPT_ARG,  "-config",    SO_REQ_SEP },
		{ OPT_ARG,  "-run",       SO_REQ_SEP },
		{ OPT_HELP, "-?",     SO_NONE    }, 
		{ OPT_HELP, "--help", SO_NONE    }, 
		SO_END_OF_OPTIONS
	};
	
	//Set base path and find executable name
	string strFullPath = argv[0];
#ifdef __APPLE__
	string strBasePath = strFullPath.substr(0, strFullPath.find_last_of('/'));
	strBasePath = strBasePath.substr(0, strBasePath.find_last_of('/') + 1);
	string strExecutableName = strFullPath.substr(strFullPath.find_last_of('/') + 1);
#else
	string strBasePath = "./";
	string strExecutableName = strFullPath.substr(strFullPath.find_last_of('/') + 1);
#endif
	string strConfigFile = strBasePath + m_strConfigFile;
	m_strBasePath = strBasePath;
	m_strConfigFile = strConfigFile;

	// declare our options parser, pass in the arguments from main
    // as well as our array of valid options.
    CSimpleOpt args(argc, argv, g_rgOptions);
	
	// while there are arguments left to process
    while (args.Next())
	{
        if (args.LastError() == SO_SUCCESS)
		{
            if (args.OptionId() == OPT_HELP) 
			{
                ShowUsage();
                return false;
            }
			else if (args.OptionId() == OPT_FLAG)
			{
				if (strcmp(args.OptionText(), "-console") == 0)
				{
					SetConsole(true);
					SetDrawGraphics(false);
				}
			}
			else if (args.OptionId() == OPT_ARG)
			{
				if (strcmp(args.OptionText(), "-config") == 0)
				{
					if (args.OptionArg())
					{
						m_strConfigFile = args.OptionArg();
					}
				}
				else if (strcmp(args.OptionText(), "-run") == 0)
				{
					if (args.OptionArg())
					{
						m_strRunID = args.OptionArg();
					}
				}
				else if (strcmp(args.OptionText(), "-seedindex") == 0)
				{
					if (args.OptionArg())
					{
						stringstream ss(args.OptionArg());
						
						if ((ss >> m_nSeedIndex).fail())
						{
							cout << "Error in -seedindex argument." << endl;
                            cout << "Received: " << ss << endl;
							ShowUsage();
							return false;
						}
					}
				}
			}
        }
        else {
			//ignore psn_* arguments passed by MacOS
#ifdef __APPLE__
			string strArgument = args.OptionText();
			if (strArgument.substr(0, 5).compare("-psn_") == 0)
			{
			}
			else
			{
#endif
            cout << "Invalid argument: " << args.OptionText() << endl;
            return false;
#ifdef __APPLE__
			}
#endif
        }
    }
	
	return true;
}

void CWorld::ShowUsage()
{
	cout << "Usage: SimulationEngine [-console] [-config FILE] [-run ID] [-seedindex ID] [-?] [--help]" << endl;
}

/*!
 * \brief Pause the simulation.
 *
 */
void CWorld::Pause()
{
	if (!m_bPaused)
	{
		m_pDevice->getTimer()->stop();
		BBWorld::Pause();
		m_bPaused = true;
	}
}

/*!
 * \brief Resume the simulation.
 *
 */
void CWorld::Resume()
{
	if (m_bPaused)
	{
		BBWorld::Resume();
		m_pDevice->getTimer()->start();
		m_bPaused = false;
	}
}

/*!
 * \brief Converts a string to a wchar_t string.
 *
 * \param string the string
 * \return pointer to wchar_t string
 *
 */
wchar_t* CWorld::String2wchar(std::string str_string)
{
	//TODO: check if this causes memory leaks.
	
	const char* chrString = str_string.c_str();
	int nStrSize = strlen(chrString) + 1;
	wchar_t* wchrString = (wchar_t*)(malloc(nStrSize * sizeof(wchar_t)));
	mbstowcs(wchrString, chrString, nStrSize);
	
	return wchrString;
}

void CWorld::SetShowInfo(bool b_show_info)
{
	if (m_pGuiEnv != NULL)
	{
		if (b_show_info)
		{
			if (m_pInfoBox == NULL)
			{
				m_pInfoBox = m_pGuiEnv->addStaticText(CWorld::String2wchar(GetInfoText()),irr::core::rect<irr::s32>(m_nWindowWidth - 150, m_nWindowHeight - 50, m_nWindowWidth - 5, m_nWindowHeight - 5));
			}
		}
		else
		{
			if (m_pInfoBox != NULL)
			{
				m_pInfoBox->remove();
				m_pInfoBox = NULL;
			}
		}
		
		m_bShowInfo = b_show_info;
	}
}

std::string CWorld::GetInfoText()
{
	stringstream strText;
	
	strText << "Time: " << GetTime() << endl;
	
	return strText.str();
}

void CWorld::CreateGroundPlane(float f_size_x, float f_size_y)
{
	if (m_pSmgr != NULL)
	{
		irr::scene::IMesh* pPlane = m_pSmgr->getGeometryCreator()->createPlaneMesh(irr::core::dimension2d<irr::f32>(f_size_x, f_size_y),
																			  irr::core::dimension2d<irr::u32>(1,1),
																			  0,
																			  irr::core::dimension2d<irr::f32>(1.0f,1.0f));
		irr::scene::ISceneNode* pNode = m_pSmgr->addMeshSceneNode(pPlane);
		
		//set color to green
		pNode->getMaterial(0).EmissiveColor = irr::video::SColor(255, 20, 110, 30);
		
	}
	else 
	{
		cout << "Error trying to access uninitialized m_pSmgr!" << endl;
	}

}
