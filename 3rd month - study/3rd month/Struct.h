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
	FLOAT Get_Size() { return sqrtf(powf(vX, 2) + powf(vY, 2)); }
};

struct POSINFO
{
	float		fX;
	float		fY;
	float		fCX;
	float		fCY;

	POSINFO operator+ (const Vec2& vec) { return POSINFO{ fX + vec.vX, fY + vec.vY, fCX,fCY }; }
	POSINFO operator- (const Vec2& vec) { return POSINFO{ fX - vec.vX, fY - vec.vY, fCX,fCY }; }
	void operator+= (const Vec2& vec) { fX += vec.vX; fY += vec.vY; }
	void operator-= (const Vec2& vec) { fX -= vec.vX; fY -= vec.vY; }
	Vec2 Get_PosVec() { return Vec2{ fX,fY }; }
};

struct STATINFO
{
	string		sName;
	INT			iLevel;
	FLOAT		fHp;
	FLOAT		fMaxHp;
	FLOAT		fAtt;
	FLOAT		Get_HpRatio() { if (fMaxHp) return fHp / fMaxHp; else return 0; }
};

struct Collider
{
	static BOOL IntersectCircle(RECT* circleA, RECT* circleB)
	{
		Vec2 cenA = { ((circleA->left + circleA->right) / 2.f) , ((circleA->top + circleA->bottom) / 2.f) };
		Vec2 cenB = { ((circleB->left + circleB->right) / 2.f) , ((circleB->top + circleB->bottom) / 2.f) };

		LONG sizeA = abs(circleA->right - circleA->left);
		LONG sizeB = abs(circleB->right - circleB->left);

		return (cenA - cenB).Get_Size() <  (sizeA + sizeB) / 2.f;
	}
	
	static BOOL IntersectCirDot(RECT* circle, LONG fX, LONG fY)
	{
		Vec2 cen = { ((circle->left + circle->right) / 2.f) , ((circle->top + circle->bottom) / 2.f) };
		Vec2 dot = { (FLOAT)fX,(FLOAT)fY };

		return (cen - dot).Get_Size() < abs(circle->right - circle->left) * 0.5f;

	}

	static BOOL IntersectCirRect(RECT* circle, RECT* rect)
	{
		RECT tmp;
		
		if (!IntersectCirDot(circle, rect->left, rect->top) && !IntersectCirDot(circle, rect->right, rect->top) &&
			!IntersectCirDot(circle, rect->left, rect->bottom) && !IntersectCirDot(circle, rect->right, rect->bottom))
		{
			if (!IntersectRect(&tmp, circle, rect))
				return false;
		}
		
		return true;
	}
};