#include "pch.h"
#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

void Bullet::Init()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
	m_fSpeed = 5.f;
}

int Bullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	switch (m_eDir)
	{
	case DIRECTION::DIR_LEFT:
		m_tInfo.fX -= m_fSpeed;
		break;
	case DIRECTION::DIR_UP:
		m_tInfo.fY -= m_fSpeed;
		break;
	case DIRECTION::DIR_RIGHT:
		m_tInfo.fX += m_fSpeed;
		break;
	case DIRECTION::DIR_DOWN:
		m_tInfo.fY += m_fSpeed;
		break;
	case DIRECTION::DIR_LU:
		m_tInfo.fX -= m_fSpeed;
		m_tInfo.fY -= m_fSpeed;
		break;
	case DIRECTION::DIR_RU:
		m_tInfo.fX += m_fSpeed;
		m_tInfo.fY -= m_fSpeed;
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
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void Bullet::Release()
{

}

