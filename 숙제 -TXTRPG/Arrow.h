#pragma once
#include "define.h"
class Creature;

class Arrow
{
public:
	Arrow(Creature* _owner, Creature* _target);
	~Arrow();

public:
	void FireArrow();
	void SetArrowPos();
	int GetFlyingDistance() { return _flyingDistance; }
	PosInfo GetArrowPos() { return _posCrd; }
	void CorrectPos();
	int GetDirOfArrow() { if (_Vel._crdX > 0)return RIGHT; else return LEFT; }
private:
	int _flyingDistance;
	PosInfo _posCrd;
	PosInfo _Vel;
	Creature* m_owner;
	Creature* m_target;
	PosInfo _startedPos;
};

