#pragma once
#include "UI.h"
class JumpChargeBar :   public UI
{
public:
	JumpChargeBar(Object* Owner);
	virtual ~JumpChargeBar() {}

public:
	// UI��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

