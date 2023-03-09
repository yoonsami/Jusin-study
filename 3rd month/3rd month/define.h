#pragma once

#define			WINCX		800
#define			WINCY		600

#define			PI			3.141592f
#define			PURE		= 0


//플레이존 좌표값 정의
#define			PLAYZONELEFT 50
#define			PLAYZONETOP 50
#define			PLAYZONERIGHT WINCX - 50
#define			PLAYZONEBOTTOM WINCY - 50

extern HWND g_hWnd;

struct INFO
{
	float		fX;
	float		fY;
	float		fCX;
	float		fCY;
};

template<typename T>
void	Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

template<typename T>
void	Safe_Delete_Array(T& Temp)
{
	if (Temp)
	{
		delete[] Temp;
		Temp = nullptr;
	}
}

enum class DIRECTION
{
	DIR_LEFT, 
	DIR_UP, 
	DIR_RIGHT, 
	DIR_DOWN,
	DIR_LU,
	DIR_RU,
	DIR_END
};

