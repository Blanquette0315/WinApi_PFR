#pragma once
#include "CEnvironment.h"
class CWave4 :
    public CEnvironment
{
private:
    CImage* m_pImage;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
public:
    CWave4();
    ~CWave4();
};

