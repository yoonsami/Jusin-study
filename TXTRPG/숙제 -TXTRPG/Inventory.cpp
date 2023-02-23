#include "PCH.h"
#include "Inventory.h"
#include "Item.h"

Inventory::Inventory() : m_iItemCount(0), m_notEquiped{}, m_selectedItem(nullptr),
m_cursor{},m_iShowingInven(IM_NOTEQUIPED), m_Equiped{}, m_bItemSelected(false), selectedItemNum(0)
{

}

Inventory::~Inventory()
{

}

bool Inventory::AddItem(Item* _newItem)
{
	for (int i = 0; i < INVENTORY_SIZE; ++i)
	{
		if (m_notEquiped[i] == nullptr)
		{
			m_notEquiped[i] = _newItem;
			++m_iItemCount;
			_newItem = nullptr;
			return true;
		}
	}
	_newItem = nullptr;
	return false;
}

void Inventory::Update()
{
	if (m_iShowingInven == IM_NOTEQUIPED && m_bItemSelected == false)  CursorControl(INVENTORY_SIZE);
	else if (m_iShowingInven == IM_NOTEQUIPED && m_bItemSelected == true)  CursorControl(IS_END, MAXEQUIP);
	else if(m_iShowingInven == IM_EQUIPED) CursorControl(IS_END, MAXEQUIP);
}

void Inventory::Render()
{
	system("cls");
	if (m_iShowingInven == IM_NOTEQUIPED)
	{
		
		if (m_bItemSelected == false)
		{
			ShowNotEquipedInven();
			cout << endl << endl << "Z] 장착하기 E] 장착한 목록 보기 ESC] 나가기" << endl;
		}
		else
		{
			ShowEquipedInven();
			cout << endl << endl << "Z] 여기에 장착하기 ESC] 돌아가기" << endl;
		}
	}
	else if (m_iShowingInven == IM_EQUIPED)
	{
			ShowEquipedInven();
			cout << endl << endl << "Z] 해제하기 E] 장착하지 않은 장비 보기 ESC] 나가기" << endl;
	}
}

void Inventory::CursorControl(int MenuSize)
{
	if (_kbhit())
	{
		char c = _getch();
		if (c == DIRKEY)
			CursorMove(MenuSize);
		else if (c == 'z' || c == 'Z')
		{
			if (m_bItemSelected == false)
				CursorSelectMenu();
		}
		else if (c == ESCAPE)
		{
			if (m_bItemSelected == false)
				m_iShowingInven = IM_CLOSED;
			else
				m_bItemSelected = false;
		}
		else if (c == 'E' || c == 'e')
		{
			m_iShowingInven = IM_EQUIPED;
			m_cursor.ResetCoor();
		}
		else
			while (getchar() != '\n');
	}
}

void Inventory::CursorControl(int itemType, int maxsize)
{
	if (_kbhit())
	{
		char c = _getch();
		if (c == DIRKEY)
			CursorMove(itemType, maxsize);
		else if (c == 'z' || c == 'Z')
		{
			if (m_bItemSelected == false)
				CursorSelectMenu();
			else
				ControlUnequipedItem();
		}
		else if (c == ESCAPE)
		{
			if (m_bItemSelected == false)
				m_iShowingInven = IM_CLOSED;
			else
				m_bItemSelected = false;
		}
		else if (c == 'E' || c == 'e')
		{
			m_iShowingInven = IM_NOTEQUIPED;
			m_cursor.ResetCoor();
		}
		else
			while (getchar() != '\n');
	}
}

void Inventory::CursorMove(int MenuSize)
{
	char c = _getch();

	switch (c)
	{
	case UP:
		m_cursor.MoveLeft();
		break;
	case DOWN:
		m_cursor.MoveRight(MenuSize);
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

void Inventory::CursorMove(int itemType, int maxsize)
{
	char c = _getch();

	switch (c)
	{
	case UP:
		if(m_bItemSelected == false)
			m_cursor.MoveUp();
		break;
	case DOWN:
		if (m_bItemSelected == false)
			m_cursor.MoveDown(itemType);
		break;
	case LEFT:
		m_cursor.MoveLeft();
		break;
	case RIGHT:
		m_cursor.MoveRight(maxsize);
		break;
	default:
		break;
	}
}

void Inventory::CursorSelectMenu()
{
	if (m_iShowingInven == IM_NOTEQUIPED && m_bItemSelected == false && m_notEquiped[static_cast<int>(m_cursor._crdX)])
	{
		m_selectedItem = m_notEquiped[static_cast<int>(m_cursor._crdX)];
		selectedItemNum = static_cast<int>(m_cursor._crdX);
		m_bItemSelected = true;
		if (m_selectedItem->GetItemType() == IT_WEAPON) 
		{
			m_cursor._crdY = IS_WEAPON;
			m_cursor._crdX = 0;
		}
		else
		{
			m_cursor._crdY = IS_ARMOR;
			m_cursor._crdX = 0;
		}
	}
	else if (m_iShowingInven == IM_EQUIPED && m_Equiped[static_cast<int>(m_cursor._crdY)][static_cast<int>(m_cursor._crdX)])
	{
		ControlEquipedItem();
	}
}

void Inventory::ShowNotEquipedInven()
{
	
	for (int i = 0; i < INVENTORY_SIZE; ++i)
	{
		if (i < static_cast<int>(m_cursor._crdX))		cout << "□";
		else if (i == static_cast<int>(m_cursor._crdX)) cout << "■";
		else if (i > static_cast<int>(m_cursor._crdX))	cout << "□";
	}
	cout << endl;
	for (int i = 0; i < INVENTORY_SIZE; ++i)
	{
	if (m_notEquiped[i]) cout << "★";
	else cout << "☆";
	}
	cout << endl;
	if (m_notEquiped[static_cast<int>(m_cursor._crdX)])
		m_notEquiped[static_cast<int>(m_cursor._crdX)]->PrintInfo();

	
}

void Inventory::ShowEquipedInven()
{
	cout << "무  기 : ";
	for (int i = 0; i < MAXEQUIP; ++i)
	{
		if (i < static_cast<int>(m_cursor._crdX) && m_cursor._crdY == IS_WEAPON)		cout << "□";
		else if (i == static_cast<int>(m_cursor._crdX) && m_cursor._crdY == IS_WEAPON) cout << "■";
		else if (i > static_cast<int>(m_cursor._crdX) && m_cursor._crdY == IS_WEAPON)	cout << "□";
		else cout << "□";
	}
	cout << endl;

	cout << "         ";
	for (int i = 0; i < MAXEQUIP; ++i)
	{
		if (m_Equiped[IS_WEAPON][i]) cout << "★";
		else cout << "☆";
	}
	cout << endl;

	cout << "방어구 : ";
	for (int i = 0; i < MAXEQUIP; ++i)
	{
		if (i < static_cast<int>(m_cursor._crdX) && m_cursor._crdY == IS_ARMOR)		cout << "□";
		else if (i == static_cast<int>(m_cursor._crdX) && m_cursor._crdY == IS_ARMOR) cout << "■";
		else if (i > static_cast<int>(m_cursor._crdX) && m_cursor._crdY == IS_ARMOR)	cout << "□";
		else cout << "□";
	}
	cout << endl;

	cout << "         ";
	for (int i = 0; i < MAXEQUIP; ++i)
	{
		if (m_Equiped[IS_ARMOR][i]) cout << "★";
		else cout << "☆";
	}
	cout << endl;
	if (m_Equiped[static_cast<int>(m_cursor._crdY)][static_cast<int>(m_cursor._crdX)])
		m_Equiped[static_cast<int>(m_cursor._crdY)][static_cast<int>(m_cursor._crdX)]->PrintInfo();
	
}

void Inventory::ControlUnequipedItem()
{
	//선택된 장비가 무기일 경우
	if (m_selectedItem->GetItemType() == IT_WEAPON)
	{
		m_cursor._crdY = IS_WEAPON;
		if (m_Equiped[static_cast<int>(m_cursor._crdY)][static_cast<int>(m_cursor._crdX)] == nullptr)
		{
			m_Equiped[static_cast<int>(m_cursor._crdY)][static_cast<int>(m_cursor._crdX)] = m_selectedItem;
			m_notEquiped[selectedItemNum] = nullptr;
			m_selectedItem = nullptr;
			m_bItemSelected = false;
		}
		else
		{
			cout << "그곳에는 이미 아이템이 장착되어 있습니다." << endl;
			system("pause");
			m_selectedItem = nullptr;
			m_bItemSelected = false;
		}
	}
	else if (m_selectedItem->GetItemType() == IT_ARMOR)
	{
		m_cursor._crdY = IS_ARMOR;
		if (m_Equiped[static_cast<int>(m_cursor._crdY)][static_cast<int>(m_cursor._crdX)] == nullptr)
		{
			m_Equiped[static_cast<int>(m_cursor._crdY)][static_cast<int>(m_cursor._crdX)] = m_selectedItem;
			m_notEquiped[selectedItemNum] = nullptr;
			m_selectedItem = nullptr;
			m_bItemSelected = false;
		}
		else
		{
			cout << "그곳에는 이미 아이템이 장착되어 있습니다." << endl;
			system("pause");
			m_selectedItem = nullptr;
			m_bItemSelected = false;
		}
	}
}

void Inventory::ControlEquipedItem()
{
	for (int i = 0; i < INVENTORY_SIZE; ++i)
	{
		if (m_notEquiped[i] == nullptr)
		{
			m_notEquiped[i] = m_Equiped[static_cast<int>(m_cursor._crdY)][static_cast<int>(m_cursor._crdX)];
			m_Equiped[static_cast<int>(m_cursor._crdY)][static_cast<int>(m_cursor._crdX)] = nullptr;
			return;
		}
	}

	cout << "인벤토리가 가득 차 장비를 벗을 수 없습니다." << endl;
	system("pause");
}

StatInfo Inventory::GetEquipedItemStat()
{
	StatInfo tmp = {};
	for (int i = 0; i < IS_END; ++i)
	{
		for (int j = 0; j < MAXEQUIP; ++j)
		{
			if (m_Equiped[i][j])
			{
				tmp += m_Equiped[i][j]->GetItemInfo();
			}
		}
	}
	return tmp;
}
