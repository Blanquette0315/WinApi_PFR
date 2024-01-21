#pragma once
#include "CObject.h"
class CUI :
    public CObject
{
private:
    vector<CUI*>    m_vecChildUI;
    CUI* m_pParentUI;

    Vec2            m_vFinalPos;

    bool            m_bMouseOn;
    bool            m_bLbtnPressed;

public:
    CUI* GetParentUI() { return m_pParentUI; }
    CUI* GetAncestorUI();
    void AddChildUI(CUI* _pChildUI);
    bool IsMouseOn() { return m_bMouseOn; }
    Vec2 GetFinalPos() { return m_vFinalPos; }
    bool IsLBtnDown() { return m_bLbtnPressed; }
    vector<CUI*> GetChildUI() { return m_vecChildUI; }

    void EraseChildUI() { m_vecChildUI.erase(m_vecChildUI.end()-1); }

    virtual void SetISfocus(bool _bool) {};
    virtual void SetOwnerUI(CUI* _Onwer) {};

    // BattleMessageBox
    virtual bool IS_Message_End() { return false; };
    virtual void TextReset() {};
    virtual bool IS_Enter() { return false; };

    // PlayerMonsterInfoBox
    virtual void SetOutName(const wstring& _str) {};
    virtual void SetOutLevel(const UINT _level) {};
    virtual void SetOutMaxHP(const UINT _MaxHp) {};
    virtual void SetOutCurHP(const UINT _CurHP) {};
    virtual void SetOutMaxExp(const UINT _MaxExp) {};
    virtual void SetOutCurExp(const UINT _CurExp) {};

    virtual void SetSkillinfo(SKILL_INFO _info) {};

    // SelectPokemonBox
    virtual void GetShiftPokemon() { };
    virtual void SetIndex(UINT _index) {};

public:
    virtual void tick();
    virtual void render(HDC _dc);

    virtual void OnMouse() {}
    virtual void LBtnDown() { m_bLbtnPressed = true; }
    virtual void LBtnClicked() {}

private:
    void CheckMouseOn();

public:
    virtual CUI* Clone() = 0;

public:
    CUI();
    CUI(const CUI& _ui);
    ~CUI();

    friend class CUIMgr;
};

