#pragma once
#include "CSkill.h"
class CVinewhip :
    public CSkill
{
private:
    CImage* m_pImage;
    CImage* m_pImage2;
    bool m_AnimationEnd;

public:
    virtual void SkillAct() override;
    virtual bool IS_Animation_End() override { return m_AnimationEnd; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CVinewhip();
    ~CVinewhip();
};

