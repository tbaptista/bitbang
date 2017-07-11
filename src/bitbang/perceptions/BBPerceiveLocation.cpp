//
// Created by João Simões on 11/07/17.
//

#include "BBPerceiveLocation.h"

namespace bitbang
{

BBPerceiveLocation::BBPerceiveLocation(std::string pPerceptionName, BBWorldInterface *pWorldInterface) :
{
    hasLocation = false;
    worldInterface = pWorldInterface;
    m_strName = pPerceptionName;
    m_bModifiedByNonTerminalActions = false;
}

BBPerceiveLocation::~BBPerceiveLocation()
{

}

}
