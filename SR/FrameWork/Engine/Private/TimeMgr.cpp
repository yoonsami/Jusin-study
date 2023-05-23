#include "TimeMgr.h"

IMPLEMENT_SINGLETON(CTimeMgr)

CTimeMgr::CTimeMgr()
{
}

HRESULT CTimeMgr::Ready_TimeMgr()
{
	::QueryPerformanceFrequency(&m_llFrequency);
	::QueryPerformanceCounter(&m_llPrevCount);
	m_dTimeScale = 1. / m_llFrequency.QuadPart;

	return S_OK;
}

void CTimeMgr::Cal_DeltaTime()
{
	::QueryPerformanceCounter(&m_llCurrCount);

	m_dDeltaTime = (m_llCurrCount.QuadPart - m_llPrevCount.QuadPart) * m_dTimeScale;
	m_llPrevCount = m_llCurrCount;
	m_iFrameCount++;
	m_dFrameTime += m_dDeltaTime;

	if (m_dFrameTime > 1.)
	{
		m_iFps = static_cast<_uint>(m_iFrameCount/m_dFrameTime);
		m_iFrameCount = 0;
		m_dFrameTime = 0.;
	}
}

void CTimeMgr::Free()
{

}
