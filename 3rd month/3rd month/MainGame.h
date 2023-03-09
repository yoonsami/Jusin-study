#pragma once
#include "define.h"


class Object;
class MainGame
{
public:
	MainGame();
	~MainGame();

public:
	void Init();
	void Update();
	void Render();
	void Release();
	

private:
	HDC				m_DC = {};
	Object*			m_pPlayer = nullptr;
	Object*			m_pMonster = nullptr;
	list<Object*>	m_BulletList;
};

