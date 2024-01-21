#pragma once
#include "CScene.h"
class CPPokeInfoScene :
    public CScene
{
public:
    virtual void tick() override;

    virtual void enter() override;
    virtual void exit() override;

public:
    CPPokeInfoScene();
    ~CPPokeInfoScene();
};

