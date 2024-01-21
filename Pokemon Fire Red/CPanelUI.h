#pragma once
#include "CUI.h"
class CPanelUI :
    public CUI
{
private:
    Vec2    m_vCapturePos;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void LBtnDown() override;
    virtual void LBtnClicked() override;


public:
    CLONE(CPanelUI);

    CPanelUI();
    ~CPanelUI();
};

