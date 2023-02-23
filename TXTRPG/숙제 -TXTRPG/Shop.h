#pragma once
#include "define.h"

class Player;
class Item;
class Shop
{
public:
	Shop();
	~Shop();

public:
	void Init(Player* _player);
	void Update();
	void CursorControl(int MenuSize);
	void Render();
	void CursorMove(int MenuSize);
	void CursorSelectMenu();
	bool IsShopping() { return Shopping; }
	void StartShopping() { Shopping = true; }
	void SellItem(size_t index);
	void Release();
	void ShowNotEquipedInven();
private:
	bool Shopping;
	bool ShoppingMain;
	bool ShoppingWeapon;
	bool ShoppingArmor;
	bool SellingItem;
	Player* m_player;
	Item* m_item;
	PosInfo m_cursor;
};

