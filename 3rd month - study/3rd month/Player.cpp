#include "pch.h"
#include "Player.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "HpBar.h"
#include "JumpChargeBar.h"
#include "ShootingChargeBar.h"

Player::Player() : Creature(CT_PLAYER), m_iPlayerType(0)
{

}
Player::Player(INT _PlayerType) : Creature(CT_PLAYER), m_iPlayerType(_PlayerType)
{

}


Player::Player(const Player& player) :Creature(player), m_iPlayerType(0)
{
	m_pBulletList	= nullptr;
	SpacePressed = player.SpacePressed;
	RightPressed = player.RightPressed;
	LeftPressed = player.LeftPressed;
	ZPressed	= player.ZPressed;
	XPressed	= player.XPressed;
	m_fJumpCharge = player.m_fJumpCharge;
	m_fFireCharge = player.m_fFireCharge;
	m_bFullCharged = player.m_bFullCharged;
	m_InvincibleTimer = GetTickCount64();
	
}

Player::~Player()
{
	Release();
}

void Player::Init()
{
	m_tPos = { WINCX / 2.f, WINCY / 2.f, 50.f, 50.f };

	/*_Pin.vX = WINCX / 2.f;
	_Pin.vY = 0;*/

	/*RopeSize = (m_tPos - _Pin).Get_PosVec().Get_Size();
	FirstHeight = abs(m_tPos.fY - _Pin.vY);*/
	m_fSpeed = 5.f;

	m_eFigure = FIGURETYPE::FT_RECT;

	m_Ui.push_back(new HpBar(this));
	m_Ui.push_back(new JumpChargeBar(this));
	m_Ui.push_back(new ShootingChargeBar(this));
	
}

int Player::Update()
{
	if (m_InvincibleTimer + 1000 < GetTickCount64())
	{
		m_bInvincible = false;

		m_InvincibleTimer = GetTickCount64();
	}

	if(!Is_Dead())
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
	if (m_bInvincible == false)
		Draw_Figure(hDC);
	else
	{
		HPEN hpen;
		HPEN hpenOld;
		hpen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		hpenOld = (HPEN)::SelectObject(hDC, (HGDIOBJ)hpen);
		Draw_Figure(hDC);
		hpen = (HPEN)::SelectObject(hDC, hpenOld);
		::DeleteObject(hpen);

	}

	for (auto& i : m_Ui)
	{
		i->Render(hDC);
	}

	TCHAR		szBuff1[100] = L"";
	TCHAR		szBuff2[100] = L"";
	TCHAR		szBuff3[100] = L"";
	TCHAR		szBuff4[100] = L"";
	TCHAR		szBuff5[100] = L"";

	// wsprintf : ?????? ???? ?????? ?????? ??????(WinApi???? ???????? ????, ???? ?????? ???????? ????)
	// wsprintf(szBuff, L"Bullet : %d", m_ObjList[OBJ_BULLET].size());

	// swprintf_s : visual c++???? ???????? ????, ???? ?????? ????
	swprintf_s(szBuff1, L"fX : %f, fY : %f", m_tPos.fX, m_tPos.fY);
	TextOut(hDC, 50, 50, szBuff1, lstrlen(szBuff1));

	swprintf_s(szBuff2, L"vX : %f, vY : %f", _Vel.vX, _Vel.vY);
	TextOut(hDC, 50, 100, szBuff2, lstrlen(szBuff2));

	swprintf_s(szBuff3, L"aX : %f, aY : %f", _Acc.vX, _Acc.vY);
	TextOut(hDC, 50, 150, szBuff3, lstrlen(szBuff3));
	/*Vec2 tmp = (m_tPos - _Pin).Get_PosVec();
	swprintf_s(szBuff4, L"distance : %f", tmp.Get_Size());
	TextOut(hDC, 50, 200, szBuff4, lstrlen(szBuff4));*/
	swprintf_s(szBuff5, L"GetAsyncKeyState : %d", GetAsyncKeyState(VK_SPACE));
	TextOut(hDC, 50, 250, szBuff5, lstrlen(szBuff5));
}

void Player::Release()
{
	if(m_Ui.size()>0)
		for_each(m_Ui.begin(), m_Ui.end(), Safe_Delete<Object*>);
}

void Player::Get_Acc()
{
	// ???? ??????
	_Acc = { 0.f, GRAVITY };

	if(ZPressed)
		_Acc += { 0.f, 2.f * GRAVITY };
	if (OnGround)
		_Acc -= {0.f, GRAVITY};

	//if(SetPin)
	//{
	//	Vec2 tmp = (m_tPos - _Pin).Get_PosVec();

	//	// ?????? ???? ????
	//	_Acc.vX += GRAVITY * (-tmp.vX / RopeSize) * (tmp.vY / RopeSize);
	//	_Acc.vY += -GRAVITY * static_cast<FLOAT>(pow((tmp.vY / RopeSize), 2));
	//	// ???????? ???? ????

	//	_Acc.vX += static_cast<FLOAT>(pow(_Vel.Get_Size(), 2)) * ((-tmp.vX / RopeSize) / RopeSize);
	//	_Acc.vY -= static_cast<FLOAT>(pow(_Vel.Get_Size(), 2)) * ((tmp.vY / RopeSize) / RopeSize);
	//}

	_Vel += _Acc * DELTATIME;
	//???? ?????? ???? ?? +=
	m_tPos += (_Vel + (_Vel - (_Acc * DELTATIME))) * DELTATIME * 0.5f;

	// ????
	/*if (SetPin)
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
	}*/

	if (m_tPos.fY + (m_tPos.fCY * 0.5f) > PLAYZONEBOTTOM)
	{
		_Vel.vY = sqrtf(powf(_Vel.vY,2) - 2.f * GRAVITY * (m_tPos.fY + (m_tPos.fCY * 0.5f) - (PLAYZONEBOTTOM)));
		m_tPos.fY = PLAYZONEBOTTOM - (m_tPos.fCY * 0.5f);
		_Vel.vY *= -(PLAYERELASTICITY); // ???????? ??????
	}

	if (m_tPos.fX + (m_tPos.fCX * 0.5f) > PLAYZONERIGHT)
	{
		m_tPos.fX = PLAYZONERIGHT - (m_tPos.fCX * 0.5f);
		_Vel.vX *= -(PLAYERELASTICITY); // ???????? ??????
		
	}

	if (m_tPos.fX - (m_tPos.fCX * 0.5f) < PLAYZONELEFT)
	{
		m_tPos.fX = PLAYZONELEFT + (m_tPos.fCX * 0.5f);
		_Vel.vX *= -(PLAYERELASTICITY); // ???????? ??????
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
		m_fJumpCharge += 0.5f;
		SpacePressed = true;
	}
	if ((GetAsyncKeyState(VK_SPACE) == (SHORT)0x0000) && SpacePressed == true)
	{
		
		_Vel.vY -= clamp(m_fJumpCharge, MINJMPPOW, MAXJMPPOW);
		SpacePressed = false;
		m_fJumpCharge = 5.f;
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
		++m_fFireCharge;

		if (m_fFireCharge > 80) m_bFullCharged = true;
		XPressed = true;
	}
	if ((GetAsyncKeyState('X') == (SHORT)0x0000) && XPressed)
	{
		FLOAT BulSize = clamp(m_fFireCharge, MINFIREPOW, MAXFIREPOW);
		m_pBulletList->push_back(AbstractFactory<Bullet>::Create(m_tPos.fX, m_tPos.fY,BulSize,BulSize, DIRECTION::DIR_UP));
		dynamic_cast<Bullet*>(m_pBulletList->back())->Set_FullCharged(m_bFullCharged);
		m_pBulletList->back()->Set_Att(MINBULDAM + Get_ShootChargeRatio() * (MAXBULDAM - MINBULDAM));
		XPressed = false;
		m_fFireCharge = 0;
		m_bFullCharged = false;
	}
}