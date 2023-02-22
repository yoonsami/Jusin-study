#include "PCH.h"
#include "Shop.h"
#include "Item.h"
#include "Player.h"

Shop::Shop() :m_player(nullptr), m_item(nullptr), m_cursor{},
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
		CursorControl(3);
	}
	else if (ShoppingWeapon)
	{
		CursorControl(4);
	}
	else if (ShoppingArmor)
	{
		CursorControl(4);
	}
}

void Shop::CursorControl(int MenuSize)
{
	if (_kbhit())
	{
		char c = _getch();
		if (c == DIRKEY)
			CursorMove(MenuSize);
		else if (c == 'z' || c == 'Z')
			CursorSelectMenu();
		else if (c == ESCAPE)
		{
			if (ShoppingMain)
			{
				Shopping = false;
				m_cursor.ResetCoor();
			}
			else if (ShoppingWeapon || ShoppingArmor)
			{
				ShoppingWeapon = false;
				ShoppingArmor = false;
				ShoppingMain = true;
				m_cursor.ResetCoor();
			}
		}
		else
			while (getchar() != '\n');
	}
}

void Shop::Render()
{
	system("cls");
	if(ShoppingMain)
	{
		switch (static_cast<int>(m_cursor._crdX))
		{
		case 0:
			cout << "�� ���� ����\t�� �� ����\t�� ���ư���" << endl;
			break;
		case 1:
			cout << "�� ���� ����\t�� �� ����\t�� ���ư���" << endl;
			break;
		case 2:
			cout << "�� ���� ����\t�� �� ����\t�� ���ư���" << endl;
			break;
		}
	}
	else if (ShoppingWeapon)
	{
		switch (static_cast<int>(m_cursor._crdX))
		{
		case 0:
			cout << "�� ���� ����\t�� ���� ����\t�� ��� ����\t�� ���ư��� " << endl;
			m_item = new Weapon(m_player->GetPlayerType(), RT_COMMON);
			m_item->PrintInfo();
			m_player->PrintInfo();
			SAFE_DELETE(m_item);
			break;
		case 1:
			cout << "�� ���� ����\t�� ���� ����\t�� ��� ����\t�� ���ư���" << endl;
			m_item = new Weapon(m_player->GetPlayerType(), RT_RARE);
			m_item->PrintInfo();
			m_player->PrintInfo();
			SAFE_DELETE(m_item);
			break;
		case 2:
			cout << "�� ���� ����\t�� ���� ����\t�� ��� ����\t�� ���ư���" << endl;
			m_item = new Weapon(m_player->GetPlayerType(), RT_LEGEND);
			m_item->PrintInfo();
			m_player->PrintInfo();
			SAFE_DELETE(m_item);
			break;
		case 3:
			cout << "�� ���� ����\t�� ���� ����\t�� ��� ����\t�� ���ư���" << endl;
			break;
		}
	}
	else if (ShoppingArmor)
	{
		switch (static_cast<int>(m_cursor._crdX))
		{
		case 0:
			cout << "�� ���� ��\t�� ���� ��\t�� ��� ��\t�� ���ư��� " << endl;
			m_item = new Armor(m_player->GetPlayerType(), RT_COMMON);
			m_item->PrintInfo();
			m_player->PrintInfo();
			SAFE_DELETE(m_item);
			break;
		case 1:
			cout << "�� ���� ��\t�� ���� ��\t�� ��� ��\t�� ���ư���" << endl;
			m_item = new Armor(m_player->GetPlayerType(), RT_RARE);
			m_item->PrintInfo();
			m_player->PrintInfo();
			SAFE_DELETE(m_item);
			break;
		case 2:
			cout << "�� ���� ��\t�� ���� ��\t�� ��� ��\t�� ���ư���" << endl;
			m_item = new Armor(m_player->GetPlayerType(), RT_LEGEND);
			m_item->PrintInfo();
			m_player->PrintInfo();
			SAFE_DELETE(m_item);
			break;
		case 3:
			cout << "�� ���� ��\t�� ���� ��\t�� ��� ��\t�� ���ư���" << endl;
			break;
		}
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
		case 2:
			Shopping = false;
			m_cursor.ResetCoor();
			break;
		}
	}
	else if (ShoppingWeapon)
	{
		switch (static_cast<int>(m_cursor._crdX))
		{
		case 0:
			m_item = new Weapon(m_player->GetPlayerType(), RT_COMMON);
			if (m_player->GetMoney() >= m_item->GetPrice())
			{
				bool purchased = m_player->AddItemToInven(m_item);
				if(purchased)
				{
					cout << "���Ÿ� �Ϸ��߽��ϴ�." << endl;
					system("pause");
				}
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
				bool purchased = m_player->AddItemToInven(m_item);
				if (purchased)
				{
					cout << "���Ÿ� �Ϸ��߽��ϴ�." << endl;
					system("pause");
				}
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
				bool purchased = m_player->AddItemToInven(m_item);
				if (purchased)
				{
					cout << "���Ÿ� �Ϸ��߽��ϴ�." << endl;
					system("pause");
				}
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
			ShoppingWeapon = false;
			ShoppingMain = true;
			m_cursor.ResetCoor();
			break;
		}
	}
	else if (ShoppingArmor)
	{
		switch (static_cast<int>(m_cursor._crdX))
		{
		case 0:
			m_item = new Armor(m_player->GetPlayerType(), RT_COMMON);
			if (m_player->GetMoney() >= m_item->GetPrice())
			{
				bool purchased = m_player->AddItemToInven(m_item);
				if (purchased)
				{
					cout << "���Ÿ� �Ϸ��߽��ϴ�." << endl;
					system("pause");
				}
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
				bool purchased = m_player->AddItemToInven(m_item);
				if (purchased)
				{
					cout << "���Ÿ� �Ϸ��߽��ϴ�." << endl;
					system("pause");
				}
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
				bool purchased = m_player->AddItemToInven(m_item);
				if (purchased)
				{
					cout << "���Ÿ� �Ϸ��߽��ϴ�." << endl;
					system("pause");
				}
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
			ShoppingArmor = false;
			ShoppingMain = true;
			m_cursor.ResetCoor();
			break;
		}
	}
}

void Shop::Release()
{
	SAFE_DELETE(m_item);
}
