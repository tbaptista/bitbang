#ifndef _VISUAL_MAP_H_
#define _VISUAL_MAP_H_

#include "irrlicht.h"


class AntWorldVisualMap : public irr::scene::ISceneNode
{
public:
	AntWorldVisualMap(irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, irr::s32 id, vector< vector<float> >& m_pPheromoneMap);
	void updatePoint(int i, int j, float value);
	virtual void OnRegisterSceneNode();
	virtual void render();
	virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
	virtual irr::u32 getMaterialCount() const;
	virtual irr::video::SMaterial& getMaterial(irr::u32 i);
	~AntWorldVisualMap(void);

private:
	
	int sizeX;
	int sizeZ;
	int maxInfluence;
	int resizeFactor;
	int numVertex;
	irr::u16 *indices;

	irr::core::aabbox3d<irr::f32> Box;
	irr::video::S3DVertex *Vertices;
	irr::video::SMaterial Material;

};

#endif //_VISUAL_MAP_H_

