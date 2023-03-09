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
	// �÷��̾� ������Ʈ
	if (!m_pPlayer)
	{
		m_pPlayer = new Player;
		m_pPlayer->Init();
	}

	m_pPlayer->Update();
	

	//���� ������Ʈ
	if (!m_pMonster)
	{
		m_pMonster = new Monster;
		m_pMonster->Init();
	}

	m_pMonster->Update();


	// �Ѿ� ������Ʈ
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
	// ��� ����
	Rectangle(m_DC, 0, 0, WINCX, WINCY);
	// �÷����� ����
	Rectangle(m_DC, PLAYZONELEFT, PLAYZONETOP, PLAYZONERIGHT, PLAYZONEBOTTOM);
	
	// �÷��̾� ����
	m_pPlayer->Render(m_DC);

	// ���� ����
	m_pMonster->Render(m_DC);
	// �Ѿ� ����
	for (auto& it : m_BulletList)
		it->Render(m_DC);
	
}

void MainGame::Release()
{
	// �÷��̾� ����Ʈ
	Safe_Delete<Object*>(m_pPlayer);

	// �Ѿ� ����Ʈ
	for_each(m_BulletList.begin(), m_BulletList.end(), Safe_Delete<Object*>);

	ReleaseDC(g_hWnd, m_DC);
}
