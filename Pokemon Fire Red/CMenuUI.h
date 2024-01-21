#pragma once
#include "CUI.h"
class CMenuUI :
    public CUI
{
private:
    vector<CUI*>    m_vecChildUI;
   // Vec2    m_vCapturePos;
    CImage* m_pImage;
    UINT m_CurMenuType;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;


public:
    CLONE(CMenuUI);

    CMenuUI();
    ~CMenuUI();
};

