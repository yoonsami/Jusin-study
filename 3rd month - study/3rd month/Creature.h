#pragma once
#include "Object.h"
class Creature : public Object
{

public:
	Creature(INT _CreatureType);
	Creature(const Creature& player);
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
	INT					Get_CreatureType() { return m_iCreatureType; }

	void				Draw_Figure(HDC hDC);

protected:
	INT					m_iCreatureType;
	float				m_fSpeed = 0.f;
	vector<Object*>		m_Ui = {};
	
};

