#pragma once
#include "CScene.h"
class CMartScene :
    public CScene
{
    virtual void tick() override;

    virtual void enter() override;
    virtual void exit() override;

public:
    CMartScene();
    ~CMartScene();
};

