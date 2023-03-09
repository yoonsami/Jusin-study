#pragma once
#include "Object.h"

class Bullet : public Object
{
public:
	Bullet();
	virtual ~Bullet();

public:
	virtual void		Init() override;
	virtual void		Update() override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release() override;

public:
	void Set_PosDir(float _fX, float _fY, DIRECTION _dir);
};

