#pragma once
#include "Base.h"

BEGIN(Engine)



enum class KEY_STATE
{
	NONE,
	HOLD,
	TAP,
	AWAY,
	KEYSTATE_END
};

enum
{
	KEY_TYPE_COUNT = static_cast<_uint>(VK_MAX + 1),
	KEY_STATE_COUNT = static_cast<_uint>(KEY_STATE::KEYSTATE_END)

};


class CInputMgr final : public CBase
{
    DECLARE_SINGLETON(CInputMgr)
private:
    CInputMgr();
    virtual ~CInputMgr() = default;

public:
	void Ready_InputMgr(HWND hWnd);
	void Tick();

public:
	bool GetButtonHold(KEY_TYPE key) { return GetState(key) == KEY_STATE::HOLD; }
	bool GetButtonTap(KEY_TYPE key) { return GetState(key) == KEY_STATE::TAP; }
	bool GetButtonAway(KEY_TYPE key) { return GetState(key) == KEY_STATE::AWAY; }

	const POINT& GetMousePos() { return m_ptMousePos; }
	const _float2& GetMouseDir() { return m_vMouseDir; }

public:
	virtual void Free() override;

private:
	inline KEY_STATE GetState(KEY_TYPE key) { return m_vecKeyStates[static_cast<_uchar>(key)]; }

private:
	HWND				m_hWnd = nullptr;
	vector<KEY_STATE>	m_vecKeyStates;
	POINT				m_ptMousePos{};

	_float2				m_vMouseDir{};
};

END