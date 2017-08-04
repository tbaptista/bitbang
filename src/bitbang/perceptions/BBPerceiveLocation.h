//
// Created by João Simões on 11/07/17.
//

#ifndef BULLET_TEST_BBPERCEIVELOCATION_H
#define BULLET_TEST_BBPERCEIVELOCATION_H

#include <BBPoint.h>
#include <string>
#include "BBPerceptionNumber.h"

namespace bitbang
{

class BBWorldInterface;

class BBPerceiveLocation : public BBPerceptionNumber
{
public:
    BBPerceiveLocation(std::string pPerceptionName, BBWorldInterface* pWorldInterface);
    virtual ~BBPerceiveLocation();
    
    BBPoint GetPerceivedLocation() { return perceivedLocation; };
    bool HasLocation() { return hasLocation; };

protected:
    BBPoint perceivedLocation;
    bool hasLocation;
    
    BBWorldInterface* worldInterface;
};

}


#endif //BULLET_TEST_BBPERCEIVELOCATION_H
