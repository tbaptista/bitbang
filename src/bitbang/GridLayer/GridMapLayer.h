//
// Created by João Simões on 29/06/17.
//

#ifndef BULLET_TEST_GRIDMAPLAYER_H
#define BULLET_TEST_GRIDMAPLAYER_H

#include <vector>
#include <string>
#include <cmath>
#include <bitbang/src/bitbang/BBWorldInterface.h>
#include "GridLayer/GridMapLayerInterface.h"
#include "BBPoint.h"
#include "GridLattice.h"

namespace bitbang
{

// Define a generic grid layer. Each lattice can be of any type.
template<class T>
class GridMapLayer : public GridMapLayerInterface
{
public:
    GridMapLayer(std::string pName, int sizeX,
                 int sizeZ, int cellSize);
    
    void SetWorld(BBWorldInterface* pWorldInterface) { this->m_worldInterface = pWorldInterface; } ;

    virtual ~GridMapLayer() { delete matrix; };
    virtual int GetSizeX() { return sizeX; };
    virtual int GetSizeZ() { return sizeZ; };
    virtual int GetNCellsX() { return nCellsX; };
    virtual int GetNCellsZ() { return nCellsZ; };
    virtual int GetCellSize() { return cellSize; };
    virtual int GetCellIndex(float x, float z);
    virtual int GetIndex(float pos);
    
    virtual GridLattice* GetCellAt(float x, float z);
    virtual GridLattice* GetCellAt(int x, int z);
    virtual GridLattice* GetCellAt(int p1DPos);

    virtual std::string GetName() { return name; };
    virtual void SetName(std::string pName) { name = pName; };
    int MapTo1D(int x, int z);
    
    // Method for updating grid layer. By default, the grid layer is not updated
    virtual void Update(double d_elapsed_time = 0) {};

protected:
    // Grid dimensions specifications
    int sizeX;
    int sizeZ;
    int nCellsX;
    int nCellsZ;
    int cellSize;
    float halfOfCellSize;
    float squaredCellSize;

    // Unique name for this grid layer
    std::string name;
    
    // Interface for the related world
    BBWorldInterface* m_worldInterface;

    T *matrix;
};

///
/// \param pName Unique name for this grid map layer
/// \param sizeX Size along X
/// \param sizeZ Size along Z
/// \param cellSize Size of each lattice
template<class T>
inline
GridMapLayer<T>::GridMapLayer(std::string pName, int sizeX, int sizeZ, int cellSize) :
        name(pName), sizeX(sizeX), sizeZ(sizeZ), cellSize(cellSize)
{
    // Check whether it is possible to obtain an integer number of cells; If not, an additional cell is considered.
    if ((sizeX % cellSize) == 0)
        this->nCellsX = sizeX / cellSize;
    else
        this->nCellsX = (sizeX / cellSize) + 1;

    // Check whether it is possible to obtain an integer number of cells; If not, an additional cell is considered.
    if ((sizeZ % cellSize) == 0)
        this->nCellsZ = sizeZ / cellSize;
    else
        this->nCellsZ = (sizeZ / cellSize) + 1;

    halfOfCellSize = (float) cellSize / 2;
    squaredCellSize = powf(cellSize, 2.0);

    matrix = new T[nCellsX * nCellsZ];

    int cellIndex;
    for (int x = 0; x < nCellsX; x++)
    {
        for (int z = 0; z < nCellsZ; z++)
        {
            // Map 2D to 1D
            cellIndex = (x * nCellsZ) + z;

            // Set the center of GridLayer partition
            BBPoint center;
            center.SetX(halfOfCellSize + (x * cellSize));
            center.SetY(0); // Only 2 Dimensions
            center.SetZ(halfOfCellSize + (z * cellSize));
            matrix[cellIndex].SetCenter(center);
        }
    }
}

/// Map from 2D continuous coordinates to 1D discrete matrix
///
/// \param x Continuous X coordinate
/// \param y Continuous Y coordinate
/// \param z Continuous Z coordinate
/// \return The index to the corresponded matrix cell
template<class T>
int GridMapLayer<T>::GetCellIndex(float x, float z)
{
    int cellX, cellZ;

    // Convert X to discrete
    cellX = int(x / (float) this->cellSize);
    // Convert Z to discrete
    cellZ = int(z / (float) this->cellSize);

    return MapTo1D(cellX, cellZ);
}

/// Map from 1D given discrete coordinates
/// \param x Discrete X coordinate
/// \param z Discrete Z coordinate
/// \return
template<class T>
int GridMapLayer<T>::MapTo1D(int x, int z)
{
    return (x * this->nCellsZ) + z;
}

template<class T>
GridLattice* GridMapLayer<T>::GetCellAt(float x, float z)
{
    int cellPos = GetCellIndex(x, z);
    
    return &matrix[cellPos];
}

template<class T>
GridLattice* GridMapLayer<T>::GetCellAt(int x, int z)
{
    int cellPos = MapTo1D(x, z);
    
    return &matrix[cellPos];
}

template<class T>
GridLattice* GridMapLayer<T>::GetCellAt(int p1DPos)
{
    return &matrix[p1DPos];
}

template<class T>
int GridMapLayer<T>::GetIndex(float pos)
{
    return int(pos / this->cellSize);
}

}

#endif //BULLET_TEST_GRIDMAPLAYER_H
