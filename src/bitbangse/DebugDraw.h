//
// Created by João Simões on 06/04/17.
//

#ifndef PROJECT_DEBUGDRAW_H
#define PROJECT_DEBUGDRAW_H


#include <LinearMath/btIDebugDraw.h>
#include <IrrlichtDevice.h>

class DebugDraw : public btIDebugDraw
{

public:
    DebugDraw(irr::IrrlichtDevice* const device);

    void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

    void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);

    void reportErrorWarning(const char* text);

    void draw3dText(const btVector3& location, const char* text);

    void setDebugMode(int mode);

    int getDebugMode() const;

private:
    int mode;
    irr::video::IVideoDriver* const driver;
    irr::ILogger* logger;
};


#endif //PROJECT_DEBUGDRAW_H
