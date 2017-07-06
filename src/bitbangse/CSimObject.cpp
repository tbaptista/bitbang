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

#include "CSimObject.h"
#include "CTimedLabel.h"
#include "BBWorldInterface.h"
using namespace bitbang;

#include "irrlicht.h"

#include <iostream>
#include <string>
using namespace std;


/*!
 * \brief Constructor.
 *
 */
CSimObject::CSimObject(irr::IrrlichtDevice* p_device)
{
	m_pDevice = p_device;
	m_pSmgr = p_device->getSceneManager();
	m_pDriver = p_device->getVideoDriver();
	m_pGuiEnv = p_device->getGUIEnvironment();
	m_bInitialized = false;
	m_pMesh = NULL;
	m_pNode = NULL;
	m_fScaleX = 1.0f;
	m_fScaleY = 1.0f;
	m_fScaleZ = 1.0f;
	m_strMeshFileName = "";
	m_strTextureFileName = "";
	m_nNodeType = NODETYPE_CUBE;
	m_pMaterialColor = new irr::video::SColor(255, 255, 255, 255);
}

/*!
 * \brief Constructor that sets a specific object ID.
 *
 */
CSimObject::CSimObject(irr::IrrlichtDevice* p_device, int n_id) : BBObject(n_id)
{
	m_pDevice = p_device;
	m_pSmgr = p_device->getSceneManager();
	m_pDriver = p_device->getVideoDriver();
	m_pGuiEnv = p_device->getGUIEnvironment();
	m_bInitialized = false;
	m_pMesh = NULL;
	m_pNode = NULL;
	m_fScaleX = 1.0f;
	m_fScaleY = 1.0f;
	m_fScaleZ = 1.0f;
	m_strMeshFileName = "";
	m_strTextureFileName = "";
	m_nNodeType = NODETYPE_CUBE;
	m_pMaterialColor = new irr::video::SColor(255, 255, 255, 255);
}

/*!
 * \brief Destructor.
 *
 */
CSimObject::~CSimObject()
{
	RemoveGraphics();
	
	delete m_pMaterialColor;
}

/*!
 * \brief Initialize the irrlicht object.
 *
 * \return true on success, false on failure.
 *
 */
bool CSimObject::Init()
{
	if (!CreateGraphics())
	{
		return false;
	}
	
	m_bInitialized = true;
	return true;
}

/*!
 * \brief Create graphic representation of the object.
 *
 * \return true on success, false on failure.
 *
 */
bool CSimObject::CreateGraphics()
{
	if (m_nNodeType == NODETYPE_CUBE || m_nNodeType == NODETYPE_SPHERE)
	{
		m_pNode = m_pSmgr->addCubeSceneNode(1);
		m_pNode->getMaterial(0).EmissiveColor = *m_pMaterialColor;		
	}
	else if (m_nNodeType == NODETYPE_ANIMATEDMESH)
	{
		if (GetMeshFileName().empty())
		{
			return false;
		}
		
		irr::scene::IAnimatedMesh* pMesh = m_pSmgr->getMesh(GetMeshFileName().c_str());
		
		if (pMesh == NULL)
		{
			return false;
		}
		
		irr::scene::IAnimatedMeshSceneNode* pNode = m_pSmgr->addAnimatedMeshSceneNode(pMesh);
		
		if (pNode == NULL)
		{
			return false;
		}
		
		if (m_strTextureFileName != "")
		{
			pNode->setMaterialTexture(0, m_pDriver->getTexture(m_strTextureFileName.c_str()));
		}
		
		pNode->setMaterialFlag(irr::video::EMF_LIGHTING, true); //TODO: Is this needed?
		
		m_pMesh = pMesh;
		m_pNode = pNode;
	}
	else
	{
		return false;
	}

	m_pNode->setID(m_nID);
	m_pNode->setPosition(irr::core::vector3df(GetX(), GetY(), GetZ()));
	m_pNode->setRotation(irr::core::vector3df(GetXRotation(), GetYRotation(), GetZRotation()));
	m_pNode->setScale(irr::core::vector3d<irr::f32>(m_fScaleX, m_fScaleY, m_fScaleZ));
	
	return true;
}

/*!
 * \brief Remove graphic representation of the object.
 *
 * \return true on success, false on failure.
 *
 */
void CSimObject::RemoveGraphics()
{
	if (m_pNode != NULL)
	{
		m_pSmgr->getRootSceneNode()->removeChild(m_pNode);
		m_pNode = NULL;
		
		if (m_LabelList.size() > 0)
		{
			CObjectLabelList::iterator iLabel;
			for (iLabel = m_LabelList.begin(); iLabel != m_LabelList.end(); iLabel++)
			{
				delete (*iLabel);
			}
		}
	}
}

/*!
 * \brief Sets the name of the mesh file to be used by this object.
 *
 * \param str_mesh file path and name
 *
 */
void CSimObject::SetMeshFile(std::string str_mesh)
{
	m_strMeshFileName = str_mesh;
}

/*!
 * \brief Sets the name of the texture file to be used by the object.
 * Only necessary for certain mesh formats.
 *
 * \param str_texture text file path and name.
 *
 */
void CSimObject::SetTextureFile(string str_texture)
{
	m_strTextureFileName = str_texture;
}

void CSimObject::SetMaterialColor(int n_a, int n_r, int n_g, int n_b)
{
	m_pMaterialColor->set(n_a, n_r, n_g, n_b);
	
	if (m_bInitialized)
	{
		m_pNode->getMaterial(0).EmissiveColor = *m_pMaterialColor;
	}
}

/*!
 * \brief Sets the position of the object.
 *
 * \param f_x x position
 * \param f_y y position
 * \param f_z z position
 *
 */
void CSimObject::SetPosition(float f_x, float f_y, float f_z)
{
	BBObject::SetPosition(f_x, f_y, f_z);
	
	if (m_pNode != NULL)
	{
		irr::core::vector3df vecNewPosition;
		vecNewPosition.set(f_x, f_y, f_z);
		m_pNode->setPosition(vecNewPosition);
	}
}

/*!
 * \brief Sets the rotation of the object.
 *
 * \param f_x x-axis rotation angle
 * \param f_y y-axis rotation angle
 * \param f_z z-axis rotation angle
 *
 */
void CSimObject::SetRotation(float f_x, float f_y, float f_z)
{
	BBObject::SetRotation(f_x, f_y, f_z);
	if (m_pNode != NULL)
	{
		irr::core::vector3df vecNewRotation;
		vecNewRotation.set(f_x, f_y, f_z);
		m_pNode->setRotation(vecNewRotation);
	}
}

/*!
 * \brief Sets the scale of this object.
 *
 * \param d_x x scale value
 * \param d_y y scale value
 * \param d_z z scale value
 *
 */
void CSimObject::SetScale(float f_x, float f_y, float f_z)
{
	m_fScaleX = f_x;
	m_fScaleY = f_y;
	m_fScaleZ = f_z;
	
	if (m_pNode != NULL)
	{
		m_pNode->setScale(irr::core::vector3d<irr::f32>(m_fScaleX, m_fScaleY, m_fScaleZ));
	}
}

/*!
 * \brief Sets the animation loop for the irrlicht graphics node.
 *
 * \param n_start starting loop frame
 * \param n_end ending loop frame
 *
 */
void CSimObject::SetFrameLoop(int n_start, int n_end)
{
	if (m_nNodeType == NODETYPE_ANIMATEDMESH)
	{
		irr::scene::IAnimatedMeshSceneNode* pAnimatedNode;
		pAnimatedNode = (irr::scene::IAnimatedMeshSceneNode*)m_pNode;
		pAnimatedNode->setFrameLoop(n_start, n_end);
	}
}

/*!
 * \brief Sets the animation speed for the irrlicht graphics node.
 *
 * \param n_speed the speed in frames per second
 *
 */
void CSimObject::SetAnimationSpeed(int n_speed)
{
	if (m_nNodeType == NODETYPE_ANIMATEDMESH)
	{
		irr::scene::IAnimatedMeshSceneNode* pAnimatedNode;
		pAnimatedNode = (irr::scene::IAnimatedMeshSceneNode*)m_pNode;
		pAnimatedNode->setAnimationSpeed(n_speed);
	}
}

/*!
 * \brief Set the drawing of bounding box to on or off.
 *
 * \param b_draw True, draws bounding box for this node. False to turn off.
 *
 */
void CSimObject::SetDrawBoundingBox(bool b_draw)
{
	irr::s32 nCurrentFlags = m_pNode->isDebugDataVisible();
	
	if (b_draw)
	{
		m_pNode->setDebugDataVisible(nCurrentFlags | irr::scene::EDS_BBOX);
	}
	else
	{
		m_pNode->setDebugDataVisible(nCurrentFlags & ~irr::scene::EDS_BBOX);
	}
}

void CSimObject::AddTimedLabel(BBTime timeout, std::string str_text)
{
	//No need to create the labels in console mode.
	if (!m_bConsole)
	{
		CTimedLabel* pLabel = new CTimedLabel(m_pSmgr, m_pNode, m_pWorld->GetTime(), timeout, str_text);
		m_LabelList.push_back(pLabel);
	}
}

void CSimObject::OnObjectUpdate()
{
	BBObject::OnObjectUpdate();
	
	//Update Labels
	if (m_LabelList.size() > 0)
	{
		CObjectLabelList::iterator iLabel;
		
		iLabel = m_LabelList.begin();
		while (iLabel != m_LabelList.end())
		{
			bool bKeepLabel = (*iLabel)->Update(m_pWorld->GetTime());
			if (!bKeepLabel)
			{
				delete (*iLabel);
				iLabel = m_LabelList.erase(iLabel);
			}
			else
			{
				iLabel++;
			}
		}
	}
}

/*!
 * \brief This method gets called when the object is selected.
 *
 */
void CSimObject::OnSelect()
{
	m_pNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

/*!
 * \brief This method gets called when the object is de-selected.
 *
 */
void CSimObject::OnDeselect()
{
	m_pNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
}

void CSimObject::ScaleToGivenSize(float sizeX, float sizeY, float sizeZ)
{
    irr::scene::ISceneNode* mesh = m_pNode;

    if (mesh == NULL)
    {
        return;
    }

    irr::core::vector3d<irr::f32>* edges = new irr::core::vector3d<irr::f32>[8];
    irr::core::aabbox3d<irr::f32> boundingBox = mesh->getTransformedBoundingBox();

    boundingBox.getEdges(edges);

    irr::f32 height = edges[1].Y - edges[0].Y;
    irr::f32 width = edges[5].X - edges[1].X;
    irr::f32 depth = edges[2].Z - edges[0].Z;

    irr::f32 factorX = sizeX/width;
    irr::f32 factorY = sizeY/height;
    irr::f32 factorZ = sizeZ/depth;

    m_fScaleX = factorX;
    m_fScaleY = factorY;
    m_fScaleZ = factorZ;

    mesh->setScale(irr::core::vector3df(factorX,factorY,factorZ));
}
