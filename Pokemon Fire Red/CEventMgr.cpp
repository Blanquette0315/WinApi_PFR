#include "pch.h"
#include "CEventMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CUI.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::tick()
{
	// Dead Object 를 실제로 삭제한다.
	for (size_t i = 0; i < m_vecDeadObj.size(); ++i)
	{
		SAFE_DELETE(m_vecDeadObj[i]);
	}
	m_vecDeadObj.clear();


	// 이번 프레임에 쌓인 이벤트를 처리한다.
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		tEventInfo& evt = m_vecEvent[i];

		switch (evt.eType)
		{
		case EVENT_TYPE::CREATE_OBJECT:
		{
			CObject* pNewObject = (CObject*)evt.first;
			LAYER_TYPE eLayer = (LAYER_TYPE)evt.second;

			CScene* pCurScene = CSceneMgr::CreateMgr()->GetCurScene();
			pCurScene->AddObject(pNewObject, eLayer);

			break;
		}
		
		case EVENT_TYPE::DELETE_OBJECT:
		{
			CObject* pDeadObj = (CObject*)evt.first;

			if (!pDeadObj->IsDead())
			{
				m_vecDeadObj.push_back(pDeadObj);
				pDeadObj->SetDead();
			}

			break;
		}

		
		case EVENT_TYPE::SCENE_CHANGE:
		{
			SCENE_TYPE eSceneType = (SCENE_TYPE)evt.first;

			CSceneMgr::CreateMgr()->ChangeScene(eSceneType);

			break;
		}

		


		case EVENT_TYPE::RE_RENDER:
		{
			CObject* pRerenderObj = (CObject*)evt.first;
			UINT temOjbID = (UINT)evt.second;

			if (!pRerenderObj->IsDead())
			{
				//m_vecRenderObejct.push_back(pRerenderObj);
				//m_ReRenderEventCount = 0;

				m_mapRenderObject.insert(make_pair(temOjbID, pRerenderObj));
			}

			break;
		}

		case EVENT_TYPE::DELETE_RE_RENDER:
		{
			//m_vecRenderObejct.erase(m_vecRenderObejct.end()-1);
			//m_ReRenderEventCount = 0;

			m_mapRenderObject.erase((UINT)evt.second);

			break;
		}

		case EVENT_TYPE::SETUIFOCUS:
		{
			CUI* pTargetUI = (CUI*)evt.first;
			pTargetUI->SetISfocus(true);

			break;
		}

		break;
		}
	}

	m_vecEvent.clear();
}

void CEventMgr::render(HDC _dc)
{
	/*for (size_t i = 0; i < m_vecRenderObejct.size(); ++i)
	{
		m_vecRenderObejct[i]->render(_dc);
	}*/

	map< UINT, CObject*>::iterator iter(m_mapRenderObject.begin());

	for (; iter != m_mapRenderObject.end(); ++iter)
	{
		iter->second->render(_dc);
	}
}

void CEventMgr::Re_Render(CObject* _pObj)
{
	tEventInfo info = {};
	info.eType = EVENT_TYPE::RE_RENDER;
	info.first = (DWORD_PTR)_pObj;
	info.second = _pObj->GetID();
	CEventMgr::CreateMgr()->AddEvent(info);
}

void CEventMgr::EventDeleteRe_Render(CObject* _pObj)
{
	tEventInfo info = {};
	info.eType = EVENT_TYPE::DELETE_RE_RENDER;
	info.first = (DWORD_PTR)_pObj;
	info.second = (DWORD_PTR)_pObj->GetID();
	CEventMgr::CreateMgr()->AddEvent(info);
}

void CEventMgr::EventSetUIFocus(CUI* _pObj)
{
	tEventInfo info = {};
	info.eType = EVENT_TYPE::SETUIFOCUS;
	info.first = (DWORD_PTR)_pObj;
	CEventMgr::CreateMgr()->AddEvent(info);
}

void CEventMgr::DeleteReRenderM()
{
	m_mapRenderObject.clear();
}
