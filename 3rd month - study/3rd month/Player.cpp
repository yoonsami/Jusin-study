#include "pch.h"
#include "Player.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "HpBar.h"
#include "JumpChargeBar.h"

Player::~Player()
{
	Release();
}

void Player::Init()
{
	m_tPos = { WINCX / 2.f, WINCY / 2.f, 50.f, 50.f };

	_Pin.vX = WINCX / 2.f;
	_Pin.vY = 0;

	RopeSize = (m_tPos - _Pin).Get_PosVec().Get_Size();
	FirstHeight = abs(m_tPos.fY - _Pin.vY);
	m_fSpeed = 5.f;

	m_Ui.push_back(new HpBar(this));
	m_Ui.push_back(new JumpChargeBar(this));
	// m_Ui.push_back(new HpBar(this));
	// m_Ui.push_back(new HpBar(this));
}

int Player::Update()
{
	Key_Input();
	Get_Acc();
	for (auto& i : m_Ui)
	{
		i->Update();
	}
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void Player::Late_Update()
{
	for (auto& i : m_Ui)
	{
		i->Late_Update();
	}
}

void Player::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	for (auto& i : m_Ui)
	{
		i->Render(hDC);
	}

	TCHAR		szBuff1[100] = L"";
	TCHAR		szBuff2[100] = L"";
	TCHAR		szBuff3[100] = L"";
	TCHAR		szBuff4[100] = L"";
	TCHAR		szBuff5[100] = L"";

	// wsprintf : 소수점 자리 이하의 출력은 불가능(WinApi에서 제공하는 함수, 모든 서식을 지원하지 않음)
	// wsprintf(szBuff, L"Bullet : %d", m_ObjList[OBJ_BULLET].size());

	// swprintf_s : visual c++에서 제공하는 함수, 모든 서식을 제공
	swprintf_s(szBuff1, L"fX : %f, fY : %f", m_tPos.fX, m_tPos.fY);
	TextOut(hDC, 50, 50, szBuff1, lstrlen(szBuff1));

	swprintf_s(szBuff2, L"vX : %f, vY : %f", _Vel.vX, _Vel.vY);
	TextOut(hDC, 50, 100, szBuff2, lstrlen(szBuff2));

	swprintf_s(szBuff3, L"aX : %f, aY : %f", _Acc.vX, _Acc.vY);
	TextOut(hDC, 50, 150, szBuff3, lstrlen(szBuff3));
	Vec2 tmp = (m_tPos - _Pin).Get_PosVec();
	swprintf_s(szBuff4, L"distance : %f", tmp.Get_Size());
	TextOut(hDC, 50, 200, szBuff4, lstrlen(szBuff4));
	swprintf_s(szBuff5, L"GetAsyncKeyState : %d", GetAsyncKeyState(VK_SPACE));
	TextOut(hDC, 50, 250, szBuff5, lstrlen(szBuff5));
}

void Player::Release()
{
	for_each(m_Ui.begin(), m_Ui.end(), Safe_Delete<Object*>);
}

void Player::Get_Acc()
{
	// 중력 가속도
	_Acc = { 0.f, GRAVITY };

	if(ZPressed)
		_Acc += { 0.f, 2.f * GRAVITY };
	if (OnGround)
		_Acc -= {0.f, GRAVITY};

	if(SetPin)
	{
		Vec2 tmp = (m_tPos - _Pin).Get_PosVec();

		// 중력에 의한 장력
		_Acc.vX += GRAVITY * (-tmp.vX / RopeSize) * (tmp.vY / RopeSize);
		_Acc.vY += -GRAVITY * static_cast<FLOAT>(pow((tmp.vY / RopeSize), 2));
		// 구심력에 의한 장력

		_Acc.vX += static_cast<FLOAT>(pow(_Vel.Get_Size(), 2)) * ((-tmp.vX / RopeSize) / RopeSize);
		_Acc.vY -= static_cast<FLOAT>(pow(_Vel.Get_Size(), 2)) * ((tmp.vY / RopeSize) / RopeSize);
	}

	_Vel += _Acc * DELTATIME;
	//좌표 변화량 계산 후 +=
	m_tPos += (_Vel + (_Vel - (_Acc * DELTATIME))) * DELTATIME * 0.5f;

	// 보정
	if (SetPin) 
	{
		Vec2 tmp = (m_tPos - _Pin).Get_PosVec();
		m_tPos.fX = _Pin.vX + RopeSize * ((tmp.vX) / tmp.Get_Size());
		m_tPos.fY = RopeSize * ((tmp.vY) / tmp.Get_Size());

		if (m_tPos.fY < FirstHeight && m_tPos.fX < _Pin.vX)
		{
			m_tPos.fX = WINCX * 0.5f - 100;
			m_tPos.fY = FirstHeight;

			_Vel = {};
		}
		else if (m_tPos.fY < FirstHeight && m_tPos.fX > _Pin.vX)
		{
			m_tPos.fX = WINCX * 0.5f + 100;
			m_tPos.fY = FirstHeight;

			_Vel = {};
		}
	}

	if (m_tPos.fY + (m_tPos.fCY * 0.5f) > PLAYZONEBOTTOM)
	{
		_Vel.vY = sqrtf(powf(_Vel.vY,2) - 2.f * GRAVITY * (m_tPos.fY + (m_tPos.fCY * 0.5f) - (PLAYZONEBOTTOM)));
		m_tPos.fY = PLAYZONEBOTTOM - (m_tPos.fCY * 0.5f);
		_Vel.vY *= -(PLAYERELASTICITY); // 반발계수 곱해줌
	}

	if (m_tPos.fX + (m_tPos.fCX * 0.5f) > PLAYZONERIGHT)
	{
		m_tPos.fX = PLAYZONERIGHT - (m_tPos.fCX * 0.5f);
		_Vel.vX *= -(PLAYERELASTICITY); // 반발계수 곱해줌
		
	}

	if (m_tPos.fX - (m_tPos.fCX * 0.5f) < PLAYZONELEFT)
	{
		m_tPos.fX = PLAYZONELEFT + (m_tPos.fCX * 0.5f);
		_Vel.vX *= -(PLAYERELASTICITY); // 반발계수 곱해줌
	}

	if (_Vel.vX < 0) m_eDir = DIRECTION::DIR_LEFT;
	else if (_Vel.vX > 0) m_eDir = DIRECTION::DIR_RIGHT;
	else if (_Vel.vX == 0) m_eDir = DIRECTION::DIR_END;

	if (_Vel.vY == 0 && m_tPos.fY == PLAYZONEBOTTOM - (m_tPos.fCY * 0.5f))
		OnGround = true;
	else	OnGround = false;
}

void Player::Key_Input()
{
	if ((GetAsyncKeyState(VK_RIGHT) == (SHORT)0x8000) && !LeftPressed)
	{
		if(!RightPressed)
		{
			_Vel.vX += m_fSpeed;
			RightPressed = true;
		}
		else if (RightPressed && m_eDir == DIRECTION::DIR_LEFT)
		{
			_Vel.vX += m_fSpeed;
			RightPressed = false;
		}
	}
	if ((GetAsyncKeyState(VK_RIGHT) == (SHORT)0x0000) && RightPressed)
	{
		if (m_tPos.fX == PLAYZONERIGHT - (m_tPos.fCX * 0.5f));
		else
		{
			if (m_eDir == DIRECTION::DIR_RIGHT) _Vel.vX -= m_fSpeed;
			else if (m_eDir == DIRECTION::DIR_LEFT) _Vel.vX += m_fSpeed;
		}
		RightPressed = false;
	}

	if ((GetAsyncKeyState(VK_LEFT) == (SHORT)0x8000) && !RightPressed)
	{
		if (!LeftPressed)
		{
			_Vel.vX -= m_fSpeed;
			LeftPressed = true;
		}
		else if (LeftPressed && m_eDir == DIRECTION::DIR_RIGHT)
		{
			_Vel.vX -= m_fSpeed;
			LeftPressed = false;
		}
	}
	if ((GetAsyncKeyState(VK_LEFT) == (SHORT)0x0000) && LeftPressed)
	{
		if (m_tPos.fX == PLAYZONELEFT + (m_tPos.fCX * 0.5f));
		else
		{
			if (m_eDir == DIRECTION::DIR_RIGHT) _Vel.vX -= m_fSpeed;
			else if (m_eDir == DIRECTION::DIR_LEFT) _Vel.vX += m_fSpeed;
		}
			
		LeftPressed = false;
	}

	if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && OnGround)
	{
		JumpCharge += 0.5f;
		SpacePressed = true;
	}
	if ((GetAsyncKeyState(VK_SPACE) == (SHORT)0x0000) && SpacePressed == true)
	{
		
		_Vel.vY -= clamp(JumpCharge, MINJMPPOW, MAXJMPPOW);
		SpacePressed = false;
		JumpCharge = 5.f;
	}

	if ((GetAsyncKeyState('Z') == (SHORT)0x8000) && !ZPressed && !OnGround)
	{
		ZPressed = true;
	}
	if ((GetAsyncKeyState('Z') == (SHORT)0x0000) && ZPressed)
	{
		if(OnGround) ZPressed = false;
	}

	if (GetAsyncKeyState('X') & 0x8000)
	{
		++FireCharge;
		XPressed = true;
	}
	if ((GetAsyncKeyState('X') == (SHORT)0x0000) && XPressed)
	{
		FLOAT BulSize = clamp(FireCharge, MINBULSIZE, MAXBULSIZE);
		m_pBulletList->push_back(AbstractFactory<Bullet>::Create(m_tPos.fX, m_tPos.fY,BulSize,BulSize, DIRECTION::DIR_UP));
		XPressed = false;
		FireCharge = 0;
	}
}