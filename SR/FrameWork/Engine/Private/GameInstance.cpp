#include "GameInstance.h"
#include "GraphicDevice.h"
#include "InputMgr.h"
#include "LevelMgr.h"
#include "ObjectMgr.h"
#include "GameObject.h"
#include "TimerMgr.h"

IMPLEMENT_SINGLETON(CGameInstance)

CGameInstance::CGameInstance()
{
	m_pGraphic_Device = CGraphicDevice::GetInstance();
	Safe_AddRef(m_pGraphic_Device);

	m_pInputMgr = CInputMgr::GetInstance();
	Safe_AddRef(m_pInputMgr);

	m_pLevelMgr = CLevelMgr::GetInstance();
	Safe_AddRef(m_pLevelMgr);

	m_pObjectMgr = CObjectMgr::GetInstance();
	Safe_AddRef(m_pObjectMgr);

	m_pComponentMgr = CComponentMgr::GetInstance();
	Safe_AddRef(m_pComponentMgr);

	m_pTimerMgr = CTimerMgr::GetInstance();
	Safe_AddRef(m_pTimerMgr);
}

HRESULT CGameInstance::Initialize_Engine(_uint iNumLevels, const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut)
{
	if (m_pGraphic_Device == nullptr)
		return E_FAIL;

	// InputMgr
	{
		if (!m_pInputMgr)
		{
			MSG_BOX("Failed : Ready_InputMgr");
			return E_FAIL;
		}
		else
			m_pInputMgr->Ready_InputMgr(GraphicDesc.hWnd);
	}

	// GraphicDevice
	if (FAILED(m_pGraphic_Device->Ready_GraphicDev(GraphicDesc, ppOut)))
	{
		MSG_BOX("Failed : Ready_GraphicDev");
		return E_FAIL;
	}

	//ObjMgr
	if (FAILED(m_pObjectMgr->Reserve_Manager(iNumLevels)))
	{
		MSG_BOX("Failed to Reserve_Manager : ObjMgr");
		return E_FAIL;
	}

	if (FAILED(m_pComponentMgr->Reserve_Manager(iNumLevels)))
	{
		MSG_BOX("Failed : Reserve_Manager : ComponentMgr");
		return E_FAIL;
	}

	return S_OK;
}

void CGameInstance::Tick_Engine(_float fDeltaTime)
{
	if (!m_pLevelMgr || !m_pObjectMgr)
		return;

	m_pInputMgr->Tick();

	m_pLevelMgr->Tick(fDeltaTime);
	m_pObjectMgr->Tick(fDeltaTime);

	m_pLevelMgr->Late_Tick(fDeltaTime);	
	m_pObjectMgr->Late_Tick(fDeltaTime);
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

#pragma region LevelMgr

HRESULT CGameInstance::Open_Level(_uint iLevelIndex, CLevel* pLevel)
{
	if (!m_pLevelMgr)
		return E_FAIL;

	return m_pLevelMgr->Open_Level(iLevelIndex, pLevel);
}

#pragma endregion LevelMgr

#pragma region ObjectMgr

HRESULT CGameInstance::Add_Prototype(const wstring& strPrototypeTag, CGameObject* pPrototype)
{
	if (!m_pObjectMgr)
		return E_FAIL;


	return m_pObjectMgr->Add_Prototype(strPrototypeTag, pPrototype);
}

HRESULT CGameInstance::Add_GameObject(_uint iLevel, const wstring& strPrototypeTag, const wstring& strLayerTag, void* pArg)
{
	if (!m_pObjectMgr)
		return E_FAIL;

	return m_pObjectMgr->Add_GameObject(iLevel, strPrototypeTag, strLayerTag, pArg);
}

void CGameInstance::Clear(_uint iLevelIndex)
{
	if (nullptr == m_pObjectMgr)
		return;

	m_pObjectMgr->Clear(iLevelIndex);
}

#pragma endregion ObjectMgr

#pragma region ComponentMgr

HRESULT CGameInstance::Add_Prototype(_uint iLevelInex, const wstring& strPrototypeTag, CComponent* pPrototype)
{
	if (!m_pComponentMgr)
		return E_FAIL;

	return m_pComponentMgr->Add_Prototype(iLevelInex, strPrototypeTag, pPrototype);
}

CComponent* CGameInstance::Clone_Component(_uint iLevelIndex, const wstring& strPrototypeTag, void* pArg)
{
	if (!m_pComponentMgr)
		return nullptr;
	return m_pComponentMgr->Clone_Component(iLevelIndex, strPrototypeTag, pArg);
}

#pragma endregion ComponentMgr

#pragma region TimerMgr

HRESULT CGameInstance::Add_Timer(const wstring& strTimerTag)
{
	if (!m_pTimerMgr)
		return E_FAIL;

	return m_pTimerMgr->Add_Timer(strTimerTag);
}

_float CGameInstance::Compute_TimeDelta(const wstring& strTimerTag)
{
	if (!m_pTimerMgr)
		return 0.f;

	return m_pTimerMgr->Compute_TimeDelta(strTimerTag);
}

#pragma endregion TimerMgr

#pragma region InputMgr
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

const _float2& CGameInstance::GetMouseDir()
{
	return m_pInputMgr->GetMouseDir();
}

#pragma endregion InputMgr

void CGameInstance::Free()
{
	Safe_Release(m_pTimerMgr);
	Safe_Release(m_pInputMgr);
	Safe_Release(m_pObjectMgr);
	Safe_Release(m_pComponentMgr);
	Safe_Release(m_pLevelMgr);
	Safe_Release(m_pGraphic_Device);
}

void CGameInstance::Release_Engine()
{
	CGameInstance::DestroyInstance();
	CTimerMgr::DestroyInstance();
	CInputMgr::DestroyInstance();
	CObjectMgr::DestroyInstance();
	CComponentMgr::DestroyInstance();
	CLevelMgr::DestroyInstance();
	CGraphicDevice::DestroyInstance();
}
