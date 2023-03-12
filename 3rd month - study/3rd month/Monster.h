#pragma once
#include "Creature.h"
class Monster : public Creature
{
public:
	Monster();
	Monster(INT _MonsterType);
	Monster(const Monster& monster);
	virtual ~Monster();

public:
	virtual void		Init() override;
	virtual int			Update() override;
	virtual void		Late_Update() override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release() override;

private:
	void CheckCollide();
public:
	void Set_Bullet(list<Object*>* _bulletList) { m_pBulletList = _bulletList; }

private:
	list<Object*>*	m_pBulletList = nullptr;
	DWORD64			m_InvincibleTimer = GetTickCount64();
	INT				m_iMonsterType;
};

