#pragma once
#include "CEnvironment.h"
class CWave7 :
    public CEnvironment
{
private:
    CImage* m_pImage;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
public:
    CWave7();
    ~CWave7();
};

