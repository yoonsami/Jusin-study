#include "pch.h"
#include "Object.h"
#include "KeyInputMgr.h"
#include "Line.h"
#include "CollisionMgr.h"


CObject::CObject()
{
}

CObject::~CObject()
{
}

void CObject::Draw_Figure(HDC hDC)
{
	switch (m_eFigure)
	{
	case FIGURETYPE::FT_RECT:
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		break;
	case FIGURETYPE::FT_CIRCLE:
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		break;
	}
}

void CObject::Accelarate()
{
	m_tAcceleration = { 0.f, GRAVITY };
	// 수직 항력
	if (Is_OnGround())
	{
		if (m_bOnGround)
			m_tForwarding_Dir = { 1.f,0.f };
		else
		{
			if (m_pNowLine)
				m_tForwarding_Dir = { cosf(m_pNowLine->Get_Theta()),sinf(m_pNowLine->Get_Theta()) };
		}

		//Vec2 NormalAcceleration = { GRAVITY * m_tForwarding_Dir.Get_UnitVec().vX * m_tForwarding_Dir.Get_UnitVec().vY, -GRAVITY * m_tForwarding_Dir.Get_UnitVec().vX * m_tForwarding_Dir.Get_UnitVec().vX };
		Vec2 NormalAcceleration = { 0.f, - GRAVITY };
		m_tAcceleration += NormalAcceleration;

		// 마찰력
		//Vec2 FrictionAcceleration;
		//if (Is_OnGround())
		//{
		//	if(fabsf(GRAVITY * m_tForwarding_Dir.vY) > fabsf(tanf(PI / 3.f) * GRAVITY * m_tForwarding_Dir.vX))
		//	{
		//		// 외력이 정지마찰력 이상일 때,
		//		FrictionAcceleration = { GRAVITY * m_tForwarding_Dir.Get_UnitVec().vX * m_tForwarding_Dir.Get_UnitVec().vX, GRAVITY * m_tForwarding_Dir.Get_UnitVec().vX * m_tForwarding_Dir.Get_UnitVec().vY };
		//		m_tAcceleration += FrictionAcceleration * 1.f;
		//		m_tVelocity += m_tAcceleration;
		//		m_bSliding = true;
		//	}
		//	else
		//	{
		//		if (fabsf(m_tVelocity.Get_Theta()- m_tForwarding_Dir.Get_Theta()) <= 0.001f && m_tVelocity.Get_Size() != 0.f)
		//		{
		//			FrictionAcceleration = { -GRAVITY * m_tForwarding_Dir.Get_UnitVec().vX * m_tForwarding_Dir.Get_UnitVec().vX, GRAVITY * m_tForwarding_Dir.Get_UnitVec().vX * m_tForwarding_Dir.Get_UnitVec().vY };
		//			m_tAcceleration += FrictionAcceleration * 1.5f;
		//			m_tVelocity += m_tAcceleration;
		//			m_bSliding = true;
		//			if ((fabsf(m_tVelocity.Get_Theta() - m_tForwarding_Dir.Get_Theta() <=PI + 0.001f)))
		//			{
		//				m_tVelocity = {};
		//				m_bSliding = false;
		//			}
		//		}
		//		else if ((m_tForwarding_Dir.vX * m_tVelocity.vX < 0 ) && m_tVelocity.Get_Size() != 0.f)
		//		{
		//			FrictionAcceleration = { GRAVITY * m_tForwarding_Dir.Get_UnitVec().vX * m_tForwarding_Dir.Get_UnitVec().vX, GRAVITY * m_tForwarding_Dir.Get_UnitVec().vX * m_tForwarding_Dir.Get_UnitVec().vY };
		//			m_tAcceleration += FrictionAcceleration * 1.5f;
		//			m_tVelocity += m_tAcceleration;
		//			m_bSliding = true;
		//			if (fabsf(m_tVelocity.Get_Theta() - m_tForwarding_Dir.Get_Theta()) <= 0.001f)
		//			{
		//				m_tVelocity = {};
		//				m_bSliding = false;
		//			}
		//		}
		//		else if (m_tForwarding_Dir.Get_Theta() == 0.f && m_tVelocity.Get_Size() != 0.f)
		//		{
		//			if (m_tVelocity.vX < 0)
		//			{
		//				m_tAcceleration += Vec2{ GRAVITY, 0.f } *1.5f;
		//				m_tVelocity += m_tAcceleration;
		//				m_bSliding = true;
		//				if (m_tVelocity.vX > 0) 
		//				{
		//					m_tVelocity = {};
		//					m_bSliding = false;
		//				}
		//			}
		//			else if (m_tVelocity.vX > 0)
		//			{
		//				m_tAcceleration += Vec2{ -GRAVITY, 0.f } *1.5f;
		//				m_tVelocity += m_tAcceleration;
		//				m_bSliding = true;
		//				if (m_tVelocity.vX < 0)
		//				{
		//					m_tVelocity = {};
		//					m_bSliding = false;
		//				}
		//			}
		//		}
		//	}
		//}

	}
		m_tVelocity += m_tAcceleration;

	if(Is_OnGround())
		m_tInfo += m_tVelocity + m_tForwarding_Dir * CKeyInputMgr::Get_KeyInputVec().vX * 5.f;
	else
		m_tInfo += m_tVelocity  +Vec2{ 1.f, 0.f } * CKeyInputMgr::Get_KeyInputVec().vX * 5.f;
		
	if (m_tInfo.fY + m_tInfo.fCY * 0.5f > WINCY)
	{
		// y방향 좌표, 속도 보정
		m_tVelocity.vY -= m_tAcceleration.vY;
		if (Is_OnGround())
			m_tInfo.fY -= m_tVelocity.vY + m_tForwarding_Dir.vY * CKeyInputMgr::Get_KeyInputVec().vX * 5.f;
		else
			m_tInfo.fY -= m_tVelocity.vY;
	

		FLOAT Ratio = Vec2::quad_eqn(m_tAcceleration.vY, m_tVelocity.vY, m_tInfo.fY - WINCY + m_tInfo.fCY * 0.5f);

		m_tVelocity.vY += m_tAcceleration.vY * Ratio;
		m_tInfo.fY = WINCY - m_tInfo.fCY * 0.5f;

		m_tVelocity = m_tVelocity * 0.f ;

		m_tVelocity.vY -= m_tAcceleration.vY * (1 - Ratio);
		if (Is_OnGround())
			m_tInfo.fY += (m_tVelocity.vY + m_tForwarding_Dir.vY * CKeyInputMgr::Get_KeyInputVec().vX * 5.f) *(1 - Ratio);
		else
			m_tInfo.fY += m_tVelocity.vY * (1 - Ratio);
	}
	else if (m_tInfo.fY - m_tInfo.fCY * 0.5f < 0)
	{
		/*m_tInfo.fY = 0 + m_tInfo.fCY * 0.5f;
		m_tVelocity.vY *= -0.f;*/
	}

	if(m_pNowLine)
	{
		if (CCollisionMgr::Is_UnderLine(POINTF(m_tInfo.fX, m_tInfo.fY+ m_tInfo.fCY * 0.5f), m_pNowLine))
		{
			m_tInfo.fY = m_pNowLine->Get_YPos(m_tInfo.fX) - m_tInfo.fCY*0.5f;
			m_tVelocity = m_tVelocity * 0.f;
		}
	}


	// 오른쪽 넘어갔을 때
	if (m_tInfo.fX + m_tInfo.fCX * 0.5f > WINCX)
	{
		m_tInfo.fX = WINCX - m_tInfo.fCX * 0.5f;
		m_tVelocity.vX *= -0.f;
	}

	// 왼쪽 넘어갔을 때
	if (m_tInfo.fX - m_tInfo.fCX * 0.5f < 0)
	{
		m_tInfo.fX = 0 + m_tInfo.fCX * 0.5f;
		m_tVelocity.vX *= -0.f;
	}

	if (m_tVelocity.vY == 0 && m_tInfo.fY == WINCY - (m_tInfo.fCY * 0.5f))
		m_bOnGround = true;
	else	m_bOnGround = false;

	if(!m_pNowLine)
	{
			m_bOnLine = false;
	}
}

void CObject::Update_Rect()
{
	m_tRect.left = static_cast<LONG>(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = static_cast<LONG>(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = static_cast<LONG>(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = static_cast<LONG>(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}
