#include "PCH.h"
#include "Player.h"
#include "define.h"
#include "Arrow.h"
#include "Field.h"
#include "Item.h"

Player::Player(int playerType) 
	: Creature(CT_PLAYER), m_jobName(""),m_iPlayerType(playerType), m_baseStat{},
	m_itemInventory{}, m_itemStat{},EquipedItem{}, InventoryOpened(false)
	
{
	m_statInfo._money = 3000;
}

Player::~Player()
{
}

void Player::SetName()
{
	cout << "플레이어의 이름을 입력해주세요" << endl;
	cin >> m_statInfo._name;
	CLEAR_CIN;
}

void Player::PrintJobInfo()
{
	cout << m_jobName << "의 기본스탯 정보"<< endl;
	cout << "체  력 : " << m_baseStat._maxHp << endl;
	cout << "공격력 : " << m_baseStat._att << endl;
	cout << "방어력 : " << m_baseStat._def << endl;

}

void Player::PrintInfo()
{
	PRINT_LINE;
	cout << m_statInfo._name << "의 스탯 정보" << endl;
	cout << "체  력 : " << m_statInfo._hp << " / " << m_statInfo._maxHp <<"( + " << m_itemStat._maxHp << ")" << endl;;
	cout << "공격력 : " << m_statInfo._att << "( + " << m_itemStat._att << ")";
	cout << "\t방어력 : " << m_statInfo._def << "( + " << m_itemStat._def << ")" << endl;
	cout << "직업 : " << m_jobName << "\t 소지금 : " << m_statInfo._money << endl;
}

void Player::Move()
{
	char c = _getch();
	switch (c)
	{
	case RIGHT:
		_posCrd._crdX += 1.f;
		m_iLookingDir = RIGHT;
		break;
	case LEFT:
		_posCrd._crdX += -1.f;
		m_iLookingDir = LEFT;
		break;
	default:
		break;
	}
}

void Player::AddMoney(int _money)
{
	m_statInfo._money += _money;
}

void Player::Resurrect()
{
	m_statInfo._hp = m_statInfo._maxHp;
	m_statInfo._money = static_cast<int>(0.9 * m_statInfo._money);
}



void Player::ShowInventory()
{
	m_itemInventory.OpendInven();

	while (m_itemInventory.IsOpened())
	{
		m_itemInventory.Update();
		m_itemInventory.Render();
	}

	m_itemStat = m_itemInventory.GetEquipedItemStat();
	m_statInfo = m_baseStat + m_itemStat;
}

void Knight::Attack(Creature* _target)
{
	m_target = _target;

	float dist = ( m_target->GetPos() - _posCrd).OfSize();
	if (dist <= 1.f && dist >= -1.f)
		_target->OnAttacked(this);

	m_target = nullptr;
}

void Archer::Attack(Creature* _target)
{
	if(!m_arrow)
	{
		m_arrow = new Arrow(this, _target);
		m_arrow->FireArrow();
	}
}


void Mage::Attack(Creature* _target)
{

}

