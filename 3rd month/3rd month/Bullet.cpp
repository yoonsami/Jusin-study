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

void Bullet::Update()
{
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
	default:
		break;
	}

	__super::Update_Rect();

}

void Bullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void Bullet::Release()
{

}

void Bullet::Set_PosDir(float _fX, float _fY, DIRECTION _dir)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_eDir = _dir;
}
