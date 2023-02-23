#pragma once
#include "define.h"

class Monster;
class Player;
class Arrow;
class Shop;

class Field
{
public:
	Field();
	~Field();
public:
	void Init(Player* _player);
	void CreateMap();
	void Update();
	void CreateMonster();
	void Render();
	void SetObjectPosToMap();
	void PrintMap();
	void Release();
	void CursorMove(int MaxSize);
	void CursorSelectMenu();
	void ResetCursorPos() { m_Cursor = { 0,0 }; }
	void PrintDeathMenu();
	void SetKeepPlayingTrue() { KeepPlaying = true; }
	bool IsKeepPlaying() { return KeepPlaying; }
	void Shopping();

private:
	bool m_Map[MAP_HEIGHT][MAP_WIDTH];
	Monster* m_pMonster;
	Player* _player;
	PosInfo m_Cursor;
	bool KeepPlaying;
	Arrow* _arrow;
	Shop* _shop;
};

