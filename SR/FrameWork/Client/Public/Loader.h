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
	HRESULT Initialize(LEVEL eNextLevel);
	
	HRESULT LoadingForNextLevel();

private:
	LEVEL				m_eNextLevel = LEVEL_END;
	LPDIRECT3DDEVICE9	m_pGraphic_Device = nullptr;
	HANDLE				m_hThread = nullptr;
	CRITICAL_SECTION	m_CriticalSection{};

private:
	HRESULT Loading_ForLogo();
	HRESULT Loading_ForGamePlay();

public:
	static CLoader* Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel);
	virtual void Free() override;

};

END