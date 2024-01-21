#pragma once
#include "CScene.h"

class CPallet_CITY :
    public CScene
{
private:
    CSound* m_pBGM;

public:
    virtual void tick() override;

    virtual void enter() override;
    virtual void exit() override;

public:
    CPallet_CITY();
    ~CPallet_CITY();
};

