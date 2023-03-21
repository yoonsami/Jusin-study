#pragma once
#include "Line.h"
class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();
	
public:
	void	Init();
	void	Render(HDC hDC);
	void	Release();
	void	Update();

public:
	static CLineMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CLineMgr;
		return m_pInstance;
	}
	static list<CLine*> Get_LineList()
	{ 
		return m_pInstance->m_LineList;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	list<CLine*> m_LineList;
	static CLineMgr* m_pInstance;
};

