#pragma once
#include "CUI.h"
class CMenuArrow :
    public CUI
{
private:
    CImage* m_pImage;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CMenuArrow)

public:
    CMenuArrow();
    ~CMenuArrow();
};

