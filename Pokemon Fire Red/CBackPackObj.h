#pragma once
#include "CObject.h"
class CBackPackObj :
    public CObject
{
private:
    CImage* m_pImage;
    UINT m_iImageNum;

public:
    virtual void SetImage(UINT _index) override;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CBackPackObj();
    ~CBackPackObj();
};

