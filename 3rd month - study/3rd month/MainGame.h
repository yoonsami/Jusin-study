#pragma once
#include "Include.h"


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
	

private:
	HDC				m_DC = {};
	list<Object*>	m_objList[OT_END];
	DWORD64			m_dwTime = GetTickCount64();
	int				m_iFPS = 0;
	TCHAR			m_szFPS[32];
};

// �߻� ���丮 ����
// �̻��Ϸ� ���� ���̱�
// �浹ó�� �Լ� (intersectrect)

// 