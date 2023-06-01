#include "InputMgr.h"

IMPLEMENT_SINGLETON(CInputMgr)

CInputMgr::CInputMgr()
{

}

void CInputMgr::Ready_InputMgr(HWND hWnd)
{
	m_vecKeyStates.resize(KEY_TYPE_COUNT, KEY_STATE::NONE);
	m_hWnd = hWnd;
}

void CInputMgr::Tick()
{
	HWND hWnd = ::GetActiveWindow();
	if (m_hWnd != hWnd)
	{
		for (auto& i : m_vecKeyStates)
			i = KEY_STATE::NONE;
		return;
	}

	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
	if (::GetKeyboardState(asciiKeys) == false)
		return;

	for (_uint key = 0; key < KEY_TYPE_COUNT; ++key)
	{
		if (asciiKeys[key] & 0x80)
		{
			KEY_STATE& state = m_vecKeyStates[key];

			if (state == KEY_STATE::HOLD || state == KEY_STATE::TAP)
			{
				state = KEY_STATE::HOLD;
			}
			else
			{
				state = KEY_STATE::TAP;
			}
		}
		else
		{
			KEY_STATE& state = m_vecKeyStates[key];

			if (state == KEY_STATE::HOLD || state == KEY_STATE::TAP)
			{
				state = KEY_STATE::AWAY;
			}
			else
			{
				state = KEY_STATE::NONE;
			}
		}
	}

	::GetCursorPos(&m_ptMousePos);
	::ScreenToClient(m_hWnd, &m_ptMousePos);


	POINT center = { 640,360 };
	m_MouseDir.x =_float( m_ptMousePos.x - center.x);
	m_MouseDir.y = _float(m_ptMousePos.y - center.y);

	ClientToScreen(m_hWnd, &center);
	SetCursorPos(center.x,center.y);
}

void CInputMgr::Free()
{

}
