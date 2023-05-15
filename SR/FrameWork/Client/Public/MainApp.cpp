#include "pch.h"
#include "MainApp.h"
#include "Device.h"

CMainApp::CMainApp()
{

}

HRESULT CMainApp::Init()
{
    if (FAILED(CDevice::GetInstance()->Create(g_hWnd)))
    {
        return E_FAIL;
    }

    return S_OK;
}

void CMainApp::Update()
{

}

void CMainApp::Render()
{
    CDevice::GetInstance()->Render_Begin();

    CDevice::GetInstance()->Render_End();
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
    CDevice::DestroyInstance();
}
