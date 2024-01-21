#pragma once
class CEntity
{
private:
	static UINT g_GlobalID;

private:
	wstring		m_strName;
	const UINT	m_ID;

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetID() { return m_ID; }

public:
	// 기본 대입 연산자의 구조상 const 맴버의 대입이 불가능하기 때문에 delete 처리된다.
	/*CEntity& operator = (const CEntity& _other)
	{
		m_strName = _other.m_strName;
		m_ID = _other.m_ID;
	}*/


public:
	CEntity();

	// 아이디까지 복사되는 문제를 막기위해서, 직접 복사생성자를 구현함
	CEntity(const CEntity& _other);

	virtual ~CEntity();
};

