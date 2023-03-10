#include "pch.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	m_tInfo = { WINCX / 2.f- 100,100,50.f,50.f };
	_Pin.vX = WINCX / 2.f;
	_Pin.vY = 0;

	RopeSize = (m_tInfo - _Pin).Get_PosVec().Get_Size();
	FirstHeight = abs(m_tInfo.fY - _Pin.vY);
}

int Player::Update()
{
	Key_Input();
	Get_Acc();
	Set_Rect();
	return 0;
}

void Player::Render(HDC hDC)
{
	MoveToEx(hDC, static_cast<INT>(m_tInfo.fX), static_cast<INT>(m_tInfo.fY),nullptr);
	LineTo(hDC, static_cast<INT>(_Pin.vX), static_cast<INT>(_Pin.vY));
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	TCHAR		szBuff1[100] = L"";
	TCHAR		szBuff2[100] = L"";
	TCHAR		szBuff3[100] = L"";
	TCHAR		szBuff4[100] = L"";
	TCHAR		szBuff5[100] = L"";

	// wsprintf : 소수점 자리 이하의 출력은 불가능(WinApi에서 제공하는 함수, 모든 서식을 지원하지 않음)
	// wsprintf(szBuff, L"Bullet : %d", m_ObjList[OBJ_BULLET].size());

	// swprintf_s : visual c++에서 제공하는 함수, 모든 서식을 제공
	swprintf_s(szBuff1, L"fX : %f, fY : %f", m_tInfo.fX,m_tInfo.fY);
	TextOut(hDC, 50, 50, szBuff1, lstrlen(szBuff1));

	swprintf_s(szBuff2, L"vX : %f, vY : %f", _Vel.vX, _Vel.vY);
	TextOut(hDC, 50, 100, szBuff2, lstrlen(szBuff2));

	swprintf_s(szBuff3, L"aX : %f, aY : %f", _Acc.vX, _Acc.vY);
	TextOut(hDC, 50, 150, szBuff3, lstrlen(szBuff3));
	Vec2 tmp = (m_tInfo - _Pin).Get_PosVec();
	swprintf_s(szBuff4, L"distance : %f", tmp.Get_Size());
	TextOut(hDC, 50, 200, szBuff4, lstrlen(szBuff4));
	swprintf_s(szBuff5, L"InitDist : %f", RopeSize);
	TextOut(hDC, 50, 250, szBuff5, lstrlen(szBuff5));
	
}

void Player::Release()
{
}

void Player::Key_Input()
{
	/*if (GetAsyncKeyState(VK_LEFT) & 0x8001)
		_Vel.vX += -2.f;*/
	/*if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		_Vel.vX += -2.f;*/
	/*if (GetAsyncKeyState(VK_LEFT) == 0x0000)
		_Vel.vX += -2.f;
	if (GetAsyncKeyState(VK_LEFT) == 0x0001)
		_Vel.vX += -2.f;*/
	//if (GetAsyncKeyState(VK_LEFT) & 0x0000)
	//	_Vel.vX -= -2.f;

	//if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	//	_Vel.vX += 2.f;
	//if (GetAsyncKeyState(VK_RIGHT) & 0x0000)
	//	_Vel.vX -= 2.f;
}

void Player::Set_Rect()
{
	m_tRect.left = static_cast<LONG>(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = static_cast<LONG>(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = static_cast<LONG>(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = static_cast<LONG>(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void Player::Get_Acc()
{
	float dt = 1.0f;
	// 중력 가속도
	_Acc = { 0.f, 1.f };

	Vec2 tmp = (m_tInfo - _Pin).Get_PosVec();

	// 중력에 의한 장력
	// FLOAT f_Theta = tmp.Get_Theta();
	// _Acc.vX += 1.f * sin(f_Theta - PI * 0.5f) * cos(f_Theta - PI * 0.5f);
	// _Acc.vY += -1.f * static_cast<FLOAT>(pow(cos(f_Theta - PI * 0.5f),2));
	// // 구심력에 의한 장력

	// _Acc.vX += static_cast<FLOAT>(pow(_Vel.Get_Size(), 2)) * sin(f_Theta - PI * 0.5f) / f_Size;
	// _Acc.vY -= static_cast<FLOAT>(pow(_Vel.Get_Size(), 2)) * cos(f_Theta - PI * 0.5f) / f_Size;
	
	// 중력에 의한 장력
	_Acc.vX += 1.f * (-tmp.vX / RopeSize) * (tmp.vY / RopeSize);
	_Acc.vY += -1.f * static_cast<FLOAT>(pow((tmp.vY / RopeSize),2));
	// 구심력에 의한 장력

	_Acc.vX += static_cast<FLOAT>(pow(_Vel.Get_Size(), 2)) * ((-tmp.vX / RopeSize) / RopeSize);
	_Acc.vY -= static_cast<FLOAT>(pow(_Vel.Get_Size(), 2)) * ((tmp.vY / RopeSize) / RopeSize);

	_Vel += _Acc * dt;
	//좌표 변화량 계산 후 +=
	m_tInfo += (_Vel + (_Vel - (_Acc * dt)) ) * dt * 0.5f ;

	// 보정
	tmp = (m_tInfo - _Pin).Get_PosVec();
	m_tInfo.fX = _Pin.vX + RopeSize * ((tmp.vX) / tmp.Get_Size());
	m_tInfo.fY = RopeSize * ((tmp.vY) / tmp.Get_Size());

	if (m_tInfo.fY < FirstHeight && m_tInfo.fX < _Pin.vX)
	{
		m_tInfo.fX = WINCX / 2.f - 100;
		m_tInfo.fY = FirstHeight;

		_Vel = {};
	}
	else if(m_tInfo.fY < FirstHeight && m_tInfo.fX > _Pin.vX)
	{
		m_tInfo.fX = WINCX / 2.f + 100;
		m_tInfo.fY = FirstHeight;

		_Vel = {};
	}
	
}
