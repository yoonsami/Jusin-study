#pragma once
#include "Base.h"

BEGIN(Engine)
class ENGINE_DLL CTimeMgr final :
    public CBase
{
    DECLARE_SINGLETON(CTimeMgr)
private:
    CTimeMgr();
    virtual ~CTimeMgr() = default;

public:
    HRESULT Ready_TimeMgr();
    void Cal_DeltaTime();

	_double GetDeltaTime() { return m_dDeltaTime; }
	_uint	GetFPS() { return m_iFps; }

private:
	LARGE_INTEGER m_lIFrequency{};
	LARGE_INTEGER m_lIPrevCount{};
	LARGE_INTEGER m_lICurrCount{};
	_double  m_dDeltaTime = 0.;
	_double  m_dTimeScale = 0.;

private:
	_uint m_iFrameCount = 0;
	_double  m_dFrameTime = 0.f;
	_uint m_iFps = 0;

public:
	virtual void Free() override;
};

END