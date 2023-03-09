#include "pch.h"
#include "MainGame.h"
#include "Player.h"
#include "Monster.h"

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
	Release();
}

void MainGame::Init()
{
	srand(static_cast<UINT>(time(nullptr)));
	m_DC = GetDC(g_hWnd);

	if (!m_pPlayer)
	{
		m_pPlayer = new Player;
		m_pPlayer->Init();
	}

	dynamic_cast<Player*>(m_pPlayer)->Set_Bullet(&m_BulletList);
}

void MainGame::Update()
{
	// ÇÃ·¹ÀÌ¾î ¾÷µ¥ÀÌÆ®
	if (!m_pPlayer)
	{
		m_pPlayer = new Player;
		m_pPlayer->Init();
	}

	m_pPlayer->Update();
	

	//¸ó½ºÅÍ ¾÷µ¥ÀÌÆ®
	if (!m_pMonster)
	{
		m_pMonster = new Monster;
		m_pMonster->Init();
	}

	m_pMonster->Update();


	// ÃÑ¾Ë ¾÷µ¥ÀÌÆ®
	for (auto it = m_BulletList.begin(); it != m_BulletList.end();)
	{
		(*it)->Update();
		RECT tmp = (*it)->Get_Rect();
		if (tmp.left < PLAYZONELEFT || tmp.top<PLAYZONETOP || tmp.right>PLAYZONERIGHT || tmp.bottom > PLAYZONEBOTTOM)
		{
			Safe_Delete(*it);
			it = m_BulletList.erase(it);
		}
		else
			++it;
	}
}

void MainGame::Render()
{
	// ¹è°æ ·»´õ
	Rectangle(m_DC, 0, 0, WINCX, WINCY);
	// ÇÃ·¹ÀÌÁ¸ ·»´õ
	Rectangle(m_DC, PLAYZONELEFT, PLAYZONETOP, PLAYZONERIGHT, PLAYZONEBOTTOM);
	
	// ÇÃ·¹ÀÌ¾î ·»´õ
	m_pPlayer->Render(m_DC);

	// ¸ó½ºÅÍ ·»´õ
	m_pMonster->Render(m_DC);
	// ÃÑ¾Ë ·»´õ
	for (auto& it : m_BulletList)
		it->Render(m_DC);
	
}

void MainGame::Release()
{
	// ÇÃ·¹ÀÌ¾î µô¸®Æ®
	Safe_Delete<Object*>(m_pPlayer);

	// ÃÑ¾Ë µô¸®Æ®
	for_each(m_BulletList.begin(), m_BulletList.end(), Safe_Delete<Object*>);

	ReleaseDC(g_hWnd, m_DC);
}
