#include "pch.h"
#include "Object.h"

Object::Object(INT _ObjectType) : m_iObjectType(_ObjectType)
{
	ZeroMemory(&m_tPos, sizeof(POSINFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}

Object::Object(const Object& player)
{
	m_tStat = player.m_tStat;
	m_tPos = player.m_tPos;
	m_tRect = player.m_tRect;
	m_eDir = player.m_eDir;
	_Vel = player._Vel;
	_Acc = player._Acc;
	m_bInvincible = player.m_bInvincible;
	OnGround = player.OnGround;
	m_bDead = player.m_bDead;
	m_eFigure = player.m_eFigure;
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
	//ÁÂÇ¥ º¯È­·® °è»ê ÈÄ +=
	m_tPos += (_Vel + (_Vel - (_Acc * DELTATIME))) * DELTATIME * 0.5f;

	if (m_tPos.fY + (m_tPos.fCY * 0.5f) > PLAYZONEBOTTOM)
	{
		_Vel.vY = sqrtf(powf(_Vel.vY, 2) - 2.f * GRAVITY * (m_tPos.fY + (m_tPos.fCY * 0.5f) - (PLAYZONEBOTTOM)));
		m_tPos.fY = PLAYZONEBOTTOM - (m_tPos.fCY * 0.5f);
		_Vel.vY *= -(ELASTICITY); // ¹Ý¹ß°è¼ö °öÇØÁÜ
	}

	if (m_tPos.fX + (m_tPos.fCX * 0.5f) > PLAYZONERIGHT)
	{
		m_tPos.fX = PLAYZONERIGHT - (m_tPos.fCX * 0.5f);
		_Vel.vX *= -(ELASTICITY); // ¹Ý¹ß°è¼ö °öÇØÁÜ

	}

	if (m_tPos.fX - (m_tPos.fCX * 0.5f) < PLAYZONELEFT)
	{
		m_tPos.fX = PLAYZONELEFT + (m_tPos.fCX * 0.5f);
		_Vel.vX *= -(ELASTICITY); // ¹Ý¹ß°è¼ö °öÇØÁÜ
	}

	if (_Vel.vX < 0) m_eDir = DIRECTION::DIR_LEFT;
	else if (_Vel.vX > 0) m_eDir = DIRECTION::DIR_RIGHT;
	else if (_Vel.vX == 0) m_eDir = DIRECTION::DIR_END;

	if (_Vel.vY == 0 && m_tPos.fY == PLAYZONEBOTTOM - (m_tPos.fCY * 0.5f))
		OnGround = true;
	else	OnGround = false;
}


void Object::OnAttacked(Object& Attacker)
{
	m_tStat.fHp -= Attacker.m_tStat.fAtt;
	if (m_tStat.fHp < 0) m_tStat.fHp = 0;
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
