#pragma once
#include "CScene.h"
class CCenter1fScene :
    public CScene
{
private:
    CSound* m_pBgm;
    CSound* m_pEixtSound;
    CSound* m_pInSound;

public:
    virtual void tick() override;

    virtual void enter() override;
    virtual void exit() override;

public:
    CCenter1fScene();
    ~CCenter1fScene();
};

