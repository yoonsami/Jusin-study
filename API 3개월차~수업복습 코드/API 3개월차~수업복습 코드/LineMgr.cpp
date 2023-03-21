#include "pch.h"
#include "LineMgr.h"
#include "ObjectMgr.h"
#include "CollisionMgr.h"
#include "KeyInputMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Init()
{
	POINTF		tPoint[4]{

		{ 100.f, 450.f},
		{ 300.f, 450.f },
		{ 500.f, 250.f },
		{ 700.f, 250.f }
	};

	m_LineList.push_back(new CLine(tPoint[0], tPoint[1]));
	m_LineList.push_back(new CLine(tPoint[1], tPoint[2]));
	m_LineList.push_back(new CLine(tPoint[2], tPoint[3]));
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& i : m_LineList)
	{
		i->Render(hDC);
	}
}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	m_LineList.clear();
}

void CLineMgr::Update()
{	
	
}
