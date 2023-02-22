#include "PCH.h"
#include "Creature.h"
#include "Game.h"

Creature::Creature(int creatureType) 
	: Object(OT_CREATURE), _posCrd{}, _Vel{}, m_iCreatureType(creatureType), _Acc{}, m_target(nullptr), m_iLookingDir(0)
{

}

Creature::~Creature()
{

}

void Creature::GetAcc()
{
	_Acc._crdY = Game::WorldGravity;
	_Acc._crdX = 0;

	// ���󿡼� ���ۿ� ���
	if (OnGround() && _Vel._crdY == 0) _Acc._crdY -= Game::WorldGravity;
	// ���� �޷��� �� ��� ���
	
	// ���ӵ��� ���� �ӵ�, ��ǥ ���	
		//�ӵ� ��ȭ�� ��� �� +=
	_Vel += _Acc * Game::WorldSpeed;
	//��ǥ ��ȭ�� ��� �� +=
	_posCrd += (_Vel + (_Vel - _Acc * Game::WorldSpeed)) * 0.5f * Game::WorldSpeed;


	// ��ǥ�� �� ���� �Ѿ �� �ӵ� ����
	if (_posCrd._crdY > MAP_HEIGHT - 1)
	{
		float vel_Y = static_cast<float> (sqrt(pow(_Vel._crdY, 2) - 2.f * Game::WorldGravity * (_posCrd._crdY - MAP_HEIGHT + 1)));
		if (_Vel._crdY < 0)
			_Vel._crdY = -vel_Y;
		else if (_Vel._crdY > 0)
			_Vel._crdY = vel_Y;
	}
	else if (_posCrd._crdY < 0)
	{
		float vel_Y = static_cast<float> (sqrt(pow(_Vel._crdY, 2) - 2.f * Game::WorldGravity * (0 - _posCrd._crdY)));
		if (_Vel._crdY < 0)
			_Vel._crdY = -vel_Y;
		else if (_Vel._crdY > 0)
			_Vel._crdY = vel_Y;
	}

	// ��ǥ�� �� ������ ������ �ʵ��� ����
		//x��
	CorrectPos();
	// ���� ���� ��� �浹 ����(�ݹ߰�� ����)
	if (OnGround() && _Vel._crdY >0)
		_Vel = _Vel * -1.f * Game::COR;
}

bool Creature::OnGround()
{
	if (_posCrd._crdY == MAP_HEIGHT - 1) return true;
	else return false;
}

void Creature::CorrectPos()
{
	if (_posCrd._crdX <= 0)
	{
		_posCrd._crdX = 0;
	}
	else if (_posCrd._crdX >= MAP_WIDTH - 1)
	{
		_posCrd._crdX = MAP_WIDTH - 1;
	}
	if (_posCrd._crdY <= 0)
	{
		_posCrd._crdY = 0;
	}
	else if (_posCrd._crdY >= MAP_HEIGHT - 1)
	{
		_posCrd._crdY = MAP_HEIGHT - 1;
	}
}

void Creature::OnAttacked(Creature* Attacker)
{
	int damage = Attacker->m_statInfo._att - m_statInfo._def;
	if (damage <= 0) damage = 1;

	m_statInfo._hp -= damage;
	if (m_statInfo._hp <= 0)
		m_statInfo._hp = 0;
}
