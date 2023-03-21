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
		return atan2f(vY, vX);
	}
	FLOAT Get_Size()
	{
		return sqrtf(powf(vX, 2) + powf(vY, 2));
	}
	Vec2 Get_UnitVec()
	{
		if (Get_Size() != 0) return Vec2{ vX / Get_Size(), vY / Get_Size() }; else return Vec2{ 0.f,0.f };
	}
	static FLOAT	quad_eqn(FLOAT A, FLOAT B, FLOAT C)
	{
		FLOAT D = B * B - 4.f * A * C;

		if (((-B + sqrtf(D)) / (2.f * A)) <= 1.f && ((-B + sqrtf(D)) / (2.f * A)) >= 0.f)
			return (-B + sqrtf(D)) / (2.f * A);
		else if (((-B - sqrtf(D)) / (2.f * A)) <= 1.f && ((-B - sqrtf(D)) / (2.f * A)) >= 0.f)
			return (-B - sqrtf(D)) / (2.f * A);

		return 1;
	}
	static FLOAT BUHO(FLOAT A)
	{
		if (A < 0) return -1.f;
		else if (A > 0) return 1.f;
		else return 0.f;
	}
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

struct STAT
{
	FLOAT Attack;
	FLOAT MaxHp;
	FLOAT Hp;
	FLOAT Get_HpRatio()
	{
		if (MaxHp > 0) return Hp / MaxHp;
		else return 0;
	}
};

struct POINTF
{
	POINTF() : x(0.f), y(0.f) {}
	POINTF(FLOAT _x, FLOAT _y) : x(_x), y(_y) {}
	
	FLOAT x;
	FLOAT y;
};

struct LINE
{
	LINE() :m_tLpoint(), m_tRpoint() {}
	LINE(POINTF _tLpoint, POINTF _tRpoint) 
		: m_tLpoint(_tLpoint), m_tRpoint(_tRpoint) {}

		POINTF m_tLpoint;
		POINTF m_tRpoint;

};