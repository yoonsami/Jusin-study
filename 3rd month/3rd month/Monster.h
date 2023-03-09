#pragma once
#include "Object.h"
class Monster :  public Object
{
public:
	Monster();
	virtual ~Monster();

public:
	virtual void		Init() override;
	virtual void		Update() override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release() override;

private:
	void Move();
};

