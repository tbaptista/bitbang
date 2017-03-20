//
//  TakeScreenShotSchedule.h
//  AntWorld
//
//  Created by João Miguel Moreira de Carvalho Brás Simões on 28/04/15.
//
//

#ifndef TAKESCREENSHOTSCHEDULE_H_
#define TAKESCREENSHOTSCHEDULE_H_

#include "BBSchedule.h"

using namespace bitbang;

class TakeScreenShotSchedule : public BBSchedule
{
public:
    TakeScreenShotSchedule(BBTime start_time);
    TakeScreenShotSchedule(BBTime start_time, BBTime repeat_time);
    virtual ~TakeScreenShotSchedule();
    
    virtual void Execute();
};


#endif //TAKESCREENSHOTSCHEDULE_H_