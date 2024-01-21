#pragma once
#include "CUI.h"
class CPlayerMonsterInfoBox :
    public CUI
{
private:
    CImage* m_pImage;
    CImage* m_Font;
    CImage* m_HPbar;
    CImage* m_Expbar;
    CSound* m_pRedHPSound;
    wstring m_wsName;
    UINT m_MaxHP;
    UINT m_CurHP;
    UINT m_Level;
    UINT m_CurExp;
    UINT m_MaxExp;
    bool m_bSoundON;

private:
    Fint LinkText(char _text);

public:
    virtual void SetOutName(const wstring& _str) override { m_wsName = _str; }
    virtual void SetOutLevel(const UINT _level) override { m_Level = _level; }
    virtual void SetOutMaxHP(const UINT _MaxHp) override { m_MaxHP = _MaxHp; }
    virtual void SetOutCurHP(const UINT _CurHP) override { m_CurHP = _CurHP; }
    virtual void SetOutMaxExp(const UINT _MaxExp) override { m_MaxExp = _MaxExp; }
    virtual void SetOutCurExp(const UINT _CurExp) override { m_CurExp = _CurExp; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CPlayerMonsterInfoBox)

public:
    CPlayerMonsterInfoBox();
    ~CPlayerMonsterInfoBox();
};

