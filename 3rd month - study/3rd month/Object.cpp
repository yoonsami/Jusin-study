#include "pch.h"
#include "Object.h"

Object::Object()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}

Object::~Object()
{

}

void Object::Update_Rect(void)
{
	m_tRect.left	= static_cast<LONG>(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top		= static_cast<LONG>(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right	= static_cast<LONG>(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom	= static_cast<LONG>(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void Object::Get_Acc()
{
	_Acc = { 0.f, GRAVITY };

	_Vel += _Acc * DELTATIME;
	//ÁÂÇ¥ º¯È­·® °è»ê ÈÄ +=
	m_tInfo += (_Vel + (_Vel - (_Acc * DELTATIME))) * DELTATIME * 0.5f;

	if (m_tInfo.fY + (m_tInfo.fCY / 2.f) > PLAYZONEBOTTOM)
	{
		_Vel.vY = static_cast<FLOAT>(sqrt(2.f * GRAVITY * m_tInfo.fY + ((m_tInfo.fCY * 0.5f) - PLAYZONEBOTTOM)));
		m_tInfo.fY = PLAYZONEBOTTOM - (m_tInfo.fCY * 0.5f);
	}

	_Vel.vY *= -_Vel.vY * ELASTICITY; // ¹Ý¹ß°è¼ö °öÇØÁÜ
	if (_Vel.vY == 0 && m_tInfo.fY == PLAYZONEBOTTOM - (m_tInfo.fCY * 0.5f))
		OnGround = true;
	else	OnGround = false;
}

void Object::Set_PosDir(float _fX, float _fY, DIRECTION _dir)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_eDir = _dir;
}
