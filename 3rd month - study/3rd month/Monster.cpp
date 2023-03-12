#include "pch.h"
#include "Monster.h"
#include "Bullet.h"
#include "HpBar.h"
#include "AbstractFactory.h"

Monster::Monster(INT _MonsterType) :Creature(CT_MONSTER),m_iMonsterType(_MonsterType)
{

}

Monster::Monster() : Creature(CT_MONSTER), m_iMonsterType(0)
{

}

Monster::Monster(const Monster& monster) :Creature(monster)
{
	m_pBulletList = nullptr;
	m_InvincibleTimer = GetTickCount64();
	m_iMonsterType = monster.m_iMonsterType;
}

Monster::~Monster()
{
	Release();
}

void Monster::Init()
{
	m_tPos = { WINCX / 2.f, 200, 60.f, 60.f };
	m_fSpeed = 5.f;
	if(m_eDir == DIRECTION::DIR_END)
	{
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
	}
	else if (m_eDir == DIRECTION::DIR_LEFT)  _Vel.vX = -3.f;
	else if (m_eDir == DIRECTION::DIR_RIGHT) _Vel.vX = 3.f;

	m_eFigure = FIGURETYPE::FT_CIRCLE;
	m_bInvincible = true;
	m_tStat.fAtt = 15.f;
	m_Ui.push_back(new HpBar(this));
}

int Monster::Update()
{
	if (m_InvincibleTimer + 1000 < GetTickCount64())
	{
		m_bInvincible = false;

		m_InvincibleTimer = GetTickCount64();
	}

	if (Is_Dead())
		return OBJ_DEAD;

	
	Get_Acc();

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
		Draw_Figure(hDC);
	else
	{
		HPEN hpen;
		HPEN hpenOld;
		hpen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		hpenOld = (HPEN)::SelectObject(hDC, (HGDIOBJ)hpen);
		Draw_Figure(hDC);
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
	BOOL bCollide = FALSE;
	for (auto& i : *m_pBulletList)
	{
		bCollide = Collider::IntersectWith(i->Get_Rect(), m_tRect, i->Get_Figure(), m_eFigure);
		if (bCollide)
		{
			OnAttacked(*i);
			i->Set_Dead();
			return;
		}
	}
}
