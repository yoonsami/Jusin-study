#include "pch.h"
#include "MainGame.h"
#include "Player.h"
#include "Monster.h"
#include "AbstractFactory.h"

MainGame::MainGame()
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 32);
}

MainGame::~MainGame()
{
	Release();
}

void MainGame::Init()
{
	srand(static_cast<UINT>(time(nullptr)));
	m_DC = GetDC(g_hWnd);

	m_objList[OT_PLAYER].push_back(AbstractFactory<Player>::Create());
	dynamic_cast<Player*>(m_objList[OT_PLAYER].front())->Set_Bullet(&m_objList[OT_BULLET]);

	m_objList[OT_MONSTER].push_back(AbstractFactory<Monster>::Create());
	dynamic_cast<Monster*>(m_objList[OT_MONSTER].front())->Set_Bullet(&m_objList[OT_BULLET]);
}

void MainGame::Update()
{
	++m_iFPS;

	if (m_monsterCreate + 1000 < GetTickCount64())
	{
		if (m_objList[OT_MONSTER].size() == 0)
		{
			m_objList[OT_MONSTER].push_back(AbstractFactory<Monster>::Create());
			for (auto& i : m_objList[OT_MONSTER])
				dynamic_cast<Monster*>(i)->Set_Bullet(&m_objList[OT_BULLET]);
		}
	}
	

	for (size_t i = 0; i < OT_END; ++i)
	{
		for (auto it = m_objList[i].begin(); it != m_objList[i].end(); )
		{
			int Result = (*it)->Update();
			if (Result == OBJ_DEAD)
			{
				if(i == OT_MONSTER)
					m_monsterCreate = GetTickCount64();
				Safe_Delete<Object*>(*it);
				it = m_objList[i].erase(it);
			}
			else ++it;
		}
	}
}

void MainGame::Late_Update()
{
	for (size_t i = 0; i < OT_END; ++i)
	{
		for (auto it = m_objList[i].begin(); it != m_objList[i].end(); ++it)
		{
			(*it)->Late_Update();
		}
	}
}

void MainGame::Render()
{
	if (m_dwTime + 1000 < GetTickCount64())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount64();
	}

	// 배경 렌더
	Rectangle(m_DC, 0, 0, WINCX, WINCY);
	// 플레이존 렌더
	Rectangle(m_DC, PLAYZONELEFT, PLAYZONETOP, PLAYZONERIGHT, PLAYZONEBOTTOM);
	
	for (size_t i = 0; i < OT_END; ++i)
	{
		for (auto it = m_objList[i].begin(); it != m_objList[i].end(); ++it)
		{
			(*it)->Render(m_DC);
		}
	}
	// 문자열 출력 함수

	TCHAR		szBuff[32] = L"";

	// wsprintf : 소수점 자리 이하의 출력은 불가능(WinApi에서 제공하는 함수, 모든 서식을 지원하지 않음)
	// wsprintf(szBuff, L"Bullet : %d", m_ObjList[OBJ_BULLET].size());

	// swprintf_s : visual c++에서 제공하는 함수, 모든 서식을 제공
	swprintf_s(szBuff, L"Bullet : %d", m_objList[OT_BULLET].size());
	// szBuff에 "Bullet : %d" 를 저장
	
	// TextOut(출력할 dc, 출력할 x좌표, 출력할 y좌표, 출력할 문자열의 주소, 출력할 문자열의 크기)
	TextOut(m_DC, 50, 50, szBuff, lstrlen(szBuff));

	// DrawText(출력할 dc, 출력할 문자열의 주소, 문자열의 크기, RECT 주소, 정렬 기준)
	// RECT rc{ 50, 50, 100, 100 };
	// DrawText(m_DC, szBuff, lstrlen(szBuff), &rc, DT_CENTER);


}

void MainGame::Release()
{

	for (size_t i = 0; i < OT_END; ++i)
	{
		for_each(m_objList[i].begin(), m_objList[i].end(), Safe_Delete<Object*>);
	}

	ReleaseDC(g_hWnd, m_DC);
}
