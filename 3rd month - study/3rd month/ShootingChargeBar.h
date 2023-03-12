#pragma once
#include "UI.h"
class ShootingChargeBar :
    public UI
{
public:
	ShootingChargeBar(Object* Owner);
	virtual ~ShootingChargeBar() {}
public:
	// UI을(를) 통해 상속됨
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	int		m_iFlagCount = 0;
};

