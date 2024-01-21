#pragma once
#include "CEnvironment.h"
class CWave2 :
    public CEnvironment
{
private:
    CImage* m_pImage;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
public:
    CWave2();
    ~CWave2();
};

