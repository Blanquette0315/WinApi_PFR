#pragma once
#include "CObject.h"
class CBackPackRightArrow :
    public CObject
{
private:
    CImage* m_pImage;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CBackPackRightArrow();
    ~CBackPackRightArrow();
};

