#pragma once
#include "define.h"

class Player;
class Field;

class Game
{
public:
	Game();
	~Game();

public:
	void Init();
	void Update();
	void Render();
	void Release();
	void CursorMove(int MaxSize);
	void CursorSelectMenu();
	void CreatePlayer();
	void GoField();

	bool IsKeepPlaying() { return KeepPlaying; }
	void ResetCursorPos() { m_Cursor = { 0,0 }; }
public:
	static float WorldGravity;
	static float WorldSpeed;
	static float COR;
private:
	Player* m_pPlayer;
	Player* tmp;
	const char* Menu[MAINMENU];
	PosInfo m_Cursor;
	bool KeepPlaying;
	Field* m_pField;
};

