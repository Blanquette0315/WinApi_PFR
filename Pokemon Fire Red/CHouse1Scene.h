#pragma once
#include "CScene.h"
class CHouse1Scene :
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
    CHouse1Scene();
    ~CHouse1Scene();
};

