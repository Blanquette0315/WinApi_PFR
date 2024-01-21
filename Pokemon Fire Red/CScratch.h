#pragma once
#include "CSkill.h"
class CScratch :
    public CSkill
{
private:
    CImage* m_pImage;
    CSound* m_pSound;
    bool m_AnimationEnd;
    bool m_bSoundON;

public:
    virtual void SkillAct() override;
    virtual bool IS_Animation_End() override { return m_AnimationEnd; }
    
public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CScratch();
    ~CScratch();
};

