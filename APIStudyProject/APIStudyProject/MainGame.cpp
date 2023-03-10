#include "pch.h"
#include "MainGame.h"
#include "define.h"
#include "Player.h"

MainGame::MainGame()
{

}

MainGame::~MainGame()
{
	Release();
}

void MainGame::Init()
{
	m_DC = GetDC(g_hWnd);
	if (!m_pPlayer)
	{
		m_pPlayer = new Player;
		m_pPlayer->Init();
	}
		
}

int MainGame::Update()
{
	m_pPlayer->Update();
	return 0;
}

void MainGame::Render()
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY);
	m_pPlayer->Render(m_DC);
}

void MainGame::Release()
{
	Safe_Delete<Player*>(m_pPlayer);
	ReleaseDC(g_hWnd, m_DC);
}
