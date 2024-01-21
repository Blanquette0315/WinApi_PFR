#pragma once
#include "CScene.h"
class CMuseum1fScene :
    public CScene
{
    virtual void tick() override;

    virtual void enter() override;
    virtual void exit() override;

public:
    CMuseum1fScene();
    ~CMuseum1fScene();
};

