#pragma once
#include "CObject.h"
class CItem :
    public CObject
{
private:
    UINT m_price;

public:
    virtual const wstring* GetExplanation() { wstring tem = L""; return &tem; };

public:
    CItem();
    ~CItem();
};

