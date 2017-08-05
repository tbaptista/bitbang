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
                  int sizeX, int sizeZ, int cellSize);
    
    virtual ~CGridMapLayer();
    
    void InitGridSim();
    
    void SetIsVisible(bool pIsVisible) { m_IsVisible = pIsVisible; };
    void SetUsePhysics(bool pUsePhysics) { m_usePhysics = pUsePhysics; };

protected:
    void InitCellGraphics(int x, int z, int index, bool pIsVisible);
    
    bool m_IsVisible;
    bool m_usePhysics;
    
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
                                irr::s32 id, int sizeX, int sizeZ, int cellSize) :
                                GridMapLayer<T>(pName, sizeX, sizeZ, cellSize), smgr(mgr),
                                                irr::scene::ISceneNode(parent, mgr, id)
{
    numberOfVertex = this->nCellsX * this->nCellsZ;
    squares = new std::vector<irr::scene::IMeshSceneNode *>(this->nCellsX * this->nCellsZ);
    m_IsVisible = false;
    m_usePhysics = false;
}

/// GridMaplayer Destructor
/// \tparam T
template<class T>
inline
CGridMapLayer<T>::~CGridMapLayer()
{
    int cellIndex;
    for (int x = 0; x < this->nCellsX; x++)
    {
        for (int z = 0; z < this->nCellsZ; z++)
        {
            // Map 2D to 1D
            cellIndex = (x * this->nCellsZ) + z;
            
            // Draw matrix partition (Graphics). FIXME: Is it right?
            delete (*squares)[cellIndex];
        }
    }
    
    delete squares;
}

template<class T>
inline void CGridMapLayer<T>::InitGridSim()
{
    this->InitGrid();
    
    int cellIndex;
    for (int x = 0; x < this->nCellsX; x++)
    {
        for (int z = 0; z < this->nCellsZ; z++)
        {
            // Map 2D to 1D
            cellIndex = (x * this->nCellsZ) + z;
            
            // Draw matrix partition (Graphics)
            (this->matrix[cellIndex]).SetParentSceneManager(this->smgr);
            (this->matrix[cellIndex]).SetIsVisible(m_IsVisible);
            (this->matrix[cellIndex]).SetIsRigid(m_usePhysics);
            (this->matrix[cellIndex]).SetWorld(this->m_worldInterface);
            // Set the size of each lattice. As this is a grid, all cells have the same size
            (this->matrix[cellIndex]).SetSize(this->cellSize);
            // Init cell graphics and physics
            (this->matrix[cellIndex]).Init();
        }
    }
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
