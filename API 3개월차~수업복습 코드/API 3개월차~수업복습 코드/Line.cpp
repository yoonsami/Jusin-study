#include "pch.h"
#include "Line.h"

CLine::CLine(POINTF _tLpoint, POINTF _tRpoint)
{
	if (_tLpoint.x < _tRpoint.x)
		m_tInfo = { _tLpoint, _tRpoint };
	else m_tInfo = { _tRpoint, _tLpoint };
}

FLOAT CLine::Get_Theta()
{
	return atan2f(m_tInfo.m_tRpoint.y - m_tInfo.m_tLpoint.y, m_tInfo.m_tRpoint.x - m_tInfo.m_tLpoint.x);
}

FLOAT CLine::Get_YPos(FLOAT X)
{
	return (m_tInfo.m_tRpoint.y - m_tInfo.m_tLpoint.y) / (m_tInfo.m_tRpoint.x - m_tInfo.m_tLpoint.x) * (X - m_tInfo.m_tLpoint.x) + m_tInfo.m_tLpoint.y;
}

FLOAT CLine::Get_Distance_With_Dot(FLOAT X, FLOAT Y)
{
	FLOAT X1 = m_tInfo.m_tLpoint.x;
	FLOAT X2 = m_tInfo.m_tRpoint.x;
	FLOAT Y1 = m_tInfo.m_tLpoint.y;
	FLOAT Y2 = m_tInfo.m_tRpoint.y;

	return fabsf((Y2 - Y1) / (X2 - X1) * (X - X1) - (Y - Y1)) / sqrtf(((Y2 - Y1) / (X2 - X1)) * ((Y2 - Y1) / (X2 - X1)) + 1);
}

Vec2 CLine::Get_NormalVector()
{
	FLOAT X1 = m_tInfo.m_tLpoint.x;
	FLOAT X2 = m_tInfo.m_tRpoint.x;
	FLOAT Y1 = m_tInfo.m_tLpoint.y;
	FLOAT Y2 = m_tInfo.m_tRpoint.y;
	return Vec2{ Y1 - Y2, X2 - X1 }.Get_UnitVec();
}

void CLine::Render(HDC hDC)
{
	MoveToEx(hDC, static_cast<INT>(m_tInfo.m_tLpoint.x), static_cast<INT>(m_tInfo.m_tLpoint.y), nullptr);
	LineTo(hDC, static_cast<INT>(m_tInfo.m_tRpoint.x), static_cast<INT>(m_tInfo.m_tRpoint.y));
}

