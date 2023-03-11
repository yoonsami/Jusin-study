#include "pch.h"
#include "Object.h"

Object::Object()
{
	ZeroMemory(&m_tPos, sizeof(POSINFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}

Object::~Object()
{

}

void Object::Update_Rect(void)
{
	m_tRect.left	= static_cast<LONG>(m_tPos.fX - (m_tPos.fCX * 0.5f));
	m_tRect.top		= static_cast<LONG>(m_tPos.fY - (m_tPos.fCY * 0.5f));
	m_tRect.right	= static_cast<LONG>(m_tPos.fX + (m_tPos.fCX * 0.5f));
	m_tRect.bottom	= static_cast<LONG>(m_tPos.fY + (m_tPos.fCY * 0.5f));
}

void Object::Get_Acc()
{
	_Acc = { 0.f, GRAVITY };

	_Vel += _Acc * DELTATIME;
	//��ǥ ��ȭ�� ��� �� +=
	m_tPos += (_Vel + (_Vel - (_Acc * DELTATIME))) * DELTATIME * 0.5f;

	if (m_tPos.fY + (m_tPos.fCY * 0.5f) > PLAYZONEBOTTOM)
	{
		_Vel.vY = sqrtf(powf(_Vel.vY, 2) - 2.f * GRAVITY * (m_tPos.fY + (m_tPos.fCY * 0.5f) - (PLAYZONEBOTTOM)));
		m_tPos.fY = PLAYZONEBOTTOM - (m_tPos.fCY * 0.5f);
		_Vel.vY *= -(ELASTICITY); // �ݹ߰�� ������
	}

	if (m_tPos.fX + (m_tPos.fCX * 0.5f) > PLAYZONERIGHT)
	{
		m_tPos.fX = PLAYZONERIGHT - (m_tPos.fCX * 0.5f);
		_Vel.vX *= -(ELASTICITY); // �ݹ߰�� ������

	}

	if (m_tPos.fX - (m_tPos.fCX * 0.5f) < PLAYZONELEFT)
	{
		m_tPos.fX = PLAYZONELEFT + (m_tPos.fCX * 0.5f);
		_Vel.vX *= -(ELASTICITY); // �ݹ߰�� ������
	}

	if (_Vel.vX < 0) m_eDir = DIRECTION::DIR_LEFT;
	else if (_Vel.vX > 0) m_eDir = DIRECTION::DIR_RIGHT;
	else if (_Vel.vX == 0) m_eDir = DIRECTION::DIR_END;

	if (_Vel.vY == 0 && m_tPos.fY == PLAYZONEBOTTOM - (m_tPos.fCY * 0.5f))
		OnGround = true;
	else	OnGround = false;
}


void Object::Set_PosDir(float _fX, float _fY, DIRECTION _dir)
{
	m_tPos.fX = _fX;
	m_tPos.fY = _fY;
	m_eDir = _dir;
}

void Object::Set_Size(float _fCX, float _fCY)
{
	m_tPos.fCX = _fCX;
	m_tPos.fCY = _fCY;
}
