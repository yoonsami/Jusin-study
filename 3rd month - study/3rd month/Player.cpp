#include "pch.h"
#include "Player.h"
#include "Bullet.h"
#include "AbstractFactory.h"

Player::~Player()
{
	Release();
}

void Player::Init()
{
	m_tInfo = { WINCX / 2.f, WINCY / 2.f, 100.f, 100.f };

	_Pin.vX = WINCX / 2.f;
	_Pin.vY = 0;

	RopeSize = (m_tInfo - _Pin).Get_PosVec().Get_Size();
	FirstHeight = abs(m_tInfo.fY - _Pin.vY);
	m_fSpeed = 5.f;
}

int Player::Update()
{
	Key_Input();
	Get_Acc();
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void Player::Late_Update()
{

}

void Player::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	TCHAR		szBuff1[100] = L"";
	TCHAR		szBuff2[100] = L"";
	TCHAR		szBuff3[100] = L"";
	TCHAR		szBuff4[100] = L"";
	TCHAR		szBuff5[100] = L"";

	// wsprintf : 소수점 자리 이하의 출력은 불가능(WinApi에서 제공하는 함수, 모든 서식을 지원하지 않음)
	// wsprintf(szBuff, L"Bullet : %d", m_ObjList[OBJ_BULLET].size());

	// swprintf_s : visual c++에서 제공하는 함수, 모든 서식을 제공
	swprintf_s(szBuff1, L"fX : %f, fY : %f", m_tInfo.fX, m_tInfo.fY);
	TextOut(hDC, 50, 50, szBuff1, lstrlen(szBuff1));

	swprintf_s(szBuff2, L"vX : %f, vY : %f", _Vel.vX, _Vel.vY);
	TextOut(hDC, 50, 100, szBuff2, lstrlen(szBuff2));

	swprintf_s(szBuff3, L"aX : %f, aY : %f", _Acc.vX, _Acc.vY);
	TextOut(hDC, 50, 150, szBuff3, lstrlen(szBuff3));
	Vec2 tmp = (m_tInfo - _Pin).Get_PosVec();
	swprintf_s(szBuff4, L"distance : %f", tmp.Get_Size());
	TextOut(hDC, 50, 200, szBuff4, lstrlen(szBuff4));
	swprintf_s(szBuff5, L"GetAsyncKeyState : %d", GetAsyncKeyState(VK_UP));
	TextOut(hDC, 50, 250, szBuff5, lstrlen(szBuff5));
}

void Player::Release()
{
}

void Player::Get_Acc()
{
	// 중력 가속도
	_Acc = { 0.f, GRAVITY };

	if (OnGround)
		_Acc -= {0.f, GRAVITY};

	if(SetPin)
	{
		Vec2 tmp = (m_tInfo - _Pin).Get_PosVec();

		// 중력에 의한 장력
		_Acc.vX += GRAVITY * (-tmp.vX / RopeSize) * (tmp.vY / RopeSize);
		_Acc.vY += -GRAVITY * static_cast<FLOAT>(pow((tmp.vY / RopeSize), 2));
		// 구심력에 의한 장력

		_Acc.vX += static_cast<FLOAT>(pow(_Vel.Get_Size(), 2)) * ((-tmp.vX / RopeSize) / RopeSize);
		_Acc.vY -= static_cast<FLOAT>(pow(_Vel.Get_Size(), 2)) * ((tmp.vY / RopeSize) / RopeSize);
	}

	_Vel += _Acc * DELTATIME;
	//좌표 변화량 계산 후 +=
	m_tInfo += (_Vel + (_Vel - (_Acc * DELTATIME))) * DELTATIME * 0.5f;

	// 보정
	if (SetPin) 
	{
		Vec2 tmp = (m_tInfo - _Pin).Get_PosVec();
		m_tInfo.fX = _Pin.vX + RopeSize * ((tmp.vX) / tmp.Get_Size());
		m_tInfo.fY = RopeSize * ((tmp.vY) / tmp.Get_Size());

		if (m_tInfo.fY < FirstHeight && m_tInfo.fX < _Pin.vX)
		{
			m_tInfo.fX = WINCX * 0.5f - 100;
			m_tInfo.fY = FirstHeight;

			_Vel = {};
		}
		else if (m_tInfo.fY < FirstHeight && m_tInfo.fX > _Pin.vX)
		{
			m_tInfo.fX = WINCX * 0.5f + 100;
			m_tInfo.fY = FirstHeight;

			_Vel = {};
		}
	}

	if (m_tInfo.fY + (m_tInfo.fCY / 2.f) > PLAYZONEBOTTOM)
	{
		_Vel.vY = static_cast<FLOAT>(sqrt(2.f * GRAVITY * m_tInfo.fY + ((m_tInfo.fCY * 0.5f) - PLAYZONEBOTTOM)));
		m_tInfo.fY = PLAYZONEBOTTOM - (m_tInfo.fCY * 0.5f);
		_Vel.vY *= -ELASTICITY; // 반발계수 곱해줌
	}

	

	if (_Vel.vY == 0 && m_tInfo.fY == PLAYZONEBOTTOM - (m_tInfo.fCY * 0.5f))
		OnGround = true;
	else	OnGround = false;
}

void Player::Key_Input()
{
	if ((GetAsyncKeyState(VK_RIGHT) == (SHORT)0x8000) && RightPressed == false)
	{
		_Vel.vX += m_fSpeed;
		m_eDir = DIRECTION::DIR_RIGHT;
		RightPressed = true;
	}
	if ((GetAsyncKeyState(VK_RIGHT) == (SHORT)0x0000) && RightPressed == true)
	{
		_Vel.vX -= m_fSpeed;
		RightPressed = false;
	}

	if ((GetAsyncKeyState(VK_LEFT) == (SHORT)0x8000) && LeftPressed == false)
	{
		_Vel.vX -= m_fSpeed;
		m_eDir = DIRECTION::DIR_LEFT;
		LeftPressed = true;
	}
	if ((GetAsyncKeyState(VK_LEFT) == (SHORT)0x0000) && LeftPressed == true)
	{
		_Vel.vX += m_fSpeed;
		LeftPressed = false;
	}
		

	if ((GetAsyncKeyState(VK_UP) == (SHORT)0x8000) && UpPressed == false)
	{
		_Vel.vY -= JUMPPOWER;
		m_eDir = DIRECTION::DIR_UP;
		UpPressed = true;
	}
	if ((GetAsyncKeyState(VK_UP) == (SHORT)0x0000) && UpPressed == true)
		UpPressed = false;

	if (GetAsyncKeyState(VK_SPACE))
	{
		m_pBulletList->push_back(AbstractFactory<Bullet>::Create(m_tInfo.fX, m_tInfo.fY, DIRECTION::DIR_UP));
		m_pBulletList->push_back(AbstractFactory<Bullet>::Create(m_tInfo.fX, m_tInfo.fY, DIRECTION::DIR_LU));
		m_pBulletList->push_back(AbstractFactory<Bullet>::Create(m_tInfo.fX, m_tInfo.fY, DIRECTION::DIR_RU));
	}
}