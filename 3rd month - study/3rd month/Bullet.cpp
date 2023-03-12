#include "pch.h"
#include "Bullet.h"

Bullet::Bullet() :Creature(CT_BULLET)
{

}

Bullet::Bullet(const Bullet& bullet) :Creature(bullet)
{
	m_bFullCharged = bullet.m_bFullCharged;
}

Bullet::~Bullet()
{

}

void Bullet::Init()
{
	m_tPos.fCX = MINFIREPOW;
	m_tPos.fCY = MINFIREPOW;
	m_fSpeed = 15.f;

	m_eFigure = FIGURETYPE::FT_CIRCLE;
}

int Bullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	switch (m_eDir)
	{
	case DIRECTION::DIR_LEFT:
		m_tPos.fX -= m_fSpeed;
		break;
	case DIRECTION::DIR_UP:
		m_tPos.fY -= m_fSpeed;
		break;
	case DIRECTION::DIR_RIGHT:
		m_tPos.fX += m_fSpeed;
		break;
	case DIRECTION::DIR_DOWN:
		m_tPos.fY += m_fSpeed;
		break;
	case DIRECTION::DIR_LU:
		m_tPos.fX -= m_fSpeed;
		m_tPos.fY -= m_fSpeed;
		break;
	case DIRECTION::DIR_RU:
		m_tPos.fX += m_fSpeed;
		m_tPos.fY -= m_fSpeed;
		break;
	case DIRECTION::DIR_END:
		break;
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void Bullet::Late_Update()
{
	if (m_tRect.left	<= PLAYZONELEFT		|| m_tRect.top		<= PLAYZONETOP ||
		m_tRect.right	>= PLAYZONERIGHT	|| m_tRect.bottom	>= PLAYZONEBOTTOM)
		m_bDead = true;
}

void Bullet::Render(HDC hDC)
{
	
	if (m_bFullCharged)
	{
		HBRUSH hNewBrush = CreateSolidBrush(RGB(0, 255, 255));

		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
		Draw_Figure(hDC);

		hNewBrush = (HBRUSH)::SelectObject(hDC, hOldBrush);
		::DeleteObject(hNewBrush);
	}
	else Draw_Figure(hDC);
	
}

void Bullet::Release()
{

}

