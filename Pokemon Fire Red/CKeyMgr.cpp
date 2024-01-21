#include "pch.h"
#include "CKeyMgr.h"

int Keyarr[(UINT)KEY_TYPE::END] =
{
	'W',
	'A',
	'S',
	'D',

	'O',
	'T',

	VK_UP,
	VK_LEFT,
	VK_DOWN,
	VK_RIGHT,

	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,

	VK_LBUTTON,

	VK_SPACE,
	VK_ESCAPE,
	VK_RETURN,
};

CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::init()
{
	for (int i = 0; i < (UINT)KEY_TYPE::END; ++i)
	{
		m_KeyInfo.push_back(Key_Info{ (KEY_TYPE)i, KEY_STATE::NONE, false });
	}
}

void CKeyMgr::tick()
{
	if (GetFocus())
	{
		for (int i = 0; i < (UINT)KEY_TYPE::END; ++i)
		{
			if (GetAsyncKeyState(Keyarr[i]) & 0x8000)
			{
				if (m_KeyInfo[i].PrevPress)
				{
					m_KeyInfo[i]._KState = KEY_STATE::PRESS;
				}
				else
				{
					m_KeyInfo[i]._KState = KEY_STATE::TAP;
				}
				m_KeyInfo[i].PrevPress = true;
			}
			else
			{
				if (m_KeyInfo[i].PrevPress)
				{
					m_KeyInfo[i]._KState = KEY_STATE::RELEASE;
				}
				else
				{
					m_KeyInfo[i]._KState = KEY_STATE::NONE;
				}
				m_KeyInfo[i].PrevPress = false;
			}
		}

		POINT ptMouse = {};
		GetCursorPos(&ptMouse);
		ScreenToClient(CEngine::CreateMgr()->GetMainHwnd(), &ptMouse);
		m_vMousePos = ptMouse;
	}

	else
	{
		for (UINT i = 0; i < (UINT)KEY_TYPE::END; ++i)
		{
			if (KEY_STATE::TAP == m_KeyInfo[i]._KState || KEY_STATE::PRESS == m_KeyInfo[i]._KState)
				m_KeyInfo[i]._KState = KEY_STATE::RELEASE;
			else if (KEY_STATE::RELEASE == m_KeyInfo[i]._KState)
				m_KeyInfo[i]._KState = KEY_STATE::NONE;

			m_KeyInfo[i].PrevPress = false;
		}
	}
}