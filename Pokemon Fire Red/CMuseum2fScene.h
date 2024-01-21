#pragma once
#include "CScene.h"
class CMuseum2fScene :
    public CScene
{
    virtual void tick() override;

    virtual void enter() override;
    virtual void exit() override;

public:
    CMuseum2fScene();
    ~CMuseum2fScene();
};

