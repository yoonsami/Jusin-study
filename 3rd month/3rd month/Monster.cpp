#include "pch.h"
#include "Monster.h"
#include "Bullet.h"

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
	m_bInvincible = true;
}

int Monster::Update()
{
	if (m_dwTime + 1000 < GetTickCount64())
	{
		m_bInvincible = false;

		m_dwTime = GetTickCount64();
	}
	if (m_bDead)
		return OBJ_DEAD;

	Move();
	__super::Update_Rect();
	return OBJ_NOEVENT;;
}

void Monster::Late_Update()
{
	Turn();
	if(m_bInvincible == false)
		CheckCollide();
}

void Monster::Render(HDC hDC)
{
	if(m_bInvincible == false)
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	else
	{
		HPEN hpen;
		HPEN hpenOld;
		hpen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		hpenOld = (HPEN)::SelectObject(hDC, (HGDIOBJ)hpen);
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		hpen = (HPEN)::SelectObject(hDC, hpenOld);
		::DeleteObject(hpen);

	}
}

void Monster::Release()
{
}

void Monster::Move()
{
	if (m_eDir == DIRECTION::DIR_LEFT)
		m_tInfo.fX -= m_fSpeed;
	else if (m_eDir == DIRECTION::DIR_RIGHT)
		m_tInfo.fX += m_fSpeed;
}

void Monster::Turn()
{
	if (m_tInfo.fX - (m_tInfo.fCX / 2) < PLAYZONELEFT)
		m_eDir = DIRECTION::DIR_RIGHT;
	else if (m_tInfo.fX + (m_tInfo.fCX / 2) > PLAYZONERIGHT)
		m_eDir = DIRECTION::DIR_LEFT;
}

void Monster::CheckCollide()
{
	RECT tmp{};
	BOOL bCollide = FALSE;
	for (auto& i : *m_pBulletList)
	{
		bCollide = IntersectRect(&tmp, &i->Get_Rect(), &m_tRect);
		if (bCollide)
		{
			dynamic_cast<Bullet*>(i)->Set_Dead();
			m_bDead = true;
			return;
		}
	}
}
