#pragma once
#include "Include.h"

class CLine;

class CObject
{
public:
	CObject();
	virtual ~CObject();

public:
	virtual void	Init() PURE;
	virtual int		Update() PURE;
	virtual void	Late_Update() PURE;
	virtual void	Render(HDC hDC) PURE;
	virtual void	Release() PURE;

public:
	RECT&		Get_Rect() { return m_tRect; }
	INFO&		Get_Info() { return m_tInfo; }
	STAT&		Get_Stat() { return m_tStat; }
	FIGURETYPE& Get_Figure() { return m_eFigure; }
	BOOL		Is_OnGround() { return m_bOnGround || m_bOnLine; }
	void		Draw_Figure(HDC hDC);

protected:
	void	Accelarate();
	void	Update_Rect();

protected:
	RECT		m_tRect = {};
	INFO		m_tInfo = {};
	STAT		m_tStat = {10.f,10.f,10.f};
	FIGURETYPE	m_eFigure = FIGURETYPE::FT_RECT;
	Vec2		m_tForwarding_Dir = { 1.f,0.f };
	Vec2		m_tVelocity = {};
	Vec2		m_tAcceleration = {};
	BOOL		m_bOnGround = false;
	BOOL		m_bOnLine = false;
	BOOL		m_bSliding = false;
	CLine*		m_pNowLine = nullptr;
	Vec2		m_tAim = {};
};

