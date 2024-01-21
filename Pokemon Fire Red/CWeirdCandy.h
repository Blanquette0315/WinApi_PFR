#pragma once
#include "CItem.h"
class CWeirdCandy :
    public CItem
{
private:
    CImage* m_pImage;
    ITEM_TYPE m_eItemType;

    wstring m_wsExplanation;

public:
    virtual const wstring* GetExplanation() override { return &m_wsExplanation; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CWeirdCandy();
    ~CWeirdCandy();
};

