#pragma once
#include "CSkill.h"
class CRockTomb :
    public CSkill
{
private:
    CImage* m_pImage;
    CImage* m_pxImage;
    CSound* m_pRockSound;
    CSound* m_pRockbgm;
    Vec2 OriPos;
    Vec2 Rock1Pos;
    Vec2 Rock2Pos;
    Vec2 Rock3Pos;
    float m_Rock1time;
    float m_Rock2time;
    float m_Rock3time;
    bool m_Rock2Start;
    bool m_Rock3Start;
    bool m_XStart;
    float m_xtime;

    bool m_bRockSoundON1;
    bool m_bRockSoundON2;
    bool m_bRockSoundON3;
    bool m_bRockbgmOn;

    bool m_AnimationEnd;

public:
    virtual void SkillAct() override;
    virtual bool IS_Animation_End() override { return m_AnimationEnd; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CRockTomb();
    ~CRockTomb();
};

