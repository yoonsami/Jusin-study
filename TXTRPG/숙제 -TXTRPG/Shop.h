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
	void Release();

private:
	bool Shopping;
	bool ShoppingMain;
	bool ShoppingWeapon;
	bool ShoppingArmor;
	Player* m_player;
	Item* m_item;
	PosInfo m_cursor;
};

