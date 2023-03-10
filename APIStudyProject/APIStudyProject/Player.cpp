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
	// 중력 가속도
	_Acc = { 0.f, 1.f };

	Vec2 tmp = (m_tInfo - _Pin).Get_PosVec();
	FLOAT f_Size = tmp.Get_Size();
	// 중력에 의한 장력
	// FLOAT f_Theta = tmp.Get_Theta();
	// _Acc.vX += 1.f * sin(f_Theta - PI * 0.5f) * cos(f_Theta - PI * 0.5f);
	// _Acc.vY += -1.f * static_cast<FLOAT>(pow(cos(f_Theta - PI * 0.5f),2));
	// // 구심력에 의한 장력

	// _Acc.vX += static_cast<FLOAT>(pow(_Vel.Get_Size(), 2)) * sin(f_Theta - PI * 0.5f) / f_Size;
	// _Acc.vY -= static_cast<FLOAT>(pow(_Vel.Get_Size(), 2)) * cos(f_Theta - PI * 0.5f) / f_Size;
	
	// 중력에 의한 장력
	_Acc.vX += 1.f * (-tmp.vX / f_Size) * (tmp.vY / f_Size);
	_Acc.vY += -1.f * static_cast<FLOAT>(pow((tmp.vY / f_Size),2));
	// 구심력에 의한 장력

	_Acc.vX += static_cast<FLOAT>(pow(_Vel.Get_Size(), 2)) * ((-tmp.vX / f_Size) / f_Size);
	_Acc.vY -= static_cast<FLOAT>(pow(_Vel.Get_Size(), 2)) * ((tmp.vY / f_Size) / f_Size);

	_Vel += _Acc;
	//좌표 변화량 계산 후 +=
	m_tInfo += _Vel;


}
