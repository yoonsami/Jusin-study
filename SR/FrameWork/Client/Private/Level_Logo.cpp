#include "pch.h"
#include "Level_Logo.h"

#pragma region ENGINE_HEADER
#include "GameInstance.h"
#pragma endregion

#pragma region CLIENT_HEADER
#include "Level_Loading.h"
#pragma endregion

CLevel_Logo::CLevel_Logo(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel(pGraphic_Device)
{
}

HRESULT CLevel_Logo::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
		return E_FAIL;

	return S_OK;
}

void CLevel_Logo::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	
}

void CLevel_Logo::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (pGameInstance->GetButtonTap(KEY_TYPE::SPACE))
	{
		if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_GAMEPLAY))))
		{
			Safe_Release(pGameInstance);
			return;
		}
	}

	Safe_Release(pGameInstance);

	SetWindowText(g_hWnd, TEXT("로고레벨입니다."));
}

HRESULT CLevel_Logo::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_Logo::Ready_Layer_BackGround(const wstring& strLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	/* For.BackGround */
	if (FAILED(pGameInstance->Add_GameObject(
		TEXT("Prototype_GameObject_BackGround"), L"BackGround", LEVEL_LOGO)))
		return E_FAIL;

	Safe_Release(pGameInstance);
	return S_OK;
}

CLevel_Logo* CLevel_Logo::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLevel_Logo* pInstance = new CLevel_Logo(pGraphic_Device);

	if (FAILED(pInstance->Initialize()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Failed to Created : CLevel_Logo");
	}

	return pInstance;
}

void CLevel_Logo::Free()
{
	__super::Free();
}