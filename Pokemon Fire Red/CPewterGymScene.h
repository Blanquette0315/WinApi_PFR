#pragma once
#include "CScene.h"
class CPewterGymScene :
    public CScene
{
    virtual void tick() override;

    virtual void enter() override;
    virtual void exit() override;

public:
    CPewterGymScene();
    ~CPewterGymScene();
};

