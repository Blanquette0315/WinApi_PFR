#pragma once
#include "CScene.h"
class CRedHouseScene2F :
    public CScene
{
private:
    CSound* m_pEixtSound;
    CSound* m_pInSound;
    CSound* m_pBGM;

public:
    virtual void tick() override;

    virtual void enter() override;
    virtual void exit() override;

public:
    CRedHouseScene2F();
    ~CRedHouseScene2F();
};

