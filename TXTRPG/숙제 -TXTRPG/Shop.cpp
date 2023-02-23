#include "PCH.h"
#include "Shop.h"
#include "Item.h"
#include "Player.h"

Shop::Shop() :m_player(nullptr), m_item(nullptr), m_cursor{}, SellingItem(false),
ShoppingMain(true), ShoppingArmor(false), ShoppingWeapon(false),Shopping(true)
{
}

Shop::~Shop()
{

}

void Shop::Init(Player* _player)
{
	m_player = _player;
	Shopping = true;
	ShoppingMain = true;
	ShoppingWeapon = false;
	ShoppingArmor = false;
}

void Shop::Update()
{
	if (ShoppingMain)
	{
		CursorControl(MAINSHOPNUM);
	}
	else if (ShoppingWeapon && SellingItem == false)
	{
		CursorControl(WEAPONSHOPNUM);
	}
	else if (ShoppingArmor && SellingItem == false)
	{
		CursorControl(ARMORSHOPNUM);
	}
	else if (SellingItem)
	{
		size_t tmp = m_player->GetInventory().InvenSize();
		CursorControl(tmp);
	}
	
}
void Shop::Render()
{
	system("cls");

	if (ShoppingMain)
	{
		switch (static_cast<int>(m_cursor._crdX))
		{
		case 0:
			cout << "�� ���� ����\t�� �� ����\t�� ���ư���" << endl;
			break;
		case 1:
			cout << "�� ���� ����\t�� �� ����\t�� ���ư���" << endl;
			break;
		case MAINSHOPNUM - 1:
			cout << "�� ���� ����\t�� �� ����\t�� ���ư���" << endl;
			break;
		}
	}
	else if (ShoppingWeapon && SellingItem == false)
	{
		switch (static_cast<int>(m_cursor._crdX))
		{
		case 0:
			cout << "�� ���� ����\t�� ���� ����\t�� ��� ����\t�� �Ǹ��ϱ�\t�� ���ư��� " << endl;
			m_item = new Weapon(m_player->GetPlayerType(), RT_COMMON);
			m_item->PrintInfo();
			m_player->PrintInfo();
			SAFE_DELETE(m_item);
			break;
		case 1:
			cout << "�� ���� ����\t�� ���� ����\t�� ��� ����\t�� �Ǹ��ϱ�\t�� ���ư���" << endl;
			m_item = new Weapon(m_player->GetPlayerType(), RT_RARE);
			m_item->PrintInfo();
			m_player->PrintInfo();
			SAFE_DELETE(m_item);
			break;
		case 2:
			cout << "�� ���� ����\t�� ���� ����\t�� ��� ����\t�� �Ǹ��ϱ�\t�� ���ư���" << endl;
			m_item = new Weapon(m_player->GetPlayerType(), RT_LEGEND);
			m_item->PrintInfo();
			m_player->PrintInfo();
			SAFE_DELETE(m_item);
			break;
		case 3:
			cout << "�� ���� ����\t�� ���� ����\t�� ��� ����\t�� �Ǹ��ϱ�\t�� ���ư���" << endl;
			break;
		case WEAPONSHOPNUM - 1:
			cout << "�� ���� ����\t�� ���� ����\t�� ��� ����\t�� �Ǹ��ϱ�\t�� ���ư���" << endl;
			break;
		}
	}
	else if (ShoppingArmor && SellingItem == false)
	{
		switch (static_cast<int>(m_cursor._crdX))
		{
		case 0:
			cout << "�� ���� ��\t�� ���� ��\t�� ��� ��\t�� �Ǹ��ϱ�\t�� ���ư��� " << endl;
			m_item = new Armor(m_player->GetPlayerType(), RT_COMMON);
			m_item->PrintInfo();
			m_player->PrintInfo();
			SAFE_DELETE(m_item);
			break;
		case 1:
			cout << "�� ���� ��\t�� ���� ��\t�� ��� ��\t�� �Ǹ��ϱ�\t�� ���ư���" << endl;
			m_item = new Armor(m_player->GetPlayerType(), RT_RARE);
			m_item->PrintInfo();
			m_player->PrintInfo();
			SAFE_DELETE(m_item);
			break;
		case 2:
			cout << "�� ���� ��\t�� ���� ��\t�� ��� ��\t�� �Ǹ��ϱ�\t�� ���ư���" << endl;
			m_item = new Armor(m_player->GetPlayerType(), RT_LEGEND);
			m_item->PrintInfo();
			m_player->PrintInfo();
			SAFE_DELETE(m_item);
			break;
		case 3:
			cout << "�� ���� ��\t�� ���� ��\t�� ��� ��\t�� �Ǹ��ϱ�\t�� ���ư���" << endl;
			break;
		case ARMORSHOPNUM - 1:
			cout << "�� ���� ��\t�� ���� ��\t�� ��� ��\t�� �Ǹ��ϱ�\t�� ���ư���" << endl;
			break;
		}
	}
	else if (SellingItem)
	{
		if (m_player->GetInventory().InvenSize() != 0)
		{
			ShowNotEquipedInven();
			cout << "Z] �Ǹ��ϱ� ESC] ���ư���" << endl;
		}
		else
		{
			cout << "�κ��丮�� ������ϴ�." << endl;
			cout << "ESC] ���ư���" << endl;
		}
	}
}
void Shop::CursorControl(int MenuSize)
{
	if (_kbhit())
	{
		char c = _getch();
		if (c == DIRKEY)
			CursorMove(MenuSize);
		else if (c == 'z' || c == 'Z' || c == ENTER || c == SPACEBAR)
			CursorSelectMenu();
		else if (c == ESCAPE)
		{
			if (ShoppingMain)
			{
				Shopping = false;
				m_cursor.ResetCoor();
			}
			else if ((ShoppingWeapon || ShoppingArmor) && SellingItem == false)
			{
				ShoppingWeapon = false;
				ShoppingArmor = false;
				ShoppingMain = true;
				m_cursor.ResetCoor();
			}
			else if (SellingItem == true)
			{
				SellingItem = false;
				m_cursor.ResetCoor();
			}
		}
		else
			while (getchar() != '\n');
	}
}



void Shop::CursorMove(int MenuSize)
{
	char c = _getch();

	switch (c)
	{
	case UP:
		break;
	case DOWN:
		break;
	case LEFT:
		m_cursor.MoveLeft();
		break;
	case RIGHT:
		m_cursor.MoveRight(MenuSize);
		break;
	default:
		break;
	}
}

void Shop::CursorSelectMenu()
{
	if (ShoppingMain)
	{
		switch (static_cast<int>(m_cursor._crdX))
		{
		case 0:
			ShoppingMain = false;
			ShoppingWeapon = true;
			ShoppingArmor = false;
			m_cursor.ResetCoor();
			break;
		case 1:
			ShoppingMain = false;
			ShoppingWeapon = false;
			ShoppingArmor = true;
			m_cursor.ResetCoor();
			break;
		case MAINSHOPNUM - 1:
			Shopping = false;
			m_cursor.ResetCoor();
			break;
		}
	}
	else if (ShoppingWeapon && SellingItem == false)
	{
		switch (static_cast<int>(m_cursor._crdX))
		{
		case 0:
			m_item = new Weapon(m_player->GetPlayerType(), RT_COMMON);
			if (m_player->GetMoney() >= m_item->GetPrice())
			{
				m_player->GetInventory().AddItem(m_item);
				m_player->AddMoney(-m_item->GetPrice());
				cout << "���Ÿ� �Ϸ��߽��ϴ�." << endl;
				system("pause");

				m_item = nullptr;
			}
			else if (m_player->GetMoney() < m_item->GetPrice())
			{
				cout << "��尡 ���ڶ��ϴ�." << endl;
				system("pause");
				SAFE_DELETE(m_item);
			}
			break;
		case 1:
			m_item = new Weapon(m_player->GetPlayerType(), RT_RARE);
			if (m_player->GetMoney() >= m_item->GetPrice())
			{
				m_player->GetInventory().AddItem(m_item);
				m_player->AddMoney(-m_item->GetPrice());
				cout << "���Ÿ� �Ϸ��߽��ϴ�." << endl;
				system("pause");

				m_item = nullptr;
			}
			else if (m_player->GetMoney() < m_item->GetPrice())
			{
				cout << "��尡 ���ڶ��ϴ�." << endl;
				system("pause");
				SAFE_DELETE(m_item);
			}
			break;
		case 2:
			m_item = new Weapon(m_player->GetPlayerType(), RT_LEGEND);
			if (m_player->GetMoney() >= m_item->GetPrice())
			{
				m_player->GetInventory().AddItem(m_item);
				m_player->AddMoney(-m_item->GetPrice());
				cout << "���Ÿ� �Ϸ��߽��ϴ�." << endl;
				system("pause");

				m_item = nullptr;
			}
			else if (m_player->GetMoney() < m_item->GetPrice())
			{
				cout << "��尡 ���ڶ��ϴ�." << endl;
				system("pause");
				SAFE_DELETE(m_item);
			}
			break;
		case 3:
			SellingItem = true;
			m_cursor.ResetCoor();
			break;
		case WEAPONSHOPNUM - 1:
			ShoppingWeapon = false;
			ShoppingMain = true;
			m_cursor.ResetCoor();
			break;
		}
	}
	else if (ShoppingArmor && SellingItem == false)
	{
		switch (static_cast<int>(m_cursor._crdX))
		{
		case 0:
			m_item = new Armor(m_player->GetPlayerType(), RT_COMMON);
			if (m_player->GetMoney() >= m_item->GetPrice())
			{
				m_player->GetInventory().AddItem(m_item);
				m_player->AddMoney(-m_item->GetPrice());
				cout << "���Ÿ� �Ϸ��߽��ϴ�." << endl;
				system("pause");

				m_item = nullptr;
			}
			else if (m_player->GetMoney() < m_item->GetPrice())
			{
				cout << "��尡 ���ڶ��ϴ�." << endl;
				system("pause");
				SAFE_DELETE(m_item);
			}
			
			break;
		case 1:
			m_item = new Armor(m_player->GetPlayerType(), RT_RARE);
			if (m_player->GetMoney() >= m_item->GetPrice())
			{
				m_player->GetInventory().AddItem(m_item);
				m_player->AddMoney(-m_item->GetPrice());
				cout << "���Ÿ� �Ϸ��߽��ϴ�." << endl;
				system("pause");

				m_item = nullptr;
			}
			else if (m_player->GetMoney() < m_item->GetPrice())
			{
				cout << "��尡 ���ڶ��ϴ�." << endl;
				system("pause");
				SAFE_DELETE(m_item);
			}
			break;
		case 2:
			m_item = new Armor(m_player->GetPlayerType(), RT_LEGEND);
			if (m_player->GetMoney() >= m_item->GetPrice())
			{
				m_player->GetInventory().AddItem(m_item);
				m_player->AddMoney(-m_item->GetPrice());
				cout << "���Ÿ� �Ϸ��߽��ϴ�." << endl;
				system("pause");

				m_item = nullptr;
			}
			else if (m_player->GetMoney() < m_item->GetPrice())
			{
				cout << "��尡 ���ڶ��ϴ�." << endl;
				system("pause");
				SAFE_DELETE(m_item);
			}
			break;
		case 3:
			SellingItem = true;
			m_cursor.ResetCoor();
			break;
		case ARMORSHOPNUM - 1:
			ShoppingArmor = false;
			ShoppingMain = true;
			m_cursor.ResetCoor();
			break;
		}
	}
	else if (SellingItem == true && m_player->GetInventory().InvenSize())
	{
		Item* tmp = m_player->GetInventory().GetNotequipedItem(static_cast<size_t>(m_cursor._crdX));
		if (ShoppingWeapon && tmp->GetItemType() == IT_WEAPON)
		{
			SellItem(static_cast<size_t>(m_cursor._crdX));
		}
		else if (ShoppingArmor && tmp->GetItemType() == IT_ARMOR)
		{
			SellItem(static_cast<size_t>(m_cursor._crdX));
		}
		else
		{
			cout << "���⼭ �� �� ���� �����Դϴ�." << endl;
			system("pause");
		}
	}
}

void Shop::SellItem(size_t index)
{
	int price = m_player->GetInventory().GetNotequipedItem(index)->GetPrice();
	m_player->AddMoney(price);
	m_player->GetInventory().DeletItem(index);
	cout << "�������� �Ǹ��߽��ϴ�." << endl;
	m_cursor.ResetCoor();
	system("pause");
}

void Shop::Release()
{
	SAFE_DELETE(m_item);
}

void Shop::ShowNotEquipedInven()
{
	
	for (size_t i = 0; i < m_player->GetInventory().InvenSize(); ++i)
	{
		if (i < static_cast<size_t>(m_cursor._crdX))		cout << "��";
		else if (i == static_cast<size_t>(m_cursor._crdX)) cout << "��";
		else if (i > static_cast<size_t>(m_cursor._crdX))	cout << "��";
	}
	cout << endl;
	if (m_player->GetInventory().InvenSize() == 0)
		cout << "�������� �����ϴ�." << endl;
	else
	{
		
		if (m_player->GetInventory().GetNotequipedItem(static_cast<size_t>(m_cursor._crdX)))
			m_player->GetInventory().GetNotequipedItem(static_cast<size_t>(m_cursor._crdX))->PrintInfo();
	}
}

