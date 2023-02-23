#pragma once
#include "define.h"

class Item;
class Inventory
{
public:
	Inventory();
	~Inventory();

public:
	void Update();
	void Render();
	void CursorControl(int MenuSize);
	void CursorControl(int itemType, int maxsize);
	void CursorMove(int MaxSize);
	void CursorMove(int itemType, int maxsize);
	void CursorSelectMenu();
	void ShowNotEquipedInven();
	void ShowEquipedInven();
	void OpendInven() { m_iShowingInven = IM_NOTEQUIPED; }
	bool IsOpened() { if (m_iShowingInven == IM_CLOSED) return false; else return true; }
	void ControlUnequipedItem();
	void ControlEquipedItem();
	StatInfo GetEquipedItemStat();
	void AddItem(Item* item);
private:
	Item* m_selectedItem;
	int selectedItemNum;
	bool m_bItemSelected;
	int m_iShowingInven;
	vector<Item*> m_vNotEquiped;
	Item* m_Equiped[IS_END][MAXEQUIP];
	int m_iItemCount;
	PosInfo m_cursor;
	vector<Item*>::iterator it;
};

