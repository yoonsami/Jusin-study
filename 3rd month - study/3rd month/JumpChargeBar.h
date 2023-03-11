#pragma once
#include "UI.h"
class JumpChargeBar :   public UI
{
public:
	JumpChargeBar(Object* Owner);
	virtual ~JumpChargeBar() {}

public:
	// UI을(를) 통해 상속됨
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

