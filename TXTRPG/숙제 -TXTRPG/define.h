#pragma once
#define SAFE_DELETE(p) if(p) {delete p; p =nullptr;}
#define SAFE_DELETE_ARR(p) if(p) {delete[] p; p =nullptr;}
#define MAP_WIDTH 20
#define MAP_HEIGHT 10
#define PRINT_LINE cout << "=================================" << endl
#define CLEAR_CIN cin.clear(); cin.ignore();
#define INVENTORY_SIZE 10
#define MAINMENU 3
#define MAX_SPEED 3
#define JUMP_POWER 3
#define MAX_ARROW 9
#define MAXEQUIP 3
#define MAINSHOPNUM 3
#define WEAPONSHOPNUM 5
#define ARMORSHOPNUM 5


enum ITEMTYPE
{
	IT_WEAPON = 1,
	IT_ARMOR = 2
};


struct StatInfo
{
	char _name[32];
	int _maxHp;
	int _hp;
	int _att;
	int _def;
	int _money;
	StatInfo operator+(const StatInfo& item)
	{
		StatInfo tmp = { 0 };
		tmp._maxHp = item._maxHp + _maxHp;
		tmp._hp += item._hp + _hp;
		tmp._att += item._att + _att;
		tmp._def += item._def + _def;
		return tmp;
	}
	StatInfo& operator-(const StatInfo& item)
	{
		_maxHp -= item._maxHp;
		_hp -= item._hp;
		_att -= item._att;
		_def -= item._def;
		return *this;
	}
	StatInfo& operator=(const StatInfo& rhs)
	{
		_maxHp = rhs._maxHp;
		_hp = rhs._hp;
		_att = rhs._att;
		_def = rhs._def;
		return *this;
	}
	StatInfo& operator+=(const StatInfo& rhs)
	{
		_maxHp += rhs._maxHp;
		_hp += rhs._hp;
		_att += rhs._att;
		_def += rhs._def;
		return *this;
	}
};

struct PosInfo
{
	float _crdX;

	float _crdY;
	bool operator==(const PosInfo& src)
	{
		if ((_crdX == src._crdX) && (_crdY == src._crdY))
			return true;
		else
			return false;
	}
	PosInfo operator*(const float& a)
	{
		PosInfo tmp;
		tmp._crdX = _crdX * a;
		tmp._crdY = _crdY * a;
		return tmp;
	}

	PosInfo operator+(const PosInfo& rhs)
	{
		PosInfo tmp;
		tmp._crdX = _crdX + rhs._crdX;
		tmp._crdY = _crdY + rhs._crdY;
		return tmp;
	}

	PosInfo operator-(const PosInfo& rhs)
	{
		PosInfo tmp;
		tmp._crdX = _crdX - rhs._crdX;
		tmp._crdY = _crdY - rhs._crdY;
		return tmp;
	}

	void operator+=(const PosInfo& rhs)
	{
		_crdX += rhs._crdX;
		_crdY += rhs._crdY;
	}
	void ResetCoor()
	{
		_crdX = 0;
		_crdY = 0;
	}
	void MoveRight(int MaxSize) { ++_crdX; if (_crdX > static_cast<float>(MaxSize-1)) _crdX = static_cast<float>(MaxSize-1); }
	void MoveLeft() { --_crdX; if (_crdX <= 0) _crdX = 0; }
	void MoveUp() { --_crdY; if (_crdY <= 0) _crdY = 0; }
	void MoveDown(int MaxSize) {
		++_crdY; if (_crdY >  static_cast<float>(MaxSize - 1)) _crdY = static_cast<float>(MaxSize - 1);
	}

	float OfSize()
	{
		return sqrt(static_cast<float>(pow(_crdX, 2)) + static_cast<float>(pow(_crdY, 2)));
	}
};


enum OBJECTTYPE
{
	OT_CREATURE =1,
	OT_ITEM
};

enum CREATURETYPE
{
	CT_PLAYER = 1,
	CT_MONSTER
};

enum PLAYERTYPE
{
	PT_KNIGHT = 1,
	PT_ARCHER,
	PT_MAGE
};

enum MONSTERTYPE
{
	MT_SLIME = 1,
	MT_SKELETON,
	MT_ORC
};

enum DIRECTION
{
	DIRKEY = -32,
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACEBAR = 32,
	ENTER = 13,
	ESCAPE = 27

};

enum MAPTILE
{
	WALL = 1,
};

enum RARITYTYPE
{
	RT_COMMON =1,
	RT_RARE,
	RT_LEGEND
};

enum INVENTORYSIZE
{
	IS_WEAPON =0,
	IS_ARMOR,
	IS_END
};

enum INVENTORYMENU
{
	IM_CLOSED = 0,
	IM_NOTEQUIPED =1,
	IM_EQUIPED
};