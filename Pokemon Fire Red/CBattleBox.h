#pragma once
#include "CUI.h"

class CPokemon;

class CBattleBox :
    public CUI
{
private:
    vector<CUI*>    m_vecChildUI;
    BATTLEBOX_TYPE  m_CurMenuType;
    CPokemon*       m_pTargetPokemon;
    CUI*            m_pOwnerUI;
    bool m_ISfocus;
    CImage* m_pImage;
    CImage* m_Font;
    CImage* m_PPFont;
    CSound* m_pSound;
    wstring m_arrSkillName[4];
    wstring    m_arrSkillMaxPP[4];
    wstring    m_arrSkillCurPP[4];
    wstring    m_arrSkillType[4];

private:
    Fint LinkText(char _text);
    void SetSkillInfo(SKILL_INFO _SkillInfo);

public:
    virtual void SetISfocus(bool _bool) override { m_ISfocus = _bool; }
    virtual void SetOwnerUI(CUI* _Onwer) override { m_pOwnerUI = _Onwer; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CBattleBox)

public:
    CBattleBox();
    CBattleBox(SKILL_INFO _SkillInfo);
    CBattleBox(CPokemon* _Object);
    ~CBattleBox();
};

