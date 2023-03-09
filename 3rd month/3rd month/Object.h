#pragma once
#include "define.h"
class Object
{
public:
	Object();
	virtual ~Object();

public:
	virtual void		Init() PURE;
	virtual void		Update()PURE;
	virtual void		Render(HDC hDC)PURE;
	virtual void		Release()PURE;

public:
	RECT& Get_Rect() { return m_tRect; }

protected:
	void		Update_Rect();
	
protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDir = DIRECTION::DIR_END;
	float		m_fSpeed = 0.f;
};

