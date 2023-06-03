#pragma once
#include "Base.h"
BEGIN(Engine)

class CTimer;

class CTimerMgr final : public CBase
{
	DECLARE_SINGLETON(CTimerMgr)
private:
	CTimerMgr();
	virtual ~CTimerMgr() = default;

public:
	HRESULT Add_Timer(const wstring& strTimerTag);
	_float Compute_TimeDelta(const wstring& strTimerTag);

private:
	map<wstring, CTimer*> m_Timers;

private:
	CTimer* Find_Timer(const wstring& strTimerTag);

public:
	virtual void Free() override;
};

END