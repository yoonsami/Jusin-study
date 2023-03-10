#pragma once
#include "define.h"

class Player
{
public:
	Player();
	~Player();

public:
	void Init();
	int Update();
	void Render(HDC hDC);
	void Release();
	void Key_Input();
	void Set_Rect();
	void Get_Acc();

private:
	INFO m_tInfo = {};
	RECT m_tRect = {};
	Vec2 _Vel = {};
	Vec2 _Acc = {};
	Vec2 _Pin = {};
};

