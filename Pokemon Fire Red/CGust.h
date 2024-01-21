#pragma once
#include "CSkill.h"
class CGust :
    public CSkill
{
private:
    CImage* m_pImage;
    CSound* m_pWindSound;
    Vec2 OriPos;
    Vec2 EndPos1;
    Vec2 EndPos2;
    float m_fFacetime;
    bool m_AnimationEnd;
    bool m_pSoundON;

public:
    virtual void SkillAct() override;
    virtual bool IS_Animation_End() override { return m_AnimationEnd; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CGust();
    ~CGust();
};

