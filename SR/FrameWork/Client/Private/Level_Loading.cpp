#include "pch.h"
#include "Level_Loading.h"

#pragma region ENGINE_HEADER
#include "GameInstance.h"
#pragma endregion

#pragma region CLIENT_HEADER
#include "Loader.h"
#include "Level_Logo.h"
#include "Level_GamePlay.h"
#pragma endregion

CLevel_Loading::CLevel_Loading(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel(pGraphic_Device)
{
}

HRESULT CLevel_Loading::Initialize(LEVEL eNextLevel)
{

	if (FAILED(__super::Initialize()))
		return E_FAIL;

	m_pLoader = CLoader::Create(m_pGraphic_Device, eNextLevel);

	if (!m_pLoader)
		return E_FAIL;

	m_eNextLevel = eNextLevel;


	return S_OK;
}

void CLevel_Loading::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	
}

void CLevel_Loading::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (pGameInstance->GetButtonTap(KEY_TYPE::ENTER))
	{
		if (!m_pLoader->Is_Finished())
			return;

		CLevel* pLevel = nullptr;

		switch (m_eNextLevel)
		{
		case Client::LEVEL_LOGO:
			pLevel = CLevel_Logo::Create(m_pGraphic_Device);
			break;
		case Client::LEVEL_GAMEPLAY:
			pLevel = CLevel_GamePlay::Create(m_pGraphic_Device);
			break;
		}

		if (!pLevel)
			return;

		if (FAILED(pGameInstance->Open_Level(m_eNextLevel, pLevel)))
		{
			Safe_Release(pGameInstance);
			return;
		}
	}
	Safe_Release(pGameInstance);

	SetWindowText(g_hWnd, m_pLoader->Get_LoadingText());
}

HRESULT CLevel_Loading::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

CLevel_Loading* CLevel_Loading::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel)
{
	CLevel_Loading* pInstance = new CLevel_Loading(pGraphic_Device);

	if (FAILED(pInstance->Initialize(eNextLevel)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Failed to Created : CLevel_Loading");
	}

	return pInstance;
}

void CLevel_Loading::Free()
{
	__super::Free();

	Safe_Release(m_pLoader);
}
