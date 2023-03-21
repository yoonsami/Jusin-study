#include "pch.h"
#include "CollisionMgr.h"
#include "Line.h"


BOOL CCollisionMgr::IntersectCirRect(RECT* circle, RECT* rect)
{
	FLOAT closestX = (circle->left + circle->right) / 2.f;
	FLOAT closestY = (circle->top + circle->bottom) / 2.f;

	if (closestX < rect->left)
		closestX = static_cast<FLOAT>(rect->left);
	else if (closestX > rect->right)
		closestX = static_cast<FLOAT>(rect->right);

	if (closestY < rect->top)
		closestY = static_cast<FLOAT>(rect->top);
	else if (closestY > rect->bottom)
		closestY = static_cast<FLOAT>(rect->bottom);

	return IntersectCirDot(circle, closestX, closestY);
}

BOOL CCollisionMgr::IntersectWith(RECT& rectA, RECT& rectB, FIGURETYPE figureA, FIGURETYPE figureB)
{
	RECT tmp;

	if (figureA == FIGURETYPE::FT_RECT)
	{
		if (figureB == FIGURETYPE::FT_RECT)
			return IntersectRect(&tmp, &rectA, &rectB);
		if (figureB == FIGURETYPE::FT_CIRCLE)
			return IntersectCirRect(&rectB, &rectA);
		if (figureB == FIGURETYPE::FT_ARROW)
			return IntersectRectDot(&rectA, (rectB.right + rectB.left) * 0.5f, (rectB.bottom + rectB.top) * 0.5f);
	}
	else if (figureA == FIGURETYPE::FT_CIRCLE)
	{
		if (figureB == FIGURETYPE::FT_RECT)
			return IntersectCirRect(&rectA, &rectB);
		if (figureB == FIGURETYPE::FT_CIRCLE)
			return IntersectCircle(&rectA, &rectB);
		if (figureB == FIGURETYPE::FT_ARROW)
			return IntersectCirDot(&rectA, (rectB.right + rectB.left) * 0.5f, (rectB.bottom + rectB.top) * 0.5f);
	}
	else if (figureA == FIGURETYPE::FT_ARROW)
	{
		if (figureB == FIGURETYPE::FT_RECT)
			return IntersectRectDot(&rectB, (rectA.right + rectA.left) * 0.5f, (rectA.bottom + rectA.top) * 0.5f);
		if (figureB == FIGURETYPE::FT_CIRCLE)
			return IntersectCirDot(&rectB, (rectA.right + rectA.left) * 0.5f, (rectA.bottom + rectA.top) * 0.5f);
	}

	return false;
}

void CCollisionMgr::CheckCollide(list<CObject*> _Dst, list<CObject*> _Src)
{
	for (auto& i : _Dst)
	{
		for (auto& j : _Src)
		{
			if (IntersectWith(i->Get_Rect(), j->Get_Rect(), i->Get_Figure(), j->Get_Figure()))
			{
				if (i->Get_Stat().Hp > 0 && j->Get_Stat().Hp > 0)
				{


				}
			}
		}
	}
}

void CCollisionMgr::CheckCollideBlock(list<CObject*> _Dst, list<CObject*> _Src)
{
	RECT rcTemp;

	for (auto& i : _Dst)
	{
		for (auto& j : _Src)
		{
			if (IntersectRect(&rcTemp, &(i->Get_Rect()), &(j->Get_Rect())))
			{
				float fX = float(rcTemp.right - rcTemp.left);
				float fY = float(rcTemp.bottom - rcTemp.top);

				if (fX > fY)
				{
					if (i->Get_Info().fY < j->Get_Info().fY)
						i->Get_Info().fY += -fY;
					else
						i->Get_Info().fY += fY;
				}
				else
				{
					if (i->Get_Info().fX < j->Get_Info().fX)
						i->Get_Info().fX += -fX;
					else
						i->Get_Info().fX += fX;
				}


			}
		}
	}

}

BOOL CCollisionMgr::IntersectRectLine(RECT* rect, CLine* line)
{
	if (rect->right < line->Get_Info().m_tLpoint.x)
		return false;
	if (rect->left > line->Get_Info().m_tRpoint.x)
		return false;

	int count = 0;

	if (line->Get_YPos((FLOAT)rect->left) < rect->top)
		++count;
	else if (line->Get_YPos((FLOAT)rect->left) >= rect->top)
		--count;

	if (line->Get_YPos((FLOAT)rect->right) < rect->top)
		++count;
	else if (line->Get_YPos((FLOAT)rect->right) >= rect->top)
		--count;

	if (line->Get_YPos((FLOAT)rect->left) < rect->bottom)
		++count;
	else if (line->Get_YPos((FLOAT)rect->left) >= rect->bottom)
		--count;

	if (line->Get_YPos((FLOAT)rect->right) < rect->bottom)
		++count;
	else if (line->Get_YPos((FLOAT)rect->right) >= rect->bottom)
		--count;

	if (count == -4)
		return false;

	return true;
}

Vec2 CCollisionMgr::CollideRectLine(RECT* rect, CLine* line)
{
	vector<FLOAT> distance = {};
	distance.push_back(line->Get_Distance_With_Dot(rect->left, rect->top));
	distance.push_back(line->Get_Distance_With_Dot(rect->right, rect->top));
	distance.push_back(line->Get_Distance_With_Dot(rect->right, rect->bottom));
	distance.push_back(line->Get_Distance_With_Dot(rect->left, rect->bottom));

	FLOAT ClosestDistance = *min_element(distance.begin(), distance.end());
	int min_index = min_element(distance.begin(), distance.end()) - distance.begin();

	return line->Get_NormalVector() * ClosestDistance;
}


BOOL CCollisionMgr::Is_UnderLine(POINTF dot, CLine* line)
{
	{
		POINTF LPOINT = line->Get_Info().m_tLpoint;
		POINTF RPOINT = line->Get_Info().m_tRpoint;
		if (dot.x <= LPOINT.x)
			return false;
		if (dot.x > RPOINT.x)
			return false;

		return ((RPOINT.y - LPOINT.y) / (RPOINT.x - LPOINT.x)) * (dot.x - LPOINT.x) - (dot.y - LPOINT.y) <= 0;
	}
}
