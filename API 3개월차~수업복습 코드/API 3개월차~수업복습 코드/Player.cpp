#include "pch.h"
#include "Player.h"
#include "KeyInputMgr.h"
#include "CollisionMgr.h"
#include "LineMgr.h"
#include "AbstractFactory.h"
#include "Hammer.h"
#include "ObjectMgr.h"

void CPlayer::Init()
{
    m_tInfo = { WINCX * 0.5f , 0.f, 20.f,20.f };
	m_pHammer = new CHammer;
	m_pHammer->Init();
	CObjectMgr::Get_Instance()->Add_Object(OT_HAMMER, m_pHammer);
}

int CPlayer::Update()
{
	// Key_Input();
	
	Set_Player_Aim();

	MovePlayer();

	Accelarate();
    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	int iCount = 0;
	for (auto& i : CLineMgr::Get_LineList())
	{		
		if (CCollisionMgr::Is_UnderLine(POINTF(m_tInfo.fX,m_tInfo.fY+m_tInfo.fCY * 0.7f), i))
		{
			if (m_pNowLine == nullptr)
			{
				if ((fabsf(i->Get_YPos(m_tInfo.fX) - m_tInfo.fY) <= m_tInfo.fCY * 0.7f) && m_tVelocity.vY >0)
				{
					iCount++;
					m_pNowLine = i;
					m_bOnLine = true; 
					m_tVelocity = {};
				}
			}
			else if ((fabsf(i->Get_YPos(m_tInfo.fX) - m_tInfo.fY) <= m_tInfo.fCY * 0.7f))
			{
				iCount++;
				if (m_pNowLine != i)
				{
					m_tVelocity = { -m_tVelocity.Get_Size() * cosf(i->Get_Theta()), -m_tVelocity.Get_Size() * sinf(i->Get_Theta()) };
				}
					m_pNowLine = i;
					m_bOnLine = true;
			}	
		}
	}
	if (iCount == 0)
		m_pNowLine = nullptr;

	if (m_pNowLine == nullptr)
		m_bOnLine = false;
}


void CPlayer::Render(HDC hDC)
{
    Draw_Figure(hDC);

	MoveToEx(hDC, m_tInfo.fX + m_tAim.vX, m_tInfo.fY + m_tAim.vY, nullptr);
	LineTo(hDC, m_tInfo.fX + m_tAim.vX -100.f * m_tAim.Get_UnitVec().vX, m_tInfo.fY + m_tAim.vY - 100.f * m_tAim.Get_UnitVec().vY);

	TCHAR BUF[100];
	swprintf_s(BUF, L"m_bOnLine %d", m_bOnLine);
	TextOut(hDC, 25, 25, BUF, lstrlen(BUF));
	swprintf_s(BUF, L"NowLine %p", (m_pNowLine));
	TextOut(hDC, 25, 50, BUF, lstrlen(BUF));
	swprintf_s(BUF, L"m_bOnGround %d", (m_bOnGround));
	TextOut(hDC, 25, 75, BUF, lstrlen(BUF));
	swprintf_s(BUF, L"Vel X :  %f \tVel Y : %f", m_tVelocity.vX,m_tVelocity.vY);
	TextOut(hDC, 25, 90, BUF, lstrlen(BUF));
}

void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{
	// D키
	{
		if ((GetAsyncKeyState('D') == (SHORT)0x8000) && !CKeyInputMgr::m_bLeftPressed)
		{
			if (!CKeyInputMgr::m_bRightPressed)
			{
				//m_tVelocity.vX += m_fSpeed;
				CKeyInputMgr::m_bRightPressed = true;
			}
			/*else if (CKeyInputMgr::m_bRightPressed && m_tVelocity.vX < 0)
			{
				m_tVelocity.vX += m_fSpeed;
				CKeyInputMgr::m_bRightPressed = false;
			}*/
		}
		if ((GetAsyncKeyState('D') == (SHORT)0x0000) && CKeyInputMgr::m_bRightPressed)
		{
			/*if (m_tInfo.fX == PLAYZONERIGHT - (m_tInfo.fCX * 0.5f));
			else
			{
				if (m_tVelocity.vX > 0) m_tVelocity.vX -= m_fSpeed;
				else if (m_tVelocity.vX < 0) m_tVelocity.vX += m_fSpeed;
			}*/
			CKeyInputMgr::m_bRightPressed = false;
		}
	}


	// A키
	{
		if ((GetAsyncKeyState('A') == (SHORT)0x8000) && !CKeyInputMgr::m_bRightPressed)
		{
			if (!CKeyInputMgr::m_bLeftPressed)
			{
				//m_tVelocity.vX -= m_fSpeed;
				CKeyInputMgr::m_bLeftPressed = true;
			}
			else if (CKeyInputMgr::m_bLeftPressed && m_tVelocity.vX > 0)
			{
				/*m_tVelocity.vX -= m_fSpeed;
				CKeyInputMgr::m_bLeftPressed = false;*/
			}
		}
		if ((GetAsyncKeyState('A') == (SHORT)0x0000) && CKeyInputMgr::m_bLeftPressed)
		{
		/*	if (m_tInfo.fX == 0 + (m_tInfo.fCX * 0.5f));
			else
			{
				if (m_tVelocity.vX > 0) m_tVelocity.vX -= m_fSpeed;
				else if (m_tVelocity.vX < 0) m_tVelocity.vX += m_fSpeed;
			}*/
			CKeyInputMgr::m_bLeftPressed = false;
		}
	}
	if ((GetAsyncKeyState('S') == (SHORT)0x8000) && !CKeyInputMgr::m_bUpPressed)
	{
		if (!CKeyInputMgr::m_bDownPressed)
		{
			if (m_pNowLine)
			{
				m_pNowLine->Set_PosY(10.f);
			}
			CKeyInputMgr::m_bDownPressed = true;
		}
	}
	if ((GetAsyncKeyState('S') == (SHORT)0x0000) && CKeyInputMgr::m_bDownPressed)
	{
		/*if (m_tInfo.fX == PLAYZONERIGHT - (m_tInfo.fCX * 0.5f));
		else
		{
			if (m_tVelocity.vX > 0) m_tVelocity.vX -= m_fSpeed;
			else if (m_tVelocity.vX < 0) m_tVelocity.vX += m_fSpeed;
		}*/
		CKeyInputMgr::m_bDownPressed = false;
	}

	if ((GetAsyncKeyState('W') == (SHORT)0x8000) && !CKeyInputMgr::m_bDownPressed)
	{
		if (!CKeyInputMgr::m_bUpPressed)
		{
			if(m_pNowLine)
				m_pNowLine->Set_PosY(-10.f);
			CKeyInputMgr::m_bUpPressed = true;
		}
		/*else if (CKeyInputMgr::m_bRightPressed && m_tVelocity.vX < 0)
		{
			m_tVelocity.vX += m_fSpeed;
			CKeyInputMgr::m_bRightPressed = false;
		}*/
	}
	if ((GetAsyncKeyState('W') == (SHORT)0x0000) && CKeyInputMgr::m_bUpPressed)
	{
		/*if (m_tInfo.fX == PLAYZONERIGHT - (m_tInfo.fCX * 0.5f));
		else
		{
			if (m_tVelocity.vX > 0) m_tVelocity.vX -= m_fSpeed;
			else if (m_tVelocity.vX < 0) m_tVelocity.vX += m_fSpeed;
		}*/
		CKeyInputMgr::m_bUpPressed = false;
	}
	// 스페이스바
	{
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000) &&( m_bOnGround || m_bOnLine))
		{ 
			if (m_tVelocity.vY < 0);
			else m_tVelocity.vY -= 15.f;
			CKeyInputMgr::m_bSpacePressed = true;
		}
		if ((GetAsyncKeyState(VK_SPACE) == (SHORT)0x0000) && CKeyInputMgr::m_bSpacePressed)
		{
			CKeyInputMgr::m_bSpacePressed = false;
		}
	}

}

void CPlayer::Set_Player_Aim()
{
	POINT ptMouse{};
	if (!static_cast<CHammer*>(m_pHammer)->Is_Hanged())
	{
		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);

		Vec2 tmp = { ptMouse.x - m_tInfo.fX,ptMouse.y - m_tInfo.fY };


		m_tAim = tmp.Get_UnitVec() * clamp(tmp.Get_Size(), 0.f, 100.f);
		static_cast<CHammer*>(m_pHammer)->Set_Aim(tmp.Get_UnitVec());
		static_cast<CHammer*>(m_pHammer)->Set_Pos(m_tInfo.fX + m_tAim.vX, m_tInfo.fY + m_tAim.vY);
	}
	else
	{
		m_tAim = Vec2{ m_pHammer->Get_Info().fX - m_tInfo.fX,m_pHammer->Get_Info().fY - m_tInfo.fY }.Get_UnitVec() *  100.f;
		m_tInfo.fX = m_pHammer->Get_Info().fX - m_tAim.vX;
		m_tInfo.fY = m_pHammer->Get_Info().fY - m_tAim.vY;
	}
}

void CPlayer::MovePlayer()
{
	if (static_cast<CHammer*>(m_pHammer)->Is_Hanged())
	{
		m_tHangingMouse = static_cast<CHammer*>(m_pHammer)->Get_HangingMousePos();
		POINT ptMouse{};

		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);

		Vec2 tmp = { ptMouse.x - m_pHammer->Get_Info().fX,ptMouse.y - m_pHammer->Get_Info().fY };
		
	}
}
