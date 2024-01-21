#pragma once
#include "CUI.h"
class CCancelBox :
    public CUI
{
private:
    CImage* m_pImage;
    CImage* m_pTargetImage;
    bool m_bIS_Target;

public:
    virtual void SetISfocus(bool _bool) override { m_bIS_Target = _bool; };

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CCancelBox)

public:
    CCancelBox();
    ~CCancelBox();
};

