#pragma once
#include "Creature.h"
#include "Inventory.h"


class Inventory;
class Player : public Creature
{
public:
	Player(int playerType);
	~Player();

public:
	virtual void Attack(Creature* m_target) = 0;
	virtual void PrintInfo();
	void SetName();
	void PrintJobInfo();
	void Move();
	void Resurrect();
	void AddMoney(int _money);
	bool AddItemToInven(Item* _newitem);
	void ShowInventory();
	void Jump() { _Vel._crdY -= JUMP_POWER; }
	int GetMoney() { return m_statInfo._money; }
	int GetPlayerType() { return m_iPlayerType; }
	void CloseInventory() { InventoryOpened = false; }
protected:
	Inventory m_itemInventory;
	StatInfo m_itemStat;
	int m_iPlayerType;
	char m_jobName[32];
	Item* EquipedItem[5];
	bool InventoryOpened;
	StatInfo m_baseStat;
};

class Knight : public Player
{
public:
	Knight() : Player(PT_KNIGHT)
	{
		m_statInfo._maxHp = 100;
		m_statInfo._hp = 100;
		m_statInfo._att = 10;
		m_statInfo._def = 5;
		m_baseStat = m_statInfo;
		strcpy_s(m_jobName, "기사");
	}
	~Knight(){}
public:
	virtual void Attack(Creature* m_target);
};

class Arrow;
class Archer : public Player
{
public:
	Archer() : Player(PT_ARCHER), m_arrow(nullptr)
	{
		m_statInfo._maxHp = 80;
		m_statInfo._hp = 80;
		m_statInfo._att = 10;
		m_statInfo._def = 3;
		m_baseStat = m_statInfo;
		strcpy_s(m_jobName, "궁수");
	}
	~Archer() {}
public:
	virtual void Attack(Creature* _target);
	Arrow* GetArrowPointer() { return m_arrow; }
	void SetArrowPointerNull() { m_arrow = nullptr; }
private:
	Arrow* m_arrow;

};

class Mage : public Player
{
public:
	Mage() : Player(PT_MAGE)
	{
		m_statInfo._maxHp = 70;
		m_statInfo._hp = 70;
		m_statInfo._att = 10;
		m_statInfo._def = 1;
		m_baseStat = m_statInfo;
		strcpy_s(m_jobName, "마법사");
	}
	~Mage() {}
public:
	virtual void Attack(Creature* _target);

};