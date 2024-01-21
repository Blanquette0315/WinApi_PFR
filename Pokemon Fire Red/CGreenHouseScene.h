#pragma once
#include "CScene.h"
class CGreenHouseScene :
    public CScene
{
private:
    CSound* m_pEixtSound;
    CSound* m_pInSound;

public:
    virtual void tick() override;

    virtual void enter() override;
    virtual void exit() override;

public:
    CGreenHouseScene();
    ~CGreenHouseScene();
};

