#pragma once
#include "Object.h"
#include "define.h"
class Item : public Object
{
public:
	Item(int itemType);
	~Item();

public:
	virtual void PrintInfo() = 0;
	void SetRarity();
	int GetPrice() { return m_statInfo._money; }
	virtual void SetItemStat() = 0;
	int GetItemType() { return m_iItemType; }
	StatInfo& GetItemInfo() { return m_statInfo; }
protected:
	int m_iItemType;
	int m_iRarity;
	int m_iOwnerType;
};

class Weapon : public Item
{
public:
	Weapon(int ownerType, int rarity);
	~Weapon();

public:
	void PrintInfo();
	void SetItemStat();
};

class Armor : public Item
{
public:
	Armor(int ownerType, int rarity);
	~Armor();

public:

	void PrintInfo();
	void SetItemStat();

};