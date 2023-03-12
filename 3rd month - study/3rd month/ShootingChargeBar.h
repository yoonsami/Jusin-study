#pragma once
#include "UI.h"
class ShootingChargeBar :
    public UI
{
public:
	ShootingChargeBar(Object* Owner);
	virtual ~ShootingChargeBar() {}
public:
	// UI��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	int		m_iFlagCount = 0;
};

