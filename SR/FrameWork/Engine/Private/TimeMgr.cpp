#include "TimeMgr.h"

IMPLEMENT_SINGLETON(CTimeMgr)

CTimeMgr::CTimeMgr()
{
}

HRESULT CTimeMgr::Ready_TimeMgr()
{
	::QueryPerformanceFrequency(&m_lIFrequency);
	::QueryPerformanceCounter(&m_lIPrevCount);
	m_dTimeScale = 1. / m_lIFrequency.QuadPart;

	return S_OK;
}

void CTimeMgr::Cal_DeltaTime()
{
	::QueryPerformanceCounter(&m_lICurrCount);

	m_dDeltaTime = (m_lICurrCount.QuadPart - m_lIPrevCount.QuadPart) * m_dTimeScale;
	m_lIPrevCount = m_lICurrCount;
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
