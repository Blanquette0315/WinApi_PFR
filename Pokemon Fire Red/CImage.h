#pragma once
#include "CResource.h"
class CImage :
    public CResource
{
private:
    HBITMAP     m_hBit;
    HDC         m_hDC;

    UINT        m_iWidth;
    UINT        m_iHeight;

private:
    virtual int Load(const wstring& _strFilePath) override;
    virtual int Create(UINT _iWidth, UINT _iHeight);

public:
    HDC GetDC() { return m_hDC; }
    UINT GetWidth() { return m_iWidth; }
    UINT GetHeight() { return m_iHeight; }

public:
    CImage();
    ~CImage();

    friend class CResourceMgr;
};

