#pragma once

class CObject;

template<typename T1, typename T2>
void Safe_Del_Map(const map<T1, T2>& _map)
{
	typename map<T1, T2>::const_iterator iter = _map.cbegin();
	for (iter; iter != _map.cend(); ++iter)
	{
		delete iter->second;
	}
}

// ==============
// Event Function
// ==============
#include "CEventMgr.h"

template<typename T>
T* Instantiate(Vec2 _vPos, LAYER_TYPE _type)
{
	T* pObject = new T;
	pObject->SetPos(_vPos);

	tEventInfo info = {};
	info.eType = EVENT_TYPE::CREATE_OBJECT;
	info.first = (DWORD_PTR)pObject;
	info.second = (DWORD_PTR)_type;

	CEventMgr::GetInst()->AddEvent(info);

	return pObject;
}

void EventDeleteObject(CObject* _pObj);
void SceneChange(SCENE_TYPE _eNextScene);
// void Re_Render(CObject* _pObj);
// void EventDeleteRe_Render(CObject* _pObj);