#include "pch.h"
#include "MainApp.h"
#include "GameInstance.h"

CMainApp::CMainApp()
{
    m_pGameInstance = CGameInstance::GetInstance();
    Safe_AddRef(m_pGameInstance);
}

HRESULT CMainApp::Init()
{
	GRAPHICDESC			GraphicDesc;
	ZeroMemory(&GraphicDesc, sizeof GraphicDesc);

	GraphicDesc.hWnd = g_hWnd;
	GraphicDesc.iSizeX = g_iWinSizeX;
	GraphicDesc.iSizeY = g_iWinSizeY;
	GraphicDesc.eWinMode = GRAPHICDESC::WINMODE_WIN;

    if (FAILED(m_pGameInstance->Initialize_Engine(GraphicDesc,&m_pGraphic_Device)))
    {
        return E_FAIL;
    }

    return S_OK;
}

void CMainApp::Tick(_float deltaTime)
{

}

HRESULT CMainApp::Render()
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

    m_pGameInstance->Render_Begin();

    m_pGameInstance->Render_End();

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
    Safe_Release(m_pGraphic_Device);
    Safe_Release(m_pGameInstance);

    CGameInstance::DestroyInstance();
}