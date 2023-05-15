#pragma once
#include "Include.h"
class CKeyInputMgr
{
public:





	static BOOL			m_bSpacePressed;
	static BOOL			m_bRightPressed;
	static BOOL			m_bLeftPressed;
	static BOOL			m_bUpPressed;
	static BOOL			m_bDownPressed;
	static BOOL			m_bZPressed;
	static BOOL			m_bXPressed;
	static BOOL			m_bLButtonPressed;
	static BOOL			m_bRButtonPressed;
	static Vec2			Get_KeyInputVec();
};

