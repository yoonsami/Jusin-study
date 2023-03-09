#include "pch.h"
#include "Monster.h"

Monster::Monster()
{

}

Monster::~Monster()
{
	Release();
}

void Monster::Init()
{
	m_tInfo = { WINCX / 2.f, 200, 60.f, 60.f };
	m_fSpeed = 5.f;
	if (rand() % 2 == 0)
		m_eDir = DIRECTION::DIR_LEFT;
	else
		m_eDir = DIRECTION::DIR_RIGHT;
}

void Monster::Update()
{
	Move();

	__super::Update_Rect();
}

void Monster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void Monster::Release()
{
}

void Monster::Move()
{
	if (m_tInfo.fX - (m_tInfo.fCX / 2) < PLAYZONELEFT)
		m_eDir = DIRECTION::DIR_RIGHT;

	if (m_tInfo.fX + (m_tInfo.fCX / 2) > PLAYZONERIGHT)
		m_eDir = DIRECTION::DIR_LEFT;

	if (m_eDir == DIRECTION::DIR_LEFT)
		m_tInfo.fX -= m_fSpeed;

	if (m_eDir == DIRECTION::DIR_RIGHT)
		m_tInfo.fX += m_fSpeed;

	
}
