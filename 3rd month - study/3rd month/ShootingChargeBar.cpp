#include "pch.h"
#include "ShootingChargeBar.h"
#include "Player.h"

ShootingChargeBar::ShootingChargeBar(Object* Owner) :UI(UT_SHOOTINGCHABAR, Owner)
{
	
}

void ShootingChargeBar::Init()
{
}

int ShootingChargeBar::Update()
{
	POSINFO& m_pOwnerPos = m_pOwner->Get_Pos();

	m_tPos = { m_pOwnerPos.fX, m_pOwnerPos.fY + m_pOwnerPos.fCY * 0.8f , m_pOwnerPos.fCX * 1.2f, m_pOwnerPos.fCY * 0.1f };
	Update_Rect();
	return 0;
}

void ShootingChargeBar::Late_Update()
{
}

void ShootingChargeBar::Render(HDC hDC)
{
	if (dynamic_cast<Player*>(m_pOwner)->IsShootCharging())
	{
		HBRUSH hNewBrush;
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		if(dynamic_cast<Player*>(m_pOwner)->IsFullCharging() && m_iFlagCount <4)
		{
			hNewBrush = CreateSolidBrush(RGB(0, 255, 255));
			m_iFlagCount++;
		}

		else
		{
			m_iFlagCount++;
			hNewBrush = CreateSolidBrush(RGB(255, 255, 0));
			if (m_iFlagCount == 8) m_iFlagCount = 0;
		}
			
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
		Rectangle(hDC, m_tRect.left,
			m_tRect.top,
			m_tRect.left + static_cast<INT>(m_tPos.fCX * dynamic_cast<Player*>(m_pOwner)->Get_ShootChargeRatio()),
			m_tRect.bottom);
		hNewBrush = (HBRUSH)::SelectObject(hDC, hOldBrush);
		::DeleteObject(hNewBrush);
	}
}

void ShootingChargeBar::Release()
{
}
