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

void Object::Set_PosDir(float _fX, float _fY, DIRECTION _dir)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_eDir = _dir;
}
