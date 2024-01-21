#pragma once
#include "CScene.h"
class CPewter_CITY :
    public CScene
{
    virtual void tick() override;

    virtual void enter() override;
    virtual void exit() override;

public:
    CPewter_CITY();
    ~CPewter_CITY();
};

