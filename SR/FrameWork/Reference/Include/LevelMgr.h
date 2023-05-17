#pragma once
#include "Base.h"

namespace Engine { class CLevel; }

BEGIN(Engine)
class CLevelMgr final : public CBase
{
	DECLARE_SINGLETON(CLevelMgr)
private:
	CLevelMgr();
	virtual ~CLevelMgr() = default;

public:
	HRESULT Open_Level(_uint iLevelIndex, CLevel* pLevel);

	void Tick(_float fDeltaTime);
	void Late_Tick(_float fDeltaTime);


private:
	CLevel* m_pCurLevel = nullptr;
	_uint	m_iLevelIndex = 0;


public:
	virtual void Free() override;
};

END