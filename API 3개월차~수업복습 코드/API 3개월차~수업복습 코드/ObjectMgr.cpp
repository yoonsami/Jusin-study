#include "pch.h"
#include "ObjectMgr.h"


CObjectMgr* CObjectMgr::m_pInstance = nullptr;

CObjectMgr::CObjectMgr()
{
}

CObjectMgr::~CObjectMgr()
{
	Release();
}

BOOL CObjectMgr::Add_Object(OBJECTTYPE eID, CObject* obj)
{
	if (eID < 0 || !obj || eID >= OT_END)
		return false;
	m_ObjList[eID].push_back(obj);
	return true;
}

int CObjectMgr::Update()
{
	for (int i = 0; i < OT_END; ++i)
	{
		for (auto& i : m_ObjList[i])
		{
			int iResult = i->Update();
		}
	}
	return 0;
}

void CObjectMgr::Late_Update()
{
	for (int i = 0; i < OT_END; ++i)
	{
		for (auto& i : m_ObjList[i])
		{
			i->Late_Update();
		}
	}
}

void CObjectMgr::Render(HDC hDC)
{
	for (int i = 0; i < OT_END; ++i)
	{
		for (auto& i : m_ObjList[i])
		{
			i->Render(hDC);
		}
	}
}

void CObjectMgr::Release()
{
	for (int i = 0; i < OT_END; ++i)
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObject*>);
}

list<CObject*> CObjectMgr::Get_ObjList(OBJECTTYPE eID)
{
	return m_ObjList[eID];
}
