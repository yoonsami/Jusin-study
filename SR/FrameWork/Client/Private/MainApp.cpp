#include "pch.h"
#include "MainApp.h"
#include "GameInstance.h"
#include "Level_Loading.h"

CMainApp::CMainApp()
{
    m_pGameInstance = CGameInstance::GetInstance();
    Safe_AddRef(m_pGameInstance);
}

HRESULT CMainApp::Init()
{
    GRAPHICDESC			GraphicDesc{};

	GraphicDesc.hWnd = g_hWnd;
	GraphicDesc.iSizeX = g_iWinSizeX;
	GraphicDesc.iSizeY = g_iWinSizeY;
	GraphicDesc.eWinMode = GRAPHICDESC::WINMODE_WIN;

    if (FAILED(m_pGameInstance->Initialize_Engine(LEVEL_END, GraphicDesc, &m_pGraphic_Device)))
    {
        MSG_BOX("Engine Init Failed : Initialize_Engine");
        return E_FAIL;
    }

    if (FAILED(Ready_Default_Setting()))
    {
        MSG_BOX("Failed : Ready_Default_Setting");
        return E_FAIL;
    }

    if (FAILED(Ready_Prototype_Static_Component()))
    {
		MSG_BOX("Failed : Ready_Prototype_Static_Component");
		return E_FAIL;
    }

    if (FAILED(Open_Level(LEVEL_LOGO)))
    {
        MSG_BOX("Open_Level Failed : LEVEL_LOGO");
        return E_FAIL;
    }

    return S_OK;
}

void CMainApp::Tick(_float deltaTime)
{
    m_pGameInstance->Tick_Engine(deltaTime);
}

HRESULT CMainApp::Render()
{
	if (!m_pGameInstance ||
        !m_pRenderer)
		return E_FAIL;

    m_pGameInstance->Render_Begin();

    m_pRenderer->Draw_RenderGroup();

    m_pGameInstance->Render_End();

    return S_OK;
}

HRESULT CMainApp::Ready_Default_Setting()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, false);

	return S_OK;
}

HRESULT CMainApp::Open_Level(LEVEL eLevel)
{
    if (!m_pGameInstance)
        return E_FAIL;

    if (FAILED(m_pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, eLevel))))
        return E_FAIL;

    return S_OK;
}

HRESULT CMainApp::Ready_Prototype_Static_Component()
{
    if (!m_pGameInstance)
        return E_FAIL;
        
	// for Prototype_Component_Renderer
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Renderer"),
		m_pRenderer = CRenderer::Create(m_pGraphic_Device))))
		return E_FAIL;

    Safe_AddRef(m_pRenderer);

    // for Prototype_Component_VIBuffer_Rect
    if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), 
        CVIBuffer_Rect::Create(m_pGraphic_Device))))
        return E_FAIL;

    return S_OK;
}

CMainApp* CMainApp::Create()
{
    CMainApp* pMainApp = new CMainApp();

    if (FAILED(pMainApp->Init()))
    {
        MSG_BOX("Init Failed : MainApp Create");
        Safe_Release(pMainApp);
    }

    return pMainApp;
}

void CMainApp::Free()
{
    Safe_Release(m_pRenderer);
    Safe_Release(m_pGraphic_Device);
    Safe_Release(m_pGameInstance);

    CGameInstance::Release_Engine();
}


