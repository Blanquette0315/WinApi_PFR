#pragma once
#include "CSkill.h"
class CWaterGun :
    public CSkill
{
private:
    CImage* m_pImage;
    CImage* m_pHit;
    CImage* m_pOtherImage;
    CSound* m_pSoundStart;
    CSound* m_pSoundEnd;
    bool m_AnimationEnd;
    Vec2 m_vStartPos;
    Vec2 m_vNowPos;
    Vec2 m_vEndPos;
    Vec2 m_vDiff;
    float m_fFacetime;
    bool StartAnimEnd;
    bool m_bSoundStartON;
    bool m_bSoundEndON;

public:
    virtual void SkillAct() override;
    virtual bool IS_Animation_End() override { return m_AnimationEnd; }

    virtual void SetSkillPos(Vec2 _StartPos, Vec2 _EndPos) override { m_vStartPos = _StartPos; m_vEndPos = _EndPos; };

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CWaterGun();
    ~CWaterGun();
};

