#pragma once
#include "CUI.h"
class CBoxArrow :
    public CUI
{
private:
    CImage* m_pImage;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CBoxArrow)

public:
    CBoxArrow();
    ~CBoxArrow();
};

