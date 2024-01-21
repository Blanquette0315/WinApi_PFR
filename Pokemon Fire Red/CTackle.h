#pragma once
#include "CSkill.h"
class CTackle :
    public CSkill
{
private:
    CImage* m_pImage;
    CSound* m_pSound;
    Vec2 OrigPos;
    Vec2 EndPos;
    Vec2 ElseEndPos;
    bool m_AnimationEnd;
    bool m_PosEnd;
    float m_facetime;
    bool m_bSoundON;

public:
    virtual void SkillAct() override;
    virtual bool IS_Animation_End() override { return m_AnimationEnd; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CTackle();
    ~CTackle();
};

