#pragma once
#include "Base.h"

enum class KEY_TYPE
{
	UP = VK_UP,
	DOWN = VK_DOWN,
	LEFT = VK_LEFT,
	RIGHT = VK_RIGHT,

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
	Q = 'Q',
	E = 'E',
	Z = 'Z',
	C = 'C',


	KEY_1 = '1',
	KEY_2 = '2',
	KEY_3 = '3',
	KEY_4 = '4',

	SPACE = VK_SPACE,
	ESC = VK_ESCAPE,
	ENTER = VK_RETURN,
	LCTRL = VK_LCONTROL,
	LSHIFT = VK_LSHIFT,

	LBUTTON = VK_LBUTTON,
	RBUTTON = VK_RBUTTON,
};

enum class KEY_STATE
{
	NONE,
	PRESS,
	DOWN,
	UP,
	KEYSTATE_END
};

enum
{
	KEY_TYPE_COUNT = static_cast<_uint>(VK_MAX + 1),
	KEY_STATE_COUNT = static_cast<_uint>(KEY_STATE::KEYSTATE_END)

};


class CInputMgr :
    public CBase
{
    DECLARE_SINGLETON(CInputMgr)
private:
    CInputMgr();
    virtual ~CInputMgr() = default;

	void Ready_InputMgr(HWND hWnd);

	void Tick();

public:
	virtual void Free() override;


};

