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
	cout << m_statInfo._name << "�� ���� ����" << endl;
	cout << "ü  �� : " << m_statInfo._hp;
	cout << "\t���ݷ� : " << m_statInfo._att;
	cout << "\t���� : " << m_statInfo._def << endl;
}

void Monster::Attack(Creature* _target)
{

}
