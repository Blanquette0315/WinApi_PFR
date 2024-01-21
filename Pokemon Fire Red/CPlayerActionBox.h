#pragma once
#include "CUI.h"
class CPlayerActionBox :
    public CUI
{
private:
    CImage* m_pImage;
    CSound* m_pSound;
    vector<CUI*>    m_vecChildUI;
    PLAYER_ACTION_TYPE m_CurMenuType;
    SKILL_INFO m_Skillinfo;
    CPokemon* m_targetPokemon;
    bool m_ISfocus;
    CObject* m_pPlayer;
public:
    void SetFocus(bool _IsFocus) { m_ISfocus = _IsFocus; }
    virtual void SetSkillinfo(SKILL_INFO _info) override { m_Skillinfo = _info; }

    virtual void SetISfocus(bool _bool) override { m_ISfocus = _bool; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CPlayerActionBox)

public:
    CPlayerActionBox();
    CPlayerActionBox(CPokemon* _Object , CObject* _player);
    ~CPlayerActionBox();
};

