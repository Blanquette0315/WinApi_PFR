#pragma once
#include "CScene.h"
class CHouseBlackScene1 :
    public CScene
{
    virtual void tick() override;

    virtual void enter() override;
    virtual void exit() override;

public:
    CHouseBlackScene1();
    ~CHouseBlackScene1();
};

