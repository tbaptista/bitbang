//
// Created by João Simões on 03/08/17.
//

#ifndef BULLET_TEST_CGRIDLATTICE_H
#define BULLET_TEST_CGRIDLATTICE_H

#include <IMeshSceneNode.h>
#include "GridLayer/GridLattice.h"

namespace bitbang
{

class CGridLattice : public GridLattice
{
public:
    CGridLattice();
    CGridLattice(irr::scene::ISceneManager* pParentSceneManager);
    CGridLattice(irr::scene::ISceneManager* pParentSceneManager, BBPoint pCenter, int pSize);
    virtual ~CGridLattice();
    
    virtual void Init();
    
    void SetIsVisible(bool pIsVisible) { m_isVisible = pIsVisible; };
    bool IsVisible() { return m_isVisible; };
    void SetIsRigid() {}
    
    void SetParentSceneManager(irr::scene::ISceneManager* pParentSceneManager) { m_parentSmgr = pParentSceneManager; };
    irr::scene::IMeshSceneNode* GetNode() { return m_sceneNode; };

protected:
    // Attributes for Irrlicht
    irr::scene::ISceneManager* m_parentSmgr;
    irr::scene::IMeshSceneNode* m_sceneNode;
    // Enables visual debug when defined as true
    bool m_isVisible;
    // This cell becomes a rigid object when this flag is true
    bool m_usePhysics;
    
    // Physical attributes
};

}


#endif //BULLET_TEST_CGRIDLATTICE_H
