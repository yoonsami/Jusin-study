#pragma once
#include "Include.h"
class CLine
{
public:
	CLine(POINTF _tLpoint, POINTF _tRpoint);
	CLine(LINE _tLine) : m_tInfo(_tLine) {}
	~CLine() {}

public:
	const LINE& Get_Info() const { return m_tInfo; }
	void  Set_PosY(FLOAT a) { m_tInfo.m_tRpoint.y += a; }
	FLOAT Get_Theta();
	FLOAT Get_YPos(FLOAT X);
	FLOAT Get_Distance_With_Dot(FLOAT X, FLOAT Y);
	Vec2 Get_NormalVector();

public:
	void		Render(HDC hDC);
private:
	LINE		m_tInfo;

};

