#pragma once
#include "CUI.h"
class CPokemonBox :
    public CUI
{
private:
    CImage* m_pImage;
    CImage* m_pTargetImage;
    CImage* m_pFont;
    CImage* m_pHPbar;
    CPokemon* m_pPokemon;
    UINT m_iIndex;
    bool m_bIS_Target;
    bool m_bPressEnter;
    bool m_bAnim;

public:
    virtual void SetIndex(UINT _index) override { m_iIndex = _index; }
    virtual void SetISfocus(bool _bool) override { m_bIS_Target = _bool; };
    virtual bool IS_Enter() override;
    Fint LinkText(char _text);
    virtual void GetShiftPokemon() override;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CPokemonBox)

public:
    CPokemonBox(CPokemon* _Pokemon);
    ~CPokemonBox();
};

