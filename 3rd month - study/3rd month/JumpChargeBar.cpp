#include "pch.h"
#include "JumpChargeBar.h"
#include "Player.h"

JumpChargeBar::JumpChargeBar(Object* Owner) :UI(UT_HPBAR, Owner)
{
    
}

void JumpChargeBar::Init()
{
}

int JumpChargeBar::Update()
{
	POSINFO& m_pOwnerPos = m_pOwner->Get_Pos();

	m_tPos = { m_pOwnerPos.fX, m_pOwnerPos.fY + m_pOwnerPos.fCY * 0.7f , m_pOwnerPos.fCX * 1.2f, m_pOwnerPos.fCY * 0.1f };
	Update_Rect();
	return 0;
}

void JumpChargeBar::Late_Update()
{
}

void JumpChargeBar::Render(HDC hDC)
{
	if (dynamic_cast<Player*>(m_pOwner)->IsJumpCharging())
	{
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		HBRUSH hNewBrush = CreateSolidBrush(RGB(0, 255, 255));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
		Rectangle(hDC, m_tRect.left,
			m_tRect.top,
			m_tRect.left + static_cast<INT>(m_tPos.fCX * dynamic_cast<Player*>(m_pOwner)->Get_JumpChargeRatio()),
			m_tRect.bottom);
		hNewBrush = (HBRUSH)::SelectObject(hDC, hOldBrush);
		::DeleteObject(hNewBrush);
	}
}

void JumpChargeBar::Release()
{
}