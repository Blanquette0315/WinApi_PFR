#pragma once
#include "CScene.h"
class CRedHouseScene1F :
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
    CRedHouseScene1F();
    ~CRedHouseScene1F();
};

