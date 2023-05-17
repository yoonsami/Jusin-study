#pragma once

#include "Client_Defines.h"
#include "Base.h"

namespace Engine { class CGameInstance; }

BEGIN(Client)
class CMainApp final:
    public CBase
{
private:
    CMainApp();
    virtual ~CMainApp() = default;

public:
    HRESULT Init();

    void Tick(_float deltaTime);
    HRESULT Render();

private:
	LPDIRECT3DDEVICE9	m_pGraphic_Device = { nullptr };

	CGameInstance*      m_pGameInstance = { nullptr };

private:
    HRESULT Open_Level(LEVEL eLevel);

public:
    static CMainApp* Create();
    virtual void Free() override;
};

END