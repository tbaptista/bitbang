//
//  SeatsBlock.h
//  AircraftEvacuation
//
//  Created by João Simões on 31/07/15.
//
//

#ifndef __AircraftEvacuation__SeatsBlock__
#define __AircraftEvacuation__SeatsBlock__

#include <stdio.h>
#include <set>

#include "CSimObject.h"
#include "Node.hpp"
#include "GenericComponent.h"
#include "BoundingBox.h"
#include "irrlicht.h"
#include "Utility.h"

using namespace std;

class SeatsBlock : public GenericComponent
{
public:
    static const int CLASSID = 1003;
    
    SeatsBlock(irr::IrrlichtDevice* p_device, int p_nRows, int p_SeatsPerRow, float p_PosX, float p_PosZ, float p_SeatWidth, float p_SeatDepth, float p_SeatPitch, float p_SpaceBetweenSeats, bool p_HasAisleInFront, bool p_CirculationAllowed);
    virtual ~SeatsBlock();
    int GetNumberOfRows() { return numberOfRows; };
    int GetSeatsPerRow() { return seatsPerRow; };
    
    virtual bool Init();
    
    void InitBase();
    Node* GetGraphNodes() { return nodes; };
    Node* GetNodeAt(int position) { return &nodes[position]; };
    
    void SetPlaceAsBusy(int k) { occupation[k] = true; };
    bool IsBusy(int k) { return occupation[k]; };
    bool IsCirculationAllowed() { return circulationAllowed; };
    bool HasAisleInFront() { return hasAisleInFront; };
    Node* GetFreeSeat();
    
    float GetSeatWidth() { return seatWitdh; };
    float GetSeatDepth() { return seatDepth; };
    
private:
    int numberOfRows;
    int seatsPerRow;
    float seatWitdh;
    float seatDepth;
    float seatPitch;
    float spaceBetweenSeats;
    bool *occupation;
    bool hasAisleInFront;
    bool circulationAllowed;
    
    set<int> freeSeats;
    
    Node* nodes;
};

#endif /* defined(__AircraftEvacuation__SeatsBlock__) */
