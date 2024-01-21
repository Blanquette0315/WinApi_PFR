#pragma once
#include "CUI.h"

enum class SELECTPOKEMON_MSG_TYPE
{
    DEF,
    MENUON,
    CANCEL,
};

class CPokemonSelectBox :
    public CUI
{
private:
    CImage* m_pImage;
    CImage* m_pFont;
    CSound* m_pSound;
    CObject* m_pPlayer;
    POKETMONSELECT_TYPE m_eCurMenuType;
    UINT m_iCurTargetUI;
    UINT m_iPrevTargetUI;
    UINT m_iPokemonSize;
    bool m_ISfocus;

    SELECTPOKEMON_MSG_TYPE m_eMsgType;
    wstring m_wMsg;

private:
    Fint LinkText(char _text);

public:
    virtual void SetISfocus(bool _bool) override { m_ISfocus = _bool; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CPokemonSelectBox)

public:
    CPokemonSelectBox(CObject* _player);
    ~CPokemonSelectBox();
};

