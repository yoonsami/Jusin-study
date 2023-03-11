#include "pch.h"
#include "Monster.h"
#include "Bullet.h"
#include "HpBar.h"
#include "AbstractFactory.h"

Monster::Monster()
{

}

Monster::~Monster()
{
	Release();
}

void Monster::Init()
{
	m_tPos = { WINCX / 2.f, 200, 60.f, 60.f };
	m_fSpeed = 5.f;
	if (rand() % 2 == 0)
	{
		m_eDir = DIRECTION::DIR_LEFT;
		_Vel.vX = -3.f;
	}
	else
	{
		m_eDir = DIRECTION::DIR_RIGHT;
		_Vel.vX = 3.f;
	}

	m_bInvincible = true;

	m_Ui.push_back(new HpBar(this));
}

int Monster::Update()
{
	if (m_dwTime + 1000 < GetTickCount64())
	{
		m_bInvincible = false;

		m_dwTime = GetTickCount64();
	}
	if (Is_Dead())
		return OBJ_DEAD;

	
	// Get_Acc();

	for (auto& i : m_Ui)
	{
		i->Update();
	}

	__super::Update_Rect();
	return OBJ_NOEVENT;;
}

void Monster::Late_Update()
{
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
	for (auto& i : m_Ui)
	{
		i->Render(hDC);
	}
}

void Monster::Release()
{
	for_each(m_Ui.begin(), m_Ui.end(), Safe_Delete<Object*>);
}

void Monster::CheckCollide()
{
	RECT tmp{};
	BOOL bCollide = FALSE;
	for (auto& i : *m_pBulletList)
	{
		bCollide = Collider::IntersectCirRect(&i->Get_Rect(), &m_tRect);
		if (bCollide)
		{
			dynamic_cast<Bullet*>(i)->Set_Dead();
			m_tStat.fHp -= 10;
			if (m_tStat.fHp < 0) m_tStat.fHp = 0;
			return;
		}
	}
}
