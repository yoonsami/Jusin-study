#pragma once

#include "Client_Defines.h"
#include "Base.h"

BEGIN(Engine)
    class CRenderer;
    class CGameInstance;
END

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
    CRenderer*          m_pRenderer = nullptr;

private:
    HRESULT Ready_Default_Setting();
    HRESULT Open_Level(LEVEL eLevel);
    HRESULT Ready_Prototype_Static_Component();

public:
    static CMainApp* Create();
    virtual void Free() override;
};

END