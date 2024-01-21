#pragma once
#include "CUI.h"
class CCurPokemonBox :
    public CUI
{
private:
    CImage* m_pImage;
    CImage* m_pTargetImage;
    CImage* m_pFont;
    CImage* m_pHPbar;
    CPokemon* m_pPokemon;
    bool m_bIS_Target;
    bool m_bAnim;
    bool    m_bPressEnter;

public:
    virtual void SetISfocus(bool _bool) override { m_bIS_Target = _bool; };
    virtual bool IS_Enter() override { return m_bPressEnter; }
    Fint LinkText(char _text);

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CCurPokemonBox)

public:
    CCurPokemonBox(CPokemon* _Pokemon);
    ~CCurPokemonBox();
};

