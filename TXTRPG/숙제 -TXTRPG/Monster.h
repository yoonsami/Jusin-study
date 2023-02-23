#pragma once
#include "Creature.h"
#include "define.h"
class Monster :  public Creature
{
public:
	Monster(int monsterType);
	virtual ~Monster();
public:
	virtual void PrintInfo();
	virtual void Attack(Creature* _target);

private:
	int _monsterType;
};

class Slime : public Monster
{
public:
	Slime() : Monster(MT_SLIME)
	{
		strcpy_s(m_statInfo._name, "ΩΩ∂Û¿”");
		m_statInfo._maxHp = 50;
		m_statInfo._hp = 50;
		m_statInfo._att = 5;
		m_statInfo._def = 1;
		m_statInfo._money = 50;
	}
};

class Skeleton : public Monster
{
public:
	Skeleton() : Monster(MT_SKELETON)
	{
		strcpy_s(m_statInfo._name, "Ω∫ƒÃ∑π≈Ê");
		m_statInfo._maxHp = 70;
		m_statInfo._hp = 70;
		m_statInfo._att = 6;
		m_statInfo._def = 2;
		m_statInfo._money = 100;
	}
};

class Orc : public Monster
{
public:
	Orc() : Monster(MT_SKELETON)
	{
		strcpy_s(m_statInfo._name, "ø¿≈©");
		m_statInfo._maxHp = 100;
		m_statInfo._hp = 100;
		m_statInfo._att = 8;
		m_statInfo._def = 3;
		m_statInfo._money = 200;
	}
};