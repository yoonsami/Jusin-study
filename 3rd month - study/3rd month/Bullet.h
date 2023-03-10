#pragma once
#include "Object.h"

class Bullet : public Object
{
public:
	Bullet();
	virtual ~Bullet();

public:
	virtual void		Init() override;
	virtual int			Update() override;
	virtual void		Late_Update() override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release() override;

public:
	void Set_Dead() { m_bDead = true; }
};

