#include "pch.h"
#include "MainGame.h"
#include "Player.h"
#include "Monster.h"
#include "AbstractFactory.h"
#include "Memento.h"

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

	m_objList[CT_PLAYER].push_back(AbstractFactory<Player>::Create());
	dynamic_cast<Player*>(m_objList[CT_PLAYER].front())->Set_Bullet(&m_objList[CT_BULLET]);

	m_objList[CT_MONSTER].push_back(AbstractFactory<Monster>::Create());
	dynamic_cast<Monster*>(m_objList[CT_MONSTER].back())->Set_Bullet(&m_objList[CT_BULLET]);
}

void MainGame::Update()
{
	++m_iFPS;

	/*if(m_objList[CT_MONSTER].size() == 0)
	{
		m_objList[CT_MONSTER].push_back(AbstractFactory<Monster>::Create());
		dynamic_cast<Monster*>(m_objList[CT_MONSTER].front())->Set_Bullet(&m_objList[CT_BULLET]);
	}*/

	if (!PlayerDead) 
	{
		for (size_t i = 0; i < CT_END; ++i)
		{
			for (auto it = m_objList[i].begin(); it != m_objList[i].end(); )
			{
				int Result = (*it)->Update();
				if (Result == OBJ_DEAD)
				{
					if (i == CT_MONSTER)
					{
						POSINFO& tmp = (*it)->Get_Pos();
						if (tmp.fCX > 35.f)
						{
							m_objList[CT_MONSTER].push_back(AbstractFactory<Monster>::Create
							(tmp.fX, tmp.fY, tmp.fCX, tmp.fCY, DIRECTION::DIR_LEFT, 0.8f, (*it)->Get_Vel()));
							dynamic_cast<Monster*>(m_objList[CT_MONSTER].back())->Set_Bullet(&m_objList[CT_BULLET]);
							m_objList[CT_MONSTER].push_back(AbstractFactory<Monster>::Create
							(tmp.fX, tmp.fY, tmp.fCX, tmp.fCY, DIRECTION::DIR_RIGHT, 0.8f, (*it)->Get_Vel()));
							dynamic_cast<Monster*>(m_objList[CT_MONSTER].back())->Set_Bullet(&m_objList[CT_BULLET]);
						}
					}
					Safe_Delete<Object*>(*it);
					it = m_objList[i].erase(it);
				}
				else ++it;
			}
		}
	}
	if (PlayerDead)
	{
		NowObjList = (caretaker.Update());
	}
		
}

void MainGame::Late_Update()
{
	if(!PlayerDead)
	{
		BOOL bCollide = FALSE;

		for (size_t i = 0; i < CT_END; ++i)
		{
			for (auto it = m_objList[i].begin(); it != m_objList[i].end(); ++it)
			{
				(*it)->Late_Update();
			}
		}

		if (!(m_objList[CT_PLAYER].front()->IS_Invincible()))
		{
			for (auto i : m_objList[CT_MONSTER])
			{
				bCollide = Collider::IntersectWith(m_objList[CT_PLAYER].front()->Get_Rect(), i->Get_Rect(), m_objList[CT_PLAYER].front()->Get_Figure(), i->Get_Figure());
				if (bCollide)
				{
					m_objList[CT_PLAYER].front()->OnAttacked(*i);
					dynamic_cast<Player*>(m_objList[CT_PLAYER].front())->Set_Invincible();
					if (dynamic_cast<Player*>(m_objList[CT_PLAYER].front())->Is_Dead())
					{
						PlayerDead = true;

					}
				}
			}
		}

		if (m_dwTime1 + 500 < GetTickCount64())
		{
			caretaker.Push_back(CreateMemento());
		}

		if(PlayerDead)
		{
			for (size_t i = 0; i < CT_END; ++i)
			{
				for_each(m_objList[i].begin(), m_objList[i].end(), Safe_Delete<Object*>);
			}
			caretaker.Init();
			NowObjList = (caretaker.Update());
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


	// ��� ����
	Rectangle(m_DC, 0, 0, WINCX, WINCY);
	// �÷����� ����
	Rectangle(m_DC, PLAYZONELEFT, PLAYZONETOP, PLAYZONERIGHT, PLAYZONEBOTTOM);
	
	if(!PlayerDead)
	{
		for (size_t i = 0; i < CT_END; ++i)
		{
			for (auto it = m_objList[i].begin(); it != m_objList[i].end(); ++it)
			{
				(*it)->Render(m_DC);
			}
		}
		// ���ڿ� ��� �Լ�

		TCHAR		szBuff[32] = L"";

		// wsprintf : �Ҽ��� �ڸ� ������ ����� �Ұ���(WinApi���� �����ϴ� �Լ�, ��� ������ �������� ����)
		// wsprintf(szBuff, L"Bullet : %d", m_ObjList[OBJ_BULLET].size());

		// swprintf_s : visual c++���� �����ϴ� �Լ�, ��� ������ ����
		swprintf_s(szBuff, L"Bullet : %d", m_objList[CT_BULLET].size());
		// szBuff�� "Bullet : %d" �� ����

		// TextOut(����� dc, ����� x��ǥ, ����� y��ǥ, ����� ���ڿ��� �ּ�, ����� ���ڿ��� ũ��)
		TextOut(m_DC, 50, 25, szBuff, lstrlen(szBuff));

		// DrawText(����� dc, ����� ���ڿ��� �ּ�, ���ڿ��� ũ��, RECT �ּ�, ���� ����)
		// RECT rc{ 50, 50, 100, 100 };
		// DrawText(m_DC, szBuff, lstrlen(szBuff), &rc, DT_CENTER);
	}
	if (PlayerDead)
	{
		for (size_t i = 0; i < CT_END; ++i)
		{
			for (auto it = NowObjList[i].begin(); it != NowObjList[i].end(); ++it)
			{
				(*it)->Render(m_DC);
			}
		}

	}

}

void MainGame::Release()
{

	for (size_t i = 0; i < CT_END; ++i)
	{
		for_each(m_objList[i].begin(), m_objList[i].end(), Safe_Delete<Object*>);
	}

	ReleaseDC(g_hWnd, m_DC);
}

Memento* MainGame::CreateMemento()
{
	return new Memento(m_objList);
}
