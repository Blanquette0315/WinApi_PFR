#pragma once
#include "CPokemon.h"
class COnix :
    public CPokemon
{
private:
    CImage* m_pImage;
    CImage* m_pMiniImage;
    POKEMON_IO_TYPE m_eIOType;
    float m_fDuration;
    float m_fFaceTime;
    bool m_bIOAnim;

private:
    // 진화체에 따른 개체값 넣어주는 함수


public:
    // 진화 관련 함수
    //void ISEvolution();

public:
    virtual void SetIOType(POKEMON_IO_TYPE _Type) override { m_eIOType = _Type; }
    virtual void SetIOAnimOnce() override { m_bIOAnim = false; }
    virtual bool GetIOAnimOnce() override { return m_bIOAnim; }

public:
    virtual void SetAddPos() override { SetPos(GetPos() + Vec2(0, 5)); }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    COnix(UINT _CurLV);
    ~COnix();
};

