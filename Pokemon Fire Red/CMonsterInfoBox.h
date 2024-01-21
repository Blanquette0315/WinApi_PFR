#pragma once
#include "CUI.h"
class CMonsterInfoBox :
    public CUI
{
private:
    CImage* m_pImage;
    CImage* m_Font;
    CImage* m_HPbar;
    wstring m_wsName;
    UINT m_Level;
    UINT m_MaxHP;
    UINT m_CurHP;

private:
    Fint LinkText(char _text);

public:
    virtual void SetOutName(const wstring& _str) override { m_wsName = _str; }
    virtual void SetOutLevel(const UINT _level) override { m_Level = _level; }
    virtual void SetOutMaxHP(const UINT _MaxHp) override { m_MaxHP = _MaxHp; }
    virtual void SetOutCurHP(const UINT _CurHP) override { m_CurHP = _CurHP; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CMonsterInfoBox)

public:
    CMonsterInfoBox();
    ~CMonsterInfoBox();
};

