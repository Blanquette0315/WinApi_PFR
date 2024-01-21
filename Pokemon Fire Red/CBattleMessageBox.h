#pragma once
#include "CUI.h"
class CBattleMessageBox :
    public CUI
{
private:
    CImage* m_pImage;
    CImage* m_Font;
    CSound* m_pEnterSound;
    wstring m_arrMessage;
    wstring m_arrMessage2;
    bool    m_HaveText;
    bool    m_bPressEnter;

    UINT m_Tick;
    float m_fDuration;
    bool m_bEndMessage;
    bool m_bEndSwich;

private:
    Vec2 LinkText(char _text);

public:
    virtual void SetText(const wstring& _str) override;
    virtual void TextReset() override { m_Tick = 0; m_bPressEnter = false; m_bEndMessage = false; };
    virtual bool IS_Message_End() override { return m_bEndMessage; }
    virtual bool IS_Enter() override { return m_bPressEnter; }
public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CBattleMessageBox)

public:
    CBattleMessageBox();
    ~CBattleMessageBox();
};

