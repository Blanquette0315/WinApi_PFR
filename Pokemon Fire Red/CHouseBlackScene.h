#pragma once
#include "CScene.h"
class CHouseBlackScene :
    public CScene
{
    virtual void tick() override;

    virtual void enter() override;
    virtual void exit() override;

public:
    CHouseBlackScene();
    ~CHouseBlackScene();
};

