#pragma once
#include "CObject.h"
class CGrassBattle :
    public CObject
{
private:
    CImage* m_pImage; // BackGround Image аж╪р

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CGrassBattle();
    virtual ~CGrassBattle();
};

