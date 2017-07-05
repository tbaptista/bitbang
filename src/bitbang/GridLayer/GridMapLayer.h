//
// Created by João Simões on 29/06/17.
//

#ifndef BULLET_TEST_GRIDMAPLAYER_H
#define BULLET_TEST_GRIDMAPLAYER_H

#include <vector>
#include <string>
#include <cmath>
#include "GridLayer/GridMapLayerInterface.h"
#include "BBPoint.h"

namespace bitbang
{

// Define a generic grid layer. Each lattice can be of any type.
template<class T>
class GridMapLayer : public GridMapLayerInterface
{
public:
    GridMapLayer(std::string pName, int sizeX,
                 int sizeZ, int cellSize);

    virtual ~GridMapLayer() { delete matrix; };
    virtual int GetSizeX() { return sizeX; };
    virtual int GetSizeZ() { return sizeZ; };
    virtual int GetNCellsX() { return nCellsX; };
    virtual int GetNCellsZ() { return nCellsZ; };
    virtual int GetCellSize() { return cellSize; };
    virtual int GetCellIndex(float x, float z);

    virtual std::string GetName() { return name; };
    virtual void SetName(std::string pName) { name = pName; };
    
    // Method for updating grid layer. By default, the grid layer is not updated
    virtual void Update() {};

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

    T *matrix;
};

///
/// \param pName Unique name for this grid map layer
/// \param sizeX Size along X
/// \param sizeZ Size along Z
/// \param cellSize Size of each lattice
template<class T>
inline
GridMapLayer<T>::GridMapLayer(std::string pName, int sizeX, int sizeZ, int cellSize) : name(pName), sizeX(sizeX), sizeZ(sizeZ), cellSize(cellSize)
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
    cellX = int(x / this->cellSize);
    // Convert Z to discrete
    cellZ = int(z / this->cellSize);

    return (cellX * this->nCellsZ) + cellZ;
}

}

#endif //BULLET_TEST_GRIDMAPLAYER_H
