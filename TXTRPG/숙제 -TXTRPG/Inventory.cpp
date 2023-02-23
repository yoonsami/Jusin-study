#include "PCH.h"
#include "Inventory.h"
#include "Item.h"

Inventory::Inventory() : m_iItemCount(0), m_selectedItem(nullptr),
m_cursor{},m_iShowingInven(IM_NOTEQUIPED), m_Equiped{}, m_bItemSelected(false), selectedItemNum(0)
{

}

Inventory::~Inventory()
{
	Release();

}


void Inventory::Update()
{
	if (m_iShowingInven == IM_NOTEQUIPED && m_bItemSelected == false)  CursorControl(m_vNotEquiped.size());
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
			cout << endl << endl << "Z] �����ϱ� E] ������ ��� ���� ESC] ������" << endl;
		}
		else
		{
			ShowEquipedInven();
			cout << endl << endl << "Z] ���⿡ �����ϱ� ESC] ���ư���" << endl;
		}
	}
	else if (m_iShowingInven == IM_EQUIPED)
	{
			ShowEquipedInven();
			cout << endl << endl << "Z] �����ϱ� E] �������� ���� ��� ���� ESC] ������" << endl;
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
	if (m_iShowingInven == IM_NOTEQUIPED && m_bItemSelected == false && m_vNotEquiped.size() !=0)
	{
		m_selectedItem = m_vNotEquiped[static_cast<int>(m_cursor._crdX)];
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
	
	for (size_t i = 0; i < m_vNotEquiped.size(); ++i)
	{
		if (i < static_cast<size_t>(m_cursor._crdX))		cout << "��";
		else if (i == static_cast<size_t>(m_cursor._crdX)) cout << "��";
		else if (i > static_cast<size_t>(m_cursor._crdX))	cout << "��";
	}
	cout << endl;
	if (m_vNotEquiped.size() == 0)
		cout << "�������� �����ϴ�." << endl;
	else
	{
		if (m_vNotEquiped[static_cast<size_t>(m_cursor._crdX)])
			m_vNotEquiped[static_cast<size_t>(m_cursor._crdX)]->PrintInfo();
	}
}

void Inventory::ShowEquipedInven()
{
	cout << "��  �� : ";
	for (int i = 0; i < MAXEQUIP; ++i)
	{
		if (i < static_cast<int>(m_cursor._crdX) && m_cursor._crdY == IS_WEAPON)		cout << "��";
		else if (i == static_cast<int>(m_cursor._crdX) && m_cursor._crdY == IS_WEAPON) cout << "��";
		else if (i > static_cast<int>(m_cursor._crdX) && m_cursor._crdY == IS_WEAPON)	cout << "��";
		else cout << "��";
	}
	cout << endl;

	cout << "         ";
	for (int i = 0; i < MAXEQUIP; ++i)
	{
		if (m_Equiped[IS_WEAPON][i]) cout << "��";
		else cout << "��";
	}
	cout << endl;

	cout << "�� : ";
	for (int i = 0; i < MAXEQUIP; ++i)
	{
		if (i < static_cast<int>(m_cursor._crdX) && m_cursor._crdY == IS_ARMOR)		cout << "��";
		else if (i == static_cast<int>(m_cursor._crdX) && m_cursor._crdY == IS_ARMOR) cout << "��";
		else if (i > static_cast<int>(m_cursor._crdX) && m_cursor._crdY == IS_ARMOR)	cout << "��";
		else cout << "��";
	}
	cout << endl;

	cout << "         ";
	for (int i = 0; i < MAXEQUIP; ++i)
	{
		if (m_Equiped[IS_ARMOR][i]) cout << "��";
		else cout << "��";
	}
	cout << endl;
		if (m_Equiped[static_cast<size_t>(m_cursor._crdY)][static_cast<size_t>(m_cursor._crdX)])
			m_Equiped[static_cast<int>(m_cursor._crdY)][static_cast<int>(m_cursor._crdX)]->PrintInfo();
}

void Inventory::ControlUnequipedItem()
{
	//���õ� ��� ������ ���
	if (m_selectedItem->GetItemType() == IT_WEAPON)
	{
		m_cursor._crdY = IS_WEAPON;
		if (m_Equiped[static_cast<int>(m_cursor._crdY)][static_cast<int>(m_cursor._crdX)] == nullptr)
		{
			m_Equiped[static_cast<int>(m_cursor._crdY)][static_cast<int>(m_cursor._crdX)] = m_selectedItem;

			EquipItem(selectedItemNum);
			m_selectedItem = nullptr;
			m_bItemSelected = false;
		}
		else
		{
			cout << "�װ����� �̹� �������� �����Ǿ� �ֽ��ϴ�." << endl;
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
			EquipItem(selectedItemNum);
			m_selectedItem = nullptr;
			m_bItemSelected = false;
		}
		else
		{
			cout << "�װ����� �̹� �������� �����Ǿ� �ֽ��ϴ�." << endl;
			system("pause");
			m_selectedItem = nullptr;
			m_bItemSelected = false;
		}
	}

	m_cursor.ResetCoor();
}

void Inventory::ControlEquipedItem()
{

			m_vNotEquiped.push_back(m_Equiped[static_cast<int>(m_cursor._crdY)][static_cast<int>(m_cursor._crdX)]);
			m_Equiped[static_cast<int>(m_cursor._crdY)][static_cast<int>(m_cursor._crdX)] = nullptr;

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

void Inventory::AddItem(Item* item)
{
	m_vNotEquiped.push_back(item);
}

void Inventory::SwapIndex(size_t index)
{
	Item* tmp = m_vNotEquiped[index];
	m_vNotEquiped[index] = m_vNotEquiped.back();
	m_vNotEquiped.back() = tmp;
}

void Inventory::EquipItem(size_t index)
{
	SwapIndex(index);
	m_vNotEquiped.pop_back();
}

void Inventory::DeletItem(size_t index)
{
	SwapIndex(index);
	SAFE_DELETE(m_vNotEquiped.back());

	m_vNotEquiped.pop_back();
}

void Inventory::Release()
{
	if (m_vNotEquiped.size() != 0)
	{
		for (size_t i = 0; i < m_vNotEquiped.size(); i++)
		{
			delete m_vNotEquiped[i];
		}
	}

	for (int i = 0; i < IS_END; ++i)
	{
		for (int j = 0; j < MAXEQUIP; j++)
		{
			SAFE_DELETE(m_Equiped[i][j]);
		}
	}
}
