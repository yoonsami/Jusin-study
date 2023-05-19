#pragma once
#include "Client_Defines.h"
#include "Base.h"

BEGIN(Client) 

class CLoader final :  public CBase
{
private:
	CLoader(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual	~CLoader() = default;

public:
	const _tchar* Get_LoadingText() const { return m_szLoading; }
	_bool Is_Finished() const { return m_bFinished; }

public:
	HRESULT Initialize(LEVEL eNextLevel);
	HRESULT LoadingForNextLevel();

private:
	LPDIRECT3DDEVICE9	m_pGraphic_Device = nullptr;
	HANDLE				m_hThread = INVALID_HANDLE_VALUE;
	CRITICAL_SECTION	m_CriticalSection{};
	LEVEL				m_eNextLevel = LEVEL_END;

	_bool				m_bFinished = false;
	_tchar				m_szLoading[MAX_PATH] = TEXT("");

private:
	HRESULT Loading_ForLogo();
	HRESULT Loading_ForGamePlay();

public:
	static CLoader* Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel);
	virtual void Free() override;

};

END