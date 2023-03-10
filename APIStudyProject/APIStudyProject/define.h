#pragma once
#pragma once

#define			WINCX		800
#define			WINCY		600

#define			PI			3.141592f
#define			PURE		= 0

extern HWND g_hWnd;


struct Vec2
{
	float vX;
	float vY;
	void operator+= (const Vec2& vec) { vX += vec.vX; vY += vec.vY; }
	void operator-= (const Vec2& vec) { vX -= vec.vX; vY -= vec.vY; }
	Vec2 operator+ (const Vec2& vec) { return Vec2{ vX + vec.vX, vY + vec.vY }; }
	Vec2 operator- (const Vec2& vec) { return Vec2{ vX - vec.vX, vY - vec.vY }; }
	Vec2 operator/ (const FLOAT& a) { return Vec2{ vX / a, vY /a }; }
	FLOAT Get_Theta()
	{
		if (abs(vX) <= 0.0001f)
			return PI * 0.5f;
		return atan2f(vY, vX);
	}
	FLOAT Get_Size(){return sqrt(static_cast<FLOAT>(pow(vX, 2)) + static_cast<FLOAT>(pow(vY, 2)));}
};

struct INFO
{
	float		fX;
	float		fY;
	float		fCX;
	float		fCY;

	INFO operator+ (const Vec2& vec){return INFO{ fX + vec.vX, fY + vec.vY, fCX,fCY };}
	INFO operator- (const Vec2& vec){return INFO{ fX - vec.vX, fY - vec.vY, fCX,fCY };}
	void operator+= (const Vec2& vec) { fX += vec.vX; fY += vec.vY; }
	void operator-= (const Vec2& vec) { fX -= vec.vX; fY -= vec.vY; }
	Vec2 Get_PosVec() { return Vec2{ fX,fY }; }
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

