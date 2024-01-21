#pragma once
#include "CScene.h"
class CViridian_CITY :
    public CScene
{
private:
    CSound* m_pBGM;

public:
    virtual void tick() override;

    virtual void enter() override;
    virtual void exit() override;

public:
    CViridian_CITY();
    ~CViridian_CITY();
};

