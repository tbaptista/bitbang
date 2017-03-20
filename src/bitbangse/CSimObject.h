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

#ifndef CSIMOBJECT_H
#define CSIMOBJECT_H

#include <string>
#include <map>
#include <list>
#include <irrTypes.h>

#include "BBObject.h"

class CObjectLabel;

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
}
}

typedef list<CObjectLabel*> CObjectLabelList;

/*!
 * \brief This class implements a basic 3D simulation object.
 *
 * The CSimObject builds on the BBObject to include Irrlicht Engine data
 * and functions.
 *
 * \version 1.0
 * Bit Bang Simulation Engine
 *
 * \date 2005-10-28
 *
 */
class CSimObject : public bitbang::BBObject
{
public:
	static const int CLASSID = 101;
	
	static const int NODETYPE_CUBE = 0;
	static const int NODETYPE_MESH = 1;
	static const int NODETYPE_ANIMATEDMESH = 2;
	
	CSimObject(irr::IrrlichtDevice* p_device);
	CSimObject(irr::IrrlichtDevice* p_device, int n_id);
	virtual ~CSimObject();
	
	virtual bool Init();
	virtual bool IsInitialized(){return m_bInitialized;};
	virtual bool CreateGraphics();
	virtual void RemoveGraphics();
	
	irr::scene::ISceneNode* GetNode(){return m_pNode;};
	
	void SetMeshFile(std::string str_mesh);
	void SetTextureFile(std::string str_texture);
	std::string GetMeshFileName(){return m_strMeshFileName;};
	std::string GetTextureFileName(){return m_strTextureFileName;};
	
	void SetNodeType(int n_node_type){m_nNodeType = n_node_type;};
	void SetMaterialColor(int n_a, int n_r, int n_g, int n_b);

	virtual void SetPosition(float f_x, float f_y, float f_z);
	virtual void SetRotation(float f_x, float f_y, float f_z);
	virtual void SetScale(float f_x, float f_y, float f_z);
	virtual void ScaleToGivenSize(float sizeX, float sizeY, float sizeZ);

	void SetFrameLoop(int n_start, int n_end);
	void SetAnimationSpeed(int n_speed);
	void SetDrawBoundingBox(bool b_draw);
	void SetLighting(bool b_lighting);
	void SetDrawGraphics(bool b_draw_graphics){m_bDrawGraphics = b_draw_graphics;};
	void SetConsole(bool b_console){m_bConsole = b_console;};
	
	void AddTimedLabel(bitbang::BBTime timeout, std::string str_text);
	
	virtual void OnObjectUpdate();
	virtual void OnSelect();
	virtual void OnDeselect();
	
private:
	bool m_bInitialized;
	
	CObjectLabelList m_LabelList;
	
protected:
	float m_fScaleX;
	float m_fScaleY;
	float m_fScaleZ;
	irr::IrrlichtDevice* m_pDevice;
	irr::video::IVideoDriver* m_pDriver;
	irr::scene::ISceneManager* m_pSmgr;
	irr::gui::IGUIEnvironment* m_pGuiEnv;
	irr::scene::IMesh* m_pMesh;
	irr::scene::ISceneNode* m_pNode;
	std::string m_strMeshFileName;
	std::string m_strTextureFileName;
	int m_nNodeType;
	irr::video::SColor* m_pMaterialColor;
	bool m_bConsole;
	bool m_bDrawGraphics;
};

#endif /*CSIMOBJECT_H*/
