#pragma once
#include "CScene.h"
class CBackpackScene :
    public CScene
{
public:
    virtual void tick() override;

    virtual void enter() override;
    virtual void exit() override;

public:
    CBackpackScene();
    ~CBackpackScene();
};

