#include "TimerMgr.h"
#include "Timer.h"

IMPLEMENT_SINGLETON(CTimerMgr)

CTimerMgr::CTimerMgr()
{
}

HRESULT CTimerMgr::Add_Timer(const wstring& strTimerTag)
{
	if (Find_Timer(strTimerTag))
		return E_FAIL;

	m_Timers.emplace(strTimerTag, CTimer::Create());

	return S_OK;
}

_float CTimerMgr::Compute_TimeDelta(const wstring& strTimerTag)
{
	CTimer* pTimer = Find_Timer(strTimerTag);
	if (!pTimer)
		return 0.f;

	pTimer->Cal_DeltaTime();

	return _float(pTimer->GetDeltaTime());
}

CTimer* CTimerMgr::Find_Timer(const wstring& strTimerTag)
{
	auto iter = m_Timers.find(strTimerTag);
	if (iter == m_Timers.end())
		return nullptr;

	return iter->second;
}

void CTimerMgr::Free()
{
	for (auto& Pair : m_Timers)
		Safe_Release(Pair.second);

	m_Timers.clear();
}
