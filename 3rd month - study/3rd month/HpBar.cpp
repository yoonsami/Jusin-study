#include "pch.h"
#include "HpBar.h"

HpBar::HpBar(Object* _pOwner) : UI(UT_HPBAR)
{
	m_pOwner = _pOwner;
}

void HpBar::Init()
{
}

int HpBar::Update()
{
	POSINFO& m_pOwnerPos = m_pOwner->Get_Pos();

	m_tPos = { m_pOwnerPos.fX, m_pOwnerPos.fY - m_pOwnerPos.fCY * 0.8f , m_pOwnerPos.fCX * 1.2f, m_pOwnerPos.fCY * 0.2f };
	Update_Rect();
	return 0;
}

void HpBar::Late_Update()
{

}

void HpBar::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	FLOAT a = m_tPos.fCX * (1.f - m_pOwner->Get_Stat().Get_HpRatio());
	HBRUSH hNewBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
	Rectangle(hDC, m_tRect.left,
		m_tRect.top,
		m_tRect.right - static_cast<INT>(a),
		m_tRect.bottom);
	hNewBrush = (HBRUSH)::SelectObject(hDC, hOldBrush);
	::DeleteObject(hNewBrush);

}

void HpBar::Release()
{

}