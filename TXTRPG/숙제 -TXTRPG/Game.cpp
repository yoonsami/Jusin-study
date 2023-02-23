#include "PCH.h"
#include "Game.h"
#include "define.h"
#include "Player.h"
#include "Field.h"


Game::Game() :m_pPlayer(nullptr),tmp(nullptr),m_pField(nullptr), Menu{"게임 시작", "불러오기", "게임 종료"},m_Cursor{}, KeepPlaying(true)
{

}

Game::~Game()
{
	Release();
}

void Game::Init()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	m_pField = new Field;
}

void Game::Update()
{
	if (_kbhit())
	{
		char c = _getch();
		if (c == DIRKEY)
			CursorMove(MAINMENU);
		else if (c == ENTER || c == SPACEBAR)
			CursorSelectMenu();
		else if (c == ESCAPE)
		{
			KeepPlaying = false;
			return;
		}
		
	}
}

void Game::Render()
{
	system("cls");
	for (int i = 0; i < MAINMENU; ++i)
	{
		if (m_Cursor._crdX == i) cout << "■";
		else cout << "□";

		cout << " " << Menu[i]<<'\t';
	}
	cout << endl;
}

void Game::Release()
{
	SAFE_DELETE(m_pPlayer);
}

void Game::CursorMove(int MaxSize)
{
	char c = _getch();
	switch (c)
	{
	case UP:
		break;
	case DOWN:
		break;
	case LEFT:
		--m_Cursor._crdX;
		if (m_Cursor._crdX < 0) m_Cursor._crdX = 0;
		break;
	case RIGHT:
		++m_Cursor._crdX;
		if (m_Cursor._crdX > MaxSize - 1) m_Cursor._crdX = MaxSize - 1.f;
		break;
	default:
		break;
	}
	
}

void Game::CursorSelectMenu()
{
	if (Menu[static_cast<int>( m_Cursor._crdX)] == "게임 시작")
	{
		if(!m_pPlayer)	CreatePlayer();
		GoField();
	}
	else if (Menu[static_cast<int>(m_Cursor._crdX)] == "불러오기")
	{
		cout << "아직 구현 안함" << endl;
		system("pause");
	}
	else if (Menu[static_cast<int>(m_Cursor._crdX)] == "게임 종료")
	{
		KeepPlaying = false;
		return;
	}
}

void Game::CreatePlayer()
{
	ResetCursorPos();
	
	while (!m_pPlayer)
	{
		system("cls");
		SAFE_DELETE(tmp);
		cout << "직업을 선택해주세요." << endl << endl;
		switch (static_cast<int>(m_Cursor._crdX))
		{
		case 0:
			cout << "■ 기사\t□ 궁수\t□ 마법사" << endl;
			tmp = new Knight;
			break;
		case 1:
			cout << "□ 기사\t■ 궁수\t□ 마법사" << endl;
			tmp = new Archer;
			break;
		case 2:
			cout << "□ 기사\t□ 궁수\t■ 마법사" << endl;
			tmp = new Mage;
			break;
		default:
			break;
		}
		tmp->PrintJobInfo();

		if (_kbhit())
		{
			char c = _getch();
			if (c == DIRKEY)
				CursorMove(3);
			else if (c == ENTER || c == SPACEBAR)
			{
				m_pPlayer = tmp;
				m_pPlayer->SetName();
				tmp = nullptr;
				ResetCursorPos();
			}
			else if (c == ESCAPE)
			{
				ResetCursorPos();
				SAFE_DELETE(tmp);
				return;
			}
		}
	}
}

void Game::GoField()
{
	m_pField->SetKeepPlayingTrue();
	m_pField->Init(m_pPlayer);

	while (m_pField->IsKeepPlaying())
	{
		m_pField->Update();
		m_pField->Render();
	}
}
