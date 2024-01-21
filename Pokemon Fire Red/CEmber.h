#pragma once
#include "CSkill.h"
class CEmber :
    public CSkill
{
private:
    CImage* m_pImage;
    CSound* m_pStartSound;
    CSound* m_pEndSound;
    bool m_AnimationEnd;
    Vec2 m_vStartPos;
    Vec2 m_vNowPos;
    Vec2 m_vEndPos;
    Vec2 m_vDiff;
    float m_fFacetime;
    bool StartAnimEnd;
    bool m_bStartSoundON;
    bool m_bEndSoundON;

public:
    virtual void SkillAct() override;
    virtual bool IS_Animation_End() override { return m_AnimationEnd; }

    virtual void SetSkillPos(Vec2 _StartPos, Vec2 _EndPos) override { m_vStartPos = _StartPos; m_vEndPos = _EndPos; };

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CEmber();
    ~CEmber();
};

