//
// Created by João Simões on 04/07/17.
//

#ifndef PROJECT_CGRIDMAPLAYER_H
#define PROJECT_CGRIDMAPLAYER_H

#include "GridLayer/GridMapLayer.h"
#include "../util/CUtilities.h"

namespace bitbang
{

// Define a generic grid layer. Each lattice can be of any type.
template<class T>
class CGridMapLayer : public GridMapLayer<T>, public irr::scene::ISceneNode
{
public:
    CGridMapLayer(std::string pName, irr::scene::ISceneNode *parent, irr::scene::ISceneManager *mgr, irr::s32 id,
                  int sizeX,
                  int sizeZ, int cellSize, bool isVisible);
    
    virtual ~CGridMapLayer() {};


protected:
    void InitCellGraphics(int x, int z, int index, bool pIsVisible);
    
    irr::u32 getMaterialCount() const;
    
    irr::video::SMaterial &getMaterial(irr::u32 i)
    { return Material; };
    const irr::core::aabbox3d <irr::f32> &getBoundingBox() const;
    void render();
    void onRegisterSceneNode();
    
    // Attributes for visual component
    int numberOfVertex;
    std::vector<irr::scene::IMeshSceneNode *> *squares;
    irr::u32 *indices;
    irr::core::aabbox3d <irr::f32> Box;
    irr::video::S3DVertex *Vertices;
    irr::video::SMaterial Material;
    irr::scene::ISceneManager *smgr;
    void InitMatrixVertex();
};

/// GidMapLayer Constructor
/// The grid map layer is initialized according ot the specified dimensions and size of each lattice.
/// \param parent Parent scene node on which visual grid layer will be drawn
/// \param mgr Scene Manager
/// \param id
/// \param sizeX Total size X
/// \param sizeZ Total size Z
/// \param cellSize Size of each lattice
template<class T>
inline
CGridMapLayer<T>::CGridMapLayer(std::string pName, irr::scene::ISceneNode *parent, irr::scene::ISceneManager *mgr,
                                irr::s32 id,
                                int sizeX, int sizeZ, int cellSize, bool pIsVisible) : GridMapLayer<T>(pName, sizeX, sizeZ, cellSize),
                                                                      smgr(mgr), irr::scene::ISceneNode(parent, mgr, id)
{
    numberOfVertex = this->nCellsX * this->nCellsZ;
    squares = new std::vector<irr::scene::IMeshSceneNode *>(this->nCellsX * this->nCellsZ);
    
    int cellIndex;
    for (int x = 0; x < this->nCellsX; x++)
    {
        for (int z = 0; z < this->nCellsZ; z++)
        {
            // Map 2D to 1D
            cellIndex = (x * this->nCellsZ) + z;
            
            // Draw matrix partition (Graphics)
            InitCellGraphics(x * this->cellSize, z * this->cellSize, cellIndex, pIsVisible);
        }
    }
}

template<class T>
inline void CGridMapLayer<T>::InitCellGraphics(int x, int z, int index, bool pIsVisible)
{
    (*squares)[index] = smgr->addCubeSceneNode();
    (*squares)[index]->setPosition(irr::core::vector3df(x + this->halfOfCellSize, 0, z + this->halfOfCellSize));
    cutilities::ScaleToSize((*squares)[index], this->cellSize, 0, this->cellSize);
    (*squares)[index]->setRotation(irr::core::vector3df(0, 0, 0)); // no rotation
    (*squares)[index]->setDebugDataVisible(1); //draws white edges in squares, useful for debugging and viewing
    (*squares)[index]->setVisible(pIsVisible);
}

template<class T>
void CGridMapLayer<T>::render()
{
    irr::video::IVideoDriver *driver = SceneManager->getVideoDriver();
    
    driver->setMaterial(Material);
    driver->setTransform(irr::video::ETS_WORLD, AbsoluteTransformation);
    
    driver->drawVertexPrimitiveList(&Vertices[0], numberOfVertex, &indices[0], numberOfVertex, irr::video::EVT_STANDARD,
                                    irr::scene::EPT_POINTS, irr::video::EIT_32BIT);
}

template<class T>
const irr::core::aabbox3d <irr::f32> &CGridMapLayer<T>::getBoundingBox() const
{
    return Box;
}

template<class T>
irr::u32 CGridMapLayer<T>::getMaterialCount() const
{
    return 1;
}

template<class T>
void CGridMapLayer<T>::InitMatrixVertex()
{
    indices = new irr::u32[numberOfVertex];
    for (int i = 0; i < numberOfVertex; i++)
    {
        if (i + 1 < numberOfVertex)
            indices[i] = (irr::u32) i + 1;
        else
            indices[i] = (irr::u32) i - 1;
    }
}

template<class T>
void CGridMapLayer<T>::onRegisterSceneNode()
{
    if (IsVisible)
        SceneManager->registerNodeForRendering(this);
    
    irr::scene::ISceneNode::OnRegisterSceneNode();
}
    
}

#endif //PROJECT_CGRIDMAPLAYER_H
