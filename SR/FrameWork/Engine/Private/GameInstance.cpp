#include "GameInstance.h"
#include "GraphicDevice.h"

IMPLEMENT_SINGLETON(CGameInstance)

CGameInstance::CGameInstance()
{
	m_pDevice = CGraphicDevice::GetInstance();
	Safe_AddRef(m_pDevice);
}


HRESULT CGameInstance::Initialize_Engine(const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut)
{
	if (m_pDevice == nullptr)
		return E_FAIL;

	if (FAILED(m_pDevice->Ready_GraphicDev(GraphicDesc, ppOut)))
		return E_FAIL;

	return S_OK;
}

void CGameInstance::Render_Begin()
{
	if (m_pDevice)
		m_pDevice->Render_Begin();
}

void CGameInstance::Render_End()
{
	if (m_pDevice)
		m_pDevice->Render_End();
}


void CGameInstance::Free()
{
	Safe_Release(m_pDevice);

	CGraphicDevice::DestroyInstance();
}