#pragma once
#include "CUI.h"
class COakLabUI :
    public CUI
{
private:
    CImage* m_pImage;
    CImage* m_pFont;
    CSound* m_pSound;
    UINT    m_iMenuType;
    bool m_bIS_Target;
    wstring m_wCharmander;
    wstring m_wBulbasaur;
    wstring m_wSquirtle;

private:
    Fint LinkText(char _text);

public:
    virtual void SetISfocus(bool _bool) override { m_bIS_Target = _bool; };

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CLONE(COakLabUI)

public:
    COakLabUI();
    ~COakLabUI();
};
