#pragma once
#include "UI.h"

class HpBar :  public UI
{
public:
	HpBar(Object* _pOwner);
	virtual ~HpBar() {}
public:
	// UI을(를) 통해 상속됨
	virtual void	Init() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

private:	
	
};

