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

	m_fSpeed = 10.f;
}

int Player::Update()
{
	Key_Input();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void Player::Late_Update()
{

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
		m_pBulletList->push_back(AbstractFactory<Bullet>::Create(m_tInfo.fX, m_tInfo.fY, DIRECTION::DIR_UP));
		m_pBulletList->push_back(AbstractFactory<Bullet>::Create(m_tInfo.fX, m_tInfo.fY, DIRECTION::DIR_LU));
		m_pBulletList->push_back(AbstractFactory<Bullet>::Create(m_tInfo.fX, m_tInfo.fY, DIRECTION::DIR_RU));
	}

	if (GetAsyncKeyState('W'))
		m_pBulletList->push_back(AbstractFactory<Bullet>::Create(m_tInfo.fX, m_tInfo.fY, DIRECTION::DIR_UP));
	if (GetAsyncKeyState('A'))
		m_pBulletList->push_back(AbstractFactory<Bullet>::Create(m_tInfo.fX, m_tInfo.fY, DIRECTION::DIR_LEFT));
	if (GetAsyncKeyState('S'))
		m_pBulletList->push_back(AbstractFactory<Bullet>::Create(m_tInfo.fX, m_tInfo.fY, DIRECTION::DIR_DOWN));
	if (GetAsyncKeyState('D'))
		m_pBulletList->push_back(AbstractFactory<Bullet>::Create(m_tInfo.fX, m_tInfo.fY, DIRECTION::DIR_RIGHT));


}