#include "PCH.h"
#include "Monster.h"

Monster::Monster(int monsterType) :Creature(CT_MONSTER), _monsterType(monsterType)
{

}

Monster::~Monster()
{

}

void Monster::PrintInfo()
{
	PRINT_LINE;
	cout << m_statInfo._name << "의 스탯 정보" << endl;
	cout << "체  력 : " << m_statInfo._hp;
	cout << "\t공격력 : " << m_statInfo._att;
	cout << "\t방어력 : " << m_statInfo._def << endl;
}

void Monster::Attack(Creature* _target)
{

}
