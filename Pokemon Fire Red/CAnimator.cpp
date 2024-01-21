#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"
#include "CImage.h"

CAnimator::CAnimator()
	: CComponent(COMPONENT_TYPE::ANIMATOR)
	, m_pCurAnim(nullptr)
	, m_bRepeat(false)
	, m_arrMultAnim{}
	, m_bMult(false)
{
}

CAnimator::CAnimator(const CAnimator& _animator)
	: CComponent(_animator)
	, m_mapAnim()
	, m_pCurAnim(nullptr)
	, m_bRepeat(_animator.m_bRepeat)
	, m_arrMultAnim{}
	, m_bMult(false)
{
	map<wstring, CAnimation*>::const_iterator iter = _animator.m_mapAnim.begin();
	for (iter; iter != _animator.m_mapAnim.end(); ++iter)
	{
		CAnimation* pAnim = new CAnimation(*iter->second);
		pAnim->m_pAnimator = this;
		m_mapAnim.insert(make_pair(iter->first, pAnim));
	}

	//for (const auto& pair : _animator.m_mapAnim)
	//{
	//	pair.second;
	//}

	if (nullptr != _animator.m_pCurAnim)
	{
		Play(_animator.m_pCurAnim->GetName(), m_bRepeat);
	}
}

CAnimator::~CAnimator()
{
	Safe_Del_Map(m_mapAnim);
}

void CAnimator::tick()
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->tick();

		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->Reset();
		}
	}

	if (m_bMult)
	{
		for (int i = 0; i < m_arrMultAnim.size(); ++i)
		{
			if (nullptr != m_arrMultAnim[i])
			{
				m_arrMultAnim[i]->tick();

				if (m_bRepeat && m_arrMultAnim[i]->IsFinish())
				{
					m_arrMultAnim[i]->Reset();
				}
			}
		}
	}
}

void CAnimator::render(HDC _dc)
{
	if (nullptr != m_pCurAnim)
		m_pCurAnim->render(_dc);

	if (m_bMult)
	{
		for (int i = 0; i < m_arrMultAnim.size(); ++i)
		{
			if (nullptr != m_arrMultAnim[i])
			{
				m_arrMultAnim[i]->render(_dc);
			}
		}
	}
}

CAnimation* CAnimator::FindAnimation(const wstring& _strKey)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strKey);

	if (iter == m_mapAnim.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	m_pCurAnim->Reset();

	m_bRepeat = _bRepeat;
}

void CAnimator::CuntinuePlay(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}

// 애니메이션의 첫 장면을 셋팅해주면서 애니메이션을 실행해주는 함수
void CAnimator::Play(const wstring& _strName, UINT _iSetFrm, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	m_pCurAnim->Reset();
	m_pCurAnim->m_iCurFrm = _iSetFrm;

	m_bRepeat = _bRepeat;
}

void CAnimator::AddMultAnim(const wstring& _strName)
{
	CAnimation* TemAnim = FindAnimation(_strName);
	m_arrMultAnim.push_back(TemAnim);
}

void CAnimator::PlayMultAnim(bool _bRepeat)
{
	for (int i = 0; i < m_arrMultAnim.size(); ++i)
	{
		m_arrMultAnim[i]->Reset();
		m_bRepeat = _bRepeat;
		m_bMult = true;
	}
}

void CAnimator::CuntinuePlayMultAnim(bool _bRepeat)
{
	for (int i = 0; i < m_arrMultAnim.size(); ++i)
	{
		m_bRepeat = _bRepeat;
		m_bMult = true;
	}
}

void CAnimator::CreateAnimation(const wstring& _strName
	, CImage* _pImage, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset
	, float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation)
{
	CAnimation* pAnim = FindAnimation(_strName);

	if (nullptr != pAnim)
	{
		MessageBox(nullptr, L"Animation 이름 중복", L"Animation 생성 실패", MB_OK);
		return;
	}

	pAnim = new CAnimation;
	pAnim->Create(_pImage, _vLeftTop, _vSize, _vOffset, _fStep, _iFrmCount, _fDuration, _bCamRelation);
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;

	m_mapAnim.insert(make_pair(_strName, pAnim));
}

void CAnimator::CreateAnimationY(const wstring& _strName
	, CImage* _pImage, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset
	, float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation)
{
	CAnimation* pAnim = FindAnimation(_strName);

	if (nullptr != pAnim)
	{
		MessageBox(nullptr, L"Animation 이름 중복", L"Animation 생성 실패", MB_OK);
		return;
	}

	pAnim = new CAnimation;
	pAnim->CreateY(_pImage, _vLeftTop, _vSize, _vOffset, _fStep, _iFrmCount, _fDuration, _bCamRelation);
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;

	m_mapAnim.insert(make_pair(_strName, pAnim));
}
