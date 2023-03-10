#pragma once


class Player;
class MainGame
{
public:
	MainGame();
	~MainGame();

public:
	void	Init();
	int		Update();
	void	Render();
	void	Release();

private:
	HDC			m_DC = {};
	RECT		m_startMenu = { 200,200,600,300 };
	Player*		m_pPlayer = nullptr;
};

