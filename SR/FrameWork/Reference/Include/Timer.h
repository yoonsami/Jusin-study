#pragma once
#include "Base.h"

BEGIN(Engine)
class CTimer final : public CBase
{
private:
    CTimer();
    virtual ~CTimer() = default;

public:
	_double GetDeltaTime() { return m_dDeltaTime; }

public:
    HRESULT Initialize();
    void Cal_DeltaTime();

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
	static CTimer* Create();
	virtual void Free() override;
};

END