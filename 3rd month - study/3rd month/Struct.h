#pragma once

struct Vec2
{
	float vX;
	float vY;
	void operator+= (const Vec2& vec) { vX += vec.vX; vY += vec.vY; }
	void operator-= (const Vec2& vec) { vX -= vec.vX; vY -= vec.vY; }
	Vec2 operator+ (const Vec2& vec) { return Vec2{ vX + vec.vX, vY + vec.vY }; }
	Vec2 operator- (const Vec2& vec) { return Vec2{ vX - vec.vX, vY - vec.vY }; }
	Vec2 operator/ (const FLOAT& a) { return Vec2{ vX / a, vY / a }; }
	Vec2 operator* (const FLOAT& a) { return Vec2{ vX * a, vY * a }; }
	FLOAT Get_Theta()
	{
		if (abs(vX) <= 0.0001f)
			return PI * 0.5f;
		return atan2f(vY, vX);
	}
	FLOAT Get_Size() { return static_cast<FLOAT>(sqrt(static_cast<FLOAT>(pow(vX, 2)) + static_cast<FLOAT>(pow(vY, 2)))); }
};

struct INFO
{
	float		fX;
	float		fY;
	float		fCX;
	float		fCY;

	INFO operator+ (const Vec2& vec) { return INFO{ fX + vec.vX, fY + vec.vY, fCX,fCY }; }
	INFO operator- (const Vec2& vec) { return INFO{ fX - vec.vX, fY - vec.vY, fCX,fCY }; }
	void operator+= (const Vec2& vec) { fX += vec.vX; fY += vec.vY; }
	void operator-= (const Vec2& vec) { fX -= vec.vX; fY -= vec.vY; }
	Vec2 Get_PosVec() { return Vec2{ fX,fY }; }
};