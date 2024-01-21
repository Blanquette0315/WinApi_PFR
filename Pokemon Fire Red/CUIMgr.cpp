#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CKeyMgr.h"

#include "CScene.h"
#include "CUI.h"

CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
	, m_pTargetUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::tick()
{
	CScene* pCurScene = CSceneMgr::CreateMgr()->GetCurScene();

	// ���� Scene�� �ִ� UI ������Ʈ�� �����´�.
	const vector<CObject*>& vecObj = pCurScene->GetObjects(LAYER_TYPE::UI);

	for (int i = (int)vecObj.size() - 1; i >= 0; --i)
	{
		m_pTargetUI = FindTargetUI((CUI*)vecObj[i]);

		if (nullptr == m_pTargetUI)
			continue;

		if (IS_TAP(LBTN))
		{
			m_pTargetUI->LBtnDown();

			// ���� Ŭ���� UI�� �ֻ��� �θ� UI �� ����
			m_pFocusedUI = m_pTargetUI->GetAncestorUI();

			// �ش� UI �� FocusedUI �� ��ȯ�Ѵ�.
			pCurScene->SetFocusedUI(m_pFocusedUI);

			break;
		}
		else if (IS_RELEASE(LBTN))
		{
			if (m_pTargetUI->m_bLbtnPressed)
			{
				m_pTargetUI->LBtnClicked();
				m_pTargetUI->m_bLbtnPressed = false;
			}
		}
	}
}

CUI* CUIMgr::FindTargetUI(CUI* _pParentUI)
{
	CUI* pTargetUI = nullptr;

	static list<CUI*> queue;
	queue.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI && IS_RELEASE(LBTN))
			{
				pTargetUI->m_bLbtnPressed = false;
			}

			pTargetUI = pUI;
		}
		else if (IS_RELEASE(LBTN))
		{
			pUI->m_bLbtnPressed = false;
		}



		for (size_t i = 0; i < pUI->m_vecChildUI.size(); ++i)
		{
			queue.push_back(pUI->m_vecChildUI[i]);
		}
	}

	return pTargetUI;
}
