#include "pch.h"
#include "func.h"

#include "CObject.h"
#include "CImage.h"
#include "CResourceMgr.h"
#include "CEventMgr.h"

void EventDeleteObject(CObject* _pObj)
{
	tEventInfo info = {};
	info.eType = EVENT_TYPE::DELETE_OBJECT;
	info.first = (DWORD_PTR)_pObj;
	CEventMgr::CreateMgr()->AddEvent(info);
}

void SceneChange(SCENE_TYPE _eNextScene)
{
	tEventInfo info = {};
	info.eType = EVENT_TYPE::SCENE_CHANGE;
	info.first = (DWORD_PTR)_eNextScene;
	CEventMgr::CreateMgr()->AddEvent(info);
}