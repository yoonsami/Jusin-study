#include "GameInstance.h"
#include "GraphicDevice.h"
#include "InputMgr.h"
#include "LevelMgr.h"

IMPLEMENT_SINGLETON(CGameInstance)

CGameInstance::CGameInstance()
{
	m_pGraphic_Device = CGraphicDevice::GetInstance();
	Safe_AddRef(m_pGraphic_Device);

	m_pInputMgr = CInputMgr::GetInstance();
	Safe_AddRef(m_pInputMgr);

	m_pLevelMgr = CLevelMgr::GetInstance();
	Safe_AddRef(m_pLevelMgr);
}

HRESULT CGameInstance::Initialize_Engine(const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut)
{
	if (m_pGraphic_Device == nullptr)
		return E_FAIL;

	if (FAILED(m_pGraphic_Device->Ready_GraphicDev(GraphicDesc, ppOut)))
	{
		MSG_BOX("Failed : Ready_GraphicDev");
		return E_FAIL;
	}

	if (!m_pInputMgr)
	{
		MSG_BOX("Failed : Ready_InputMgr");
		return E_FAIL;
	}
	else
		m_pInputMgr->Ready_InputMgr(GraphicDesc.hWnd);

	return S_OK;
}

void CGameInstance::Tick_Engine(_float fDeltaTime)
{
	if (m_pInputMgr)
		m_pInputMgr->Tick();
	if (m_pLevelMgr)
	{
		m_pLevelMgr->Tick(fDeltaTime);
		m_pLevelMgr->Late_Tick(fDeltaTime);
	}

	
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

HRESULT CGameInstance::Open_Level(_uint iLevelIndex, CLevel* pLevel)
{
	if (!m_pLevelMgr)
		return E_FAIL;

	return m_pLevelMgr->Open_Level(iLevelIndex, pLevel);
}

bool CGameInstance::GetButtonHold(KEY_TYPE key)
{
	return m_pInputMgr->GetButtonHold(key);
}

bool CGameInstance::GetButtonTap(KEY_TYPE key)
{
	return m_pInputMgr->GetButtonTap(key);
}

bool CGameInstance::GetButtonAway(KEY_TYPE key)
{
	return m_pInputMgr->GetButtonAway(key);
	
}

const POINT& CGameInstance::GetMousePos()
{
	return m_pInputMgr->GetMousePos();
}

void CGameInstance::Free()
{
	Safe_Release(m_pInputMgr);
	Safe_Release(m_pLevelMgr);
	Safe_Release(m_pGraphic_Device);
}

void CGameInstance::Release_Engine()
{
	CGameInstance::DestroyInstance();

	CInputMgr::DestroyInstance();
	CLevelMgr::DestroyInstance();

	CGraphicDevice::DestroyInstance();
}

