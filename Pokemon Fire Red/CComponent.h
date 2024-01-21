#pragma once
#include "CEntity.h"

class CObject;

class CComponent :
    public CEntity
{
private:
    const COMPONENT_TYPE    m_eType;
    CObject* m_pOwner;


public:
    COMPONENT_TYPE GetType() { return m_eType; }
    CObject* GetOwner() { return m_pOwner; }
    void SetOwner(CObject* _pOwner) { m_pOwner = _pOwner; }

public:
    virtual void tick() = 0;
    virtual void render(HDC _dc) {}


public:
    virtual CComponent* Clone() = 0;

public:
    CComponent(COMPONENT_TYPE _eType)
        : m_eType(_eType)
        , m_pOwner(nullptr)
    {
    }

    ~CComponent()
    {
    }

    friend class CObject;
    friend class CEnvironment;
};

