#pragma once


namespace Engine
{
	struct GRAPHICDESC
	{
		enum WINMODE { WINMODE_FULL, WINMODE_WIN, WINMODE_END };

		HWND			hWnd;
		unsigned int	iSizeX, iSizeY;
		WINMODE			eWinMode;

	};

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
}
