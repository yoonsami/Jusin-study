#include "GameInstance.h"
#include "GraphicDevice.h"

IMPLEMENT_SINGLETON(CGameInstance)

CGameInstance::CGameInstance()
{
	m_pGraphic_Device = CGraphicDevice::GetInstance();
	Safe_AddRef(m_pGraphic_Device);
}


HRESULT CGameInstance::Initialize_Engine(const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut)
{
	if (m_pGraphic_Device == nullptr)
		return E_FAIL;

	if (FAILED(m_pGraphic_Device->Ready_GraphicDev(GraphicDesc, ppOut)))
		return E_FAIL;

	return S_OK;
}

void CGameInstance::Render_Begin()
{
	if (m_pGraphic_Device)
		m_pGraphic_Device->Render_Begin();
}

void CGameInstance::Render_End()
{
	if (m_pGraphic_Device)
		m_pGraphic_Device->Render_End();
}


void CGameInstance::Free()
{
	Safe_Release(m_pGraphic_Device);
}

void Engine::CGameInstance::Release_Engine()
{
	CGameInstance::DestroyInstance();
	CGraphicDevice::DestroyInstance();
}
