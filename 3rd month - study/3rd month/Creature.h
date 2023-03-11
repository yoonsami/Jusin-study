#pragma once
#include "Object.h"
class Creature : public Object
{

public:
	Creature();
	virtual ~Creature();

public:
    // Object을(를) 통해 상속됨
	virtual void		Init() PURE;
	virtual int			Update()PURE;
	virtual void		Late_Update()PURE;
	virtual void		Render(HDC hDC)PURE;
	virtual void		Release()PURE;

public:
	BOOL				Is_Dead() { return m_tStat.fHp <= 0; }
	virtual void		OnAttacked(Object& Attacker);

protected:
	
	float		m_fSpeed = 0.f;
	bool		m_bDead = false;
	bool		m_bInvincible = false;
	vector<Object*>		m_Ui = {};
	
};

