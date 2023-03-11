#pragma once
#include "Include.h"

class UI;
class Object
{
public:
	Object();
	virtual ~Object();

public:
	virtual void		Init() PURE;
	virtual int			Update()PURE;
	virtual void		Late_Update()PURE;
	virtual void		Render(HDC hDC)PURE;
	virtual void		Release()PURE;
	virtual void		Get_Acc();

public:
	RECT&		Get_Rect() { return m_tRect; }
	POSINFO&	Get_Pos() { return m_tPos; }
	STATINFO& Get_Stat() { return m_tStat; }
	void		Set_PosDir(float _fX, float _fY, DIRECTION _dir);
	void		Set_Size(float _fCX, float _fCY);

protected:
	void				Update_Rect();

protected:
	STATINFO	m_tStat{ "",1,100,100,10 };
	POSINFO		m_tPos;
	RECT		m_tRect;
	DIRECTION	m_eDir = DIRECTION::DIR_END;
	Vec2 _Vel = {};
	Vec2 _Acc = {};
	bool		OnGround = false;
	
	
};

