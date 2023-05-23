#include "GameInstance.h"
#include "GraphicDevice.h"
#include "InputMgr.h"
#include "LevelMgr.h"
#include "ObjectMgr.h"
#include "GameObject.h"
#include "TimeMgr.h"

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
	if (FAILED(m_pObjectMgr->Reserve_ObjMgr(iNumLevels)))
	{
		MSG_BOX("Failed : Reserve_ObjMgr");
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

HRESULT CGameInstance::Open_Level(_uint iLevelIndex, CLevel* pLevel)
{
	if (!m_pLevelMgr)
		return E_FAIL;

	return m_pLevelMgr->Open_Level(iLevelIndex, pLevel);
}

HRESULT CGameInstance::Add_Prototype(const wstring& strPrototypeTag, CGameObject* pPrototype)
{
	if (!m_pObjectMgr)
		return E_FAIL;

	
	return m_pObjectMgr->Add_Prototype(strPrototypeTag,pPrototype);
}

HRESULT CGameInstance::Add_GameObject(const wstring& strPrototypeTag, const wstring& strLayerTag, _uint iLevel, void* pArg)
{
	if (!m_pObjectMgr)
		return E_FAIL;

	return m_pObjectMgr->Add_GameObject(strPrototypeTag, strLayerTag, iLevel, pArg);
}

void CGameInstance::Clear(_uint iLevelIndex)
{
	if (nullptr == m_pObjectMgr)
		return;

	m_pObjectMgr->Clear(iLevelIndex);
}

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

#pragma endregion

void CGameInstance::Free()
{
	Safe_Release(m_pInputMgr);
	Safe_Release(m_pObjectMgr);
	Safe_Release(m_pLevelMgr);
	Safe_Release(m_pGraphic_Device);
}

void CGameInstance::Release_Engine()
{
	CGameInstance::DestroyInstance();

	CInputMgr::DestroyInstance();
	CObjectMgr::DestroyInstance();
	CLevelMgr::DestroyInstance();

	CGraphicDevice::DestroyInstance();
}

