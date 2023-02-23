#include "PCH.h"
#include "Field.h"
#include "define.h"
#include "Player.h"
#include "Monster.h"
#include "Arrow.h"
#include "Shop.h"

Field::Field() 
	: m_Map{}, m_pMonster(nullptr), _player(nullptr),
	m_Cursor{},KeepPlaying(true),_arrow(nullptr), _shop(nullptr)
{

}

Field::~Field()
{
	Release();
}

void Field::Init(Player* m_pPlayer)
{
	CreateMap();
	_player = m_pPlayer;
	_player->SetPos(0, MAP_HEIGHT - 1);
	
}

void Field::Update()
{
	if(!_player->IsDead())
	{
		if (!m_pMonster) CreateMonster();

		_player->GetAcc();
		m_pMonster->GetAcc();
		if (_arrow)	_arrow->SetArrowPos();

		if (_kbhit())
		{
			char c = _getch();
			if (c == DIRKEY)
			{
				_player->Move();
			}
			else if (c == SPACEBAR)
			{
				_player->Jump();
			}
			else if (c == 'z' || c == 'Z')
			{
				_player->Attack(m_pMonster);
				if (_player->GetPlayerType() == PT_ARCHER)
				{
					if(dynamic_cast<Archer*>(_player)->GetArrowPointer())
						_arrow = (dynamic_cast<Archer*>(_player)->GetArrowPointer());
				}
			}
			else if (c == 'x' || c == 'X')
				Shopping();
			else if (c == ESCAPE)
			{
				KeepPlaying = false;
			}
			else if (c == 'C' || c == 'c')
			{
				_player->ShowInventory();
			}
			else
				while (getchar() != '\n');
		}
		

		if (_arrow && _arrow->GetArrowPos() == m_pMonster->GetPos())
		{
			m_pMonster->OnAttacked(_player);
			SAFE_DELETE(_arrow);
			dynamic_cast<Archer*>(_player)->SetArrowPointerNull();
		}
		if (m_pMonster->IsDead())
		{
			_player->AddMoney(m_pMonster->GetStatInfo()._money);
			SAFE_DELETE(m_pMonster);
		}
	}
	else
	{
		if (_kbhit())
		{
			char c = _getch();
			if (c == DIRKEY)
				CursorMove(2);
			else if (c == ENTER || c == SPACEBAR)
				CursorSelectMenu();
			else
				while (getchar() != '\n');
		}
	}
}

void Field::CreateMonster()
{
	int randValue = rand() % 3 + 1;
	switch (randValue)
	{
	case MT_SLIME:
		m_pMonster = new Slime;
		break;
	case MT_SKELETON:
		m_pMonster = new Skeleton;
		break;
	case MT_ORC:
		m_pMonster = new Orc;
		break;
	}
	m_pMonster->SetPos(static_cast<float>(rand() % MAP_WIDTH), 0);
}

void Field::Render()
{
	system("cls");
	PrintMap();
	if (_player)
		_player->PrintInfo();
	if (m_pMonster)
		m_pMonster->PrintInfo();
	if (_player->IsDead())
	{
		PrintDeathMenu();
	}
}

void Field::SetObjectPosToMap()
{
	
	
	fill(&m_Map[0][0], &m_Map[0][0] + MAP_HEIGHT * MAP_WIDTH, false);
	if(_player)
	{
		_player->CorrectPos();
		m_Map[static_cast<int>(_player->GetPos()._crdY)][static_cast<int>(_player->GetPos()._crdX)] = true;

	}
	if (m_pMonster) 
	{
		m_pMonster->CorrectPos();
		m_Map[static_cast<int>(m_pMonster->GetPos()._crdY)][static_cast<int>(m_pMonster->GetPos()._crdX)] = true;
	}

	if (_arrow)
	{
		if (_arrow->GetArrowPos()._crdX <= 0)
		{
			SAFE_DELETE(_arrow);
			dynamic_cast<Archer*>(_player)->SetArrowPointerNull();
		}
		else if (_arrow->GetArrowPos()._crdX >= MAP_WIDTH - 1)
		{
			SAFE_DELETE(_arrow);
			dynamic_cast<Archer*>(_player)->SetArrowPointerNull();
		}
		else if(_arrow->GetFlyingDistance() == MAX_ARROW)
		{
			SAFE_DELETE(_arrow);
			dynamic_cast<Archer*>(_player)->SetArrowPointerNull();
		}
		if(_arrow)
			m_Map[static_cast<int>(_arrow->GetArrowPos()._crdY)][static_cast<int>(_arrow->GetArrowPos()._crdX)] = true;
	}
}

void Field::PrintMap()
{
	SetObjectPosToMap();
	for (int Height = 0; Height < MAP_HEIGHT; ++Height)
	{
		cout << "■";
		for (int Width = 0; Width < MAP_WIDTH; ++Width)
		{
			if (m_Map[Height][Width])
			{
				if (Height == static_cast<int>(_player->GetPos()._crdY) && Width == static_cast<int>(_player->GetPos()._crdX))
					cout << "○";
				else if (m_pMonster && Height == static_cast<int>(m_pMonster->GetPos()._crdY) && Width == static_cast<int>(m_pMonster->GetPos()._crdX))
					cout << "◈";
				else if (Height == static_cast<int>(_arrow->GetArrowPos()._crdY) && Width == static_cast<int>(_arrow->GetArrowPos()._crdX))
				{
					if (_arrow->GetDirOfArrow() == RIGHT)
						cout << "→";
					else
						cout << "←";
				}
			}
			else
				cout << "　";
		}
		cout << "■" << endl;
	}
	for (int Width = 0; Width < MAP_WIDTH + 2; ++Width)
		cout << "■";
		cout << endl;
		cout << "Z] 공격 SPACE BAR] 점프 X] 마을 C] 인벤토리" << endl;
}

void Field::Release()
{
	SAFE_DELETE(m_pMonster);
	// _player는 Game클래스에서 delete
	SAFE_DELETE(_arrow);
	SAFE_DELETE(_shop);
}

void Field::CreateMap()
{
	/*m_Map[MAP_HEIGHT - 1][0] = WALL;
	int HeightHasWall = 0;
	int randValue = 0;
	for (int i = 1; i < MAP_WIDTH; ++i)
	{
		for (int j = 0; j < MAP_HEIGHT; ++j)
		{
			if (m_Map[j][i - 1] == WALL) HeightHasWall = j;
		}


		if (HeightHasWall == MAP_HEIGHT - 1) randValue = rand() % 2;
		else randValue = rand() & 3 - 1;

		m_Map[HeightHasWall - randValue][i] = WALL;
	}*/
}

void Field::CursorMove(int MaxSize)
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

void Field::CursorSelectMenu()
{
	if (m_Cursor._crdX == 0)
	{
		_player->Resurrect();
		cout << "체력이 완전히 회복됩니다." << endl;
		cout << "소지금을 10퍼센트 잃어버렸습니다." << endl;
		system("pause");
	}
	else if (m_Cursor._crdX == 1)
	{
		KeepPlaying = false;
		SAFE_DELETE(m_pMonster);
		return;
	}
}

void Field::PrintDeathMenu()
{
	cout << "플레이어가 사망했습니다." << endl;
	if (m_Cursor._crdX == 0)
		cout << "■ 부활하기\t□ 종료하기" << endl;
	else if(m_Cursor._crdX == 1)
		cout << "□ 부활하기\t■ 종료하기" << endl;
}

void Field::Shopping()
{
	if (_shop == nullptr)
		_shop = new Shop;

	_shop->Init(_player);

	while (_shop->IsShopping())
	{
		_shop->Update();
		_shop->Render();
	}

	SAFE_DELETE(_shop);
}
