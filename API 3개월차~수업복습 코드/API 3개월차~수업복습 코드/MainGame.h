#pragma once
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Init();
	void Update();
	void Render();
	void Late_Update();
	void Release();
	
private:
	HDC		m_DC = nullptr;
};

