#pragma once
#include "Include.h"
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

public:
	RECT& Get_Rect() { return m_tRect; }
	void Set_PosDir(float _fX, float _fY, DIRECTION _dir);
protected:
	void		Update_Rect();
	
protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDir = DIRECTION::DIR_END;
	float		m_fSpeed = 0.f;
	bool		m_bDead = false;
	bool		m_bInvincible = false;
};

