#include "pch.h"
#include "Hammer.h"
#include "LineMgr.h"
#include "CollisionMgr.h"

void CHammer::Init()
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
	m_eFigure = FIGURETYPE::FT_RECT;
}

int CHammer::Update()
{

	Check_Line();
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CHammer::Late_Update()
{
	
}

void CHammer::Render(HDC hDC)
{
	Draw_Figure(hDC);
}

void CHammer::Release()
{
}

void CHammer::Check_Line()
{
	int iCount = 0;
	for (auto& i : CLineMgr::Get_LineList())
	{
		if (CCollisionMgr::Is_UnderLine(POINTF(m_tInfo.fX,m_tInfo.fY),i))
		{
			iCount++;
			m_pNowLine = i;
			m_bHanged = true;
			m_tInfo -=  i->Get_NormalVector() * i->Get_Distance_With_Dot(m_tInfo.fX, m_tInfo.fY);
			GetCursorPos(&m_tHangingMouse);
			ScreenToClient(g_hWnd, &m_tHangingMouse);
		}
	}

	if (iCount == 0)
		m_pNowLine = nullptr;

	if (m_pNowLine == nullptr)
		m_bHanged = false;
}
