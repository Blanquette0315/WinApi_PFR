#pragma once
#include "CEntity.h"
class CResource :
    public CEntity
{
private:
    wstring     m_strKey;
    wstring     m_strRelativePath;

public:
    const wstring& GetKey() { return m_strKey; }
    const wstring& GetRelativePath() { return m_strRelativePath; }

    void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
    void SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }


public:
    virtual int Load(const wstring& _strFilePath) = 0;

public:
    CResource();
    virtual ~CResource();
};

