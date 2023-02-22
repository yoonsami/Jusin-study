#include "PCH.h"
#include "Item.h"

Item::Item(int itemType) : Object(OT_ITEM),m_iItemType(itemType), m_iRarity(0),m_iOwnerType(0)
{

}

Item::~Item()
{
}

void Item::SetRarity()
{
}

Weapon::Weapon(int ownerType, int rarity) :Item(IT_WEAPON)
{
	m_iOwnerType = ownerType;
	m_iRarity = rarity;
	SetItemStat();
}

Weapon::~Weapon()
{

}

void Weapon::PrintInfo()
{
	char owner[32] = {};
	switch (m_iOwnerType)
	{
	case PT_KNIGHT:
		strcpy_s(owner, "기사");
		break;
	case PT_ARCHER:
		strcpy_s(owner, "궁수");
		break;
	case PT_MAGE:
		strcpy_s(owner, "마법사");
		break;
	}
	char rarity[32] = {  };
	switch (m_iRarity)
	{
	case RT_COMMON:
		strcpy_s(rarity, "구린");
		break;
	case RT_RARE:
		strcpy_s(rarity, "보통");
		break;
	case RT_LEGEND:
		strcpy_s(rarity, "고급");
		break;
	}
	PRINT_LINE;
	cout << owner << "전용 " << rarity<< "무기" << endl;
	cout << "ATT  : " << m_statInfo._att << endl;
	cout << "가격 : " << m_statInfo._money << endl;
}

void Weapon::SetItemStat()
{
	m_statInfo._att = 1 * m_iRarity;
	m_statInfo._money = 50 * m_iRarity;
}

Armor::Armor(int ownerType, int rarity) :Item(IT_ARMOR)
{
	m_iOwnerType = ownerType;
	m_iRarity = rarity;
	SetItemStat();
}

Armor::~Armor()
{
}

void Armor::PrintInfo()
{
	char owner[32] = {};
	switch (m_iOwnerType)
	{
	case PT_KNIGHT:
		strcpy_s(owner, "기사");
		break;
	case PT_ARCHER:
		strcpy_s(owner, "궁수");
		break;
	case PT_MAGE:
		strcpy_s(owner, "마법사");
		break;
	}
	char rarity[32] = {  };
	switch (m_iRarity)
	{
	case RT_COMMON:
		strcpy_s(rarity, "구린");
		break;
	case RT_RARE:
		strcpy_s(rarity, "보통");
		break;
	case RT_LEGEND:
		strcpy_s(rarity, "고급");
		break;
	}
	PRINT_LINE;
	cout << owner << "전용 "<< rarity<< "방어구" << endl;
	cout << "Hp   : " << m_statInfo._maxHp << endl;
	cout << "Def  : " << m_statInfo._def << endl;
	cout << "가격 : " << m_statInfo._money << endl;
}

void Armor::SetItemStat()
{
	m_statInfo._maxHp = 1 * m_iRarity;
	m_statInfo._def = 1 * m_iRarity;
	m_statInfo._money = 50 * m_iRarity;
}
