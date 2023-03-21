#include "pch.h"
#include "KeyInputMgr.h"

BOOL CKeyInputMgr::m_bSpacePressed = false;

BOOL CKeyInputMgr::m_bRightPressed = false;

BOOL CKeyInputMgr::m_bLeftPressed = false;

BOOL CKeyInputMgr::m_bUpPressed = false;

BOOL CKeyInputMgr::m_bDownPressed = false;

BOOL CKeyInputMgr::m_bZPressed = false;

BOOL CKeyInputMgr::m_bXPressed = false;

BOOL CKeyInputMgr::m_bLButtonPressed = false;

BOOL CKeyInputMgr::m_bRButtonPressed = false;

Vec2 CKeyInputMgr::Get_KeyInputVec()
{
	int X = (m_bRightPressed - m_bLeftPressed);
	int Y = (m_bDownPressed - m_bUpPressed);
	return Vec2{ X * 1.f,Y * 1.f }.Get_UnitVec();
}
