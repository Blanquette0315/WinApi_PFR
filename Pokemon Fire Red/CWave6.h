#pragma once
#include "CEnvironment.h"
class CWave6 :
    public CEnvironment
{
private:
    CImage* m_pImage;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
public:
    CWave6();
    ~CWave6();
};

