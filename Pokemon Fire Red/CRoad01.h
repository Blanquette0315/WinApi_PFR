#pragma once
#include "CScene.h"
class CRoad01 :
    public CScene
{
private:
    CSound* m_pBGM;

public:
    virtual void tick() override;

    virtual void enter() override;
    virtual void exit() override;

public:
    CRoad01();
    ~CRoad01();
};

