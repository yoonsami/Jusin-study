#pragma once

#include "Object.h"
class CObjectMgr
{
private:
	CObjectMgr();
	~CObjectMgr();
	
private:
	static CObjectMgr*	m_pInstance;
	list<CObject*>		m_ObjList[OT_END];

public:
	BOOL	Add_Object(OBJECTTYPE eID, CObject* obj);
	int		Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();
	list<CObject*> Get_ObjList(OBJECTTYPE eID);

public:
	static CObjectMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CObjectMgr;
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

};

