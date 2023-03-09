#include "pch.h"
#include "Player.h"
#include "Bullet.h"

Player::~Player()
{
	Release();
}

void Player::Init()
{
	m_tInfo = { WINCX / 2.f, WINCY / 2.f, 100.f, 100.f };

	m_fSpeed = 10.f;
}

void Player::Update()
{
	Key_Input();

	__super::Update_Rect();


}

void Player::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void Player::Release()
{
}

void Player::Key_Input()
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_eDir = DIRECTION::DIR_RIGHT;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		m_eDir = DIRECTION::DIR_LEFT;
	}

	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
		m_eDir = DIRECTION::DIR_UP;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
		m_eDir = DIRECTION::DIR_DOWN;
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		m_pBulletList->push_back(Create_Bullet(DIRECTION::DIR_UP));
		m_pBulletList->push_back(Create_Bullet(DIRECTION::DIR_LU));
		m_pBulletList->push_back(Create_Bullet(DIRECTION::DIR_RU));
	}


}

Object* Player::Create_Bullet(DIRECTION _dir)
{
	Object* bullet = new Bullet;
	bullet->Init();
	dynamic_cast<Bullet*>(bullet)->Set_PosDir(m_tInfo.fX, m_tInfo.fY - (m_tInfo.fCY / 2.f), _dir);
	return bullet;
}
