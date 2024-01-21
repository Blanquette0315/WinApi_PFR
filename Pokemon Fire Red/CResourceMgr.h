#pragma once

class CResource;
class CImage;
class CSound;

class CResourceMgr
{
	SINGLE(CResourceMgr);
private:
	map<wstring, CImage*> m_mapImage;
	map<wstring, CSound*> m_mapSound;

public:
	void init();


public:
	CImage* LoadImg(const wstring& _strKey, const wstring& _strRelativePath);
	CImage* CreateImg(const wstring& _strKey, UINT _iWidth, UINT _iHeight);
	CImage* FindImg(const wstring& _strKey);

	CSound* LoadSound(const wstring& _strKey, const wstring& _strRelativePath);
	CSound* FindSound(const wstring& _strKey);
};

