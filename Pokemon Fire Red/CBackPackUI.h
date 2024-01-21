#pragma once
#include "CUI.h"

class CItem;

class CBackPackUI :
    public CUI
{
private:
    CImage* m_pImage;
    CImage* m_pFont;
    vector<CObject*> m_arrOBJ;

    vector<CItem*> m_arrExpendablesIT;
    vector<UINT> m_arrExpendablesITNum;
    //vector<CItem*> m_arrBallIT;

    CItem* m_pTargetItem;
    wstring m_arrMessage;

    UINT m_iBackCount;
    UINT m_iIndex;
    UINT m_iMaxIndex;

    bool m_bTargetUI;

private:
    Fint LinkText(char _text);

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;



public:
    CLONE(CBackPackUI);

    CBackPackUI();
    ~CBackPackUI();
};
