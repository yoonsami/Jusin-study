#pragma once
#include "Include.h"

class UI;
class Object
{
public:
	Object(INT _ObjectType);
	Object(const Object& player);
	virtual ~Object();

public:
	virtual void		Init() PURE;
	virtual int			Update()PURE;
	virtual void		Late_Update()PURE;
	virtual void		Render(HDC hDC)PURE;
	virtual void		Release()PURE;
	virtual void		Get_Acc();
	virtual void		OnAttacked(Object& Attacker);
	virtual void		Set_Att(FLOAT Att) { m_tStat.fAtt = Att; }

public:
	RECT&		Get_Rect() { return m_tRect; }
	POSINFO&	Get_Pos() { return m_tPos; }
	STATINFO&	Get_Stat() { return m_tStat; }
	void		Set_PosDir(float _fX, float _fY, DIRECTION _dir);
	void		Set_Size(float _fCX, float _fCY);
	FIGURETYPE	Get_Figure() { return m_eFigure; }
	void		Set_Dead() { m_bDead = true; }
	bool		Set_Vel(const Vec2& vel) { _Vel = vel; }
	Vec2&		Get_Vel() { return _Vel; }
	DIRECTION	Get_Direction() { return m_eDir; }
	BOOL		IS_Invincible() { return m_bInvincible; }
protected:
	void				Update_Rect();
protected:
	INT			m_iObjectType;
	STATINFO	m_tStat{ "",1,100,100,10 };
	POSINFO		m_tPos;
	RECT		m_tRect;
	DIRECTION	m_eDir = DIRECTION::DIR_END;
	Vec2		_Vel = {};
	Vec2		_Acc = {};
	bool		m_bInvincible = false;
	bool		OnGround = false;
	bool		m_bDead = false;
	FIGURETYPE	m_eFigure = FIGURETYPE::FT_RECT;
	
};

