#pragma once
#include "Base.h"

BEGIN(Engine)
class CLevelMgr final : public CBase
{
	DECLARE_SINGLETON(CLevelMgr)
private:
	CLevelMgr();
	virtual ~CLevelMgr() = default;

public:
	virtual void Free() override;
};

END