#pragma once

#include "CCameraMgr.h"

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<Key_Info>	m_KeyInfo;
	Vec2				m_vMousePos;

public:
	void init();
	void tick();

public:
	KEY_STATE GetKeyState(KEY_TYPE _key)
	{
		return m_KeyInfo[(UINT)_key]._KState;
	}
	
	Vec2 GetMousePos() { return m_vMousePos; }
	Vec2 GetMouseRealPos() { return CCameraMgr::CreateMgr()->GetRealPos(m_vMousePos); }
};

