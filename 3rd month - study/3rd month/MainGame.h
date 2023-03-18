#pragma once
#include "Include.h"
#include "CareTaker.h"

class Object;
class MainGame
{
public:
	MainGame();
	~MainGame();

public:
	void Init();
	void Update();
	void Late_Update();
	void Render();
	void Release();
	
public:
	Memento* CreateMemento();

private:
	HDC				m_DC = nullptr;
	list<Object*>	m_objList[CT_END];
	DWORD64			m_dwTime1 = GetTickCount64();
	DWORD64			m_dwTime = GetTickCount64();
	int				m_iFPS = 0;
	TCHAR			m_szFPS[32];
	CareTaker		caretaker;
	bool			PlayerDead = false;
	list<Object*>*	NowObjList;
};

// 추상 팩토리 패턴
// 미사일로 몬스터 죽이기
// 충돌처리 함수 (intersectrect)

// 