#pragma once
#include "define.h"
#include "Object.h"

class Creature : public Object
{
public:
	Creature(int creatureType);
	virtual ~Creature();

public:
	void GetAcc();
	bool OnGround();
	void SetPos(float x, float y) { _posCrd._crdX = x; _posCrd._crdY = y; }
	PosInfo GetPos() { return _posCrd; }
	StatInfo GetStatInfo() { return m_statInfo; }
	virtual void PrintInfo() = 0;
	void CorrectPos();
	virtual void Attack(Creature* _target) = 0;
	void OnAttacked(Creature* Attacker);
	bool IsDead() { return m_statInfo._hp == 0; }
	int GetLookingDir() { return m_iLookingDir; }

protected:
	int m_iLookingDir;
	int m_iCreatureType;
	Creature* m_target;
	PosInfo _posCrd;
	PosInfo _Vel;
	PosInfo _Acc;

};

