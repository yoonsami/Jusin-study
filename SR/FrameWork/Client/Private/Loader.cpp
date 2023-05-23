#include "pch.h"
#include "Loader.h"
#include "GameInstance.h"
#include "BackGround.h"

CLoader::CLoader(LPDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device(pGraphic_Device)
	, m_hThread(INVALID_HANDLE_VALUE)
{
	Safe_AddRef(m_pGraphic_Device);
}

unsigned int APIENTRY ThreadEntry(void* pArg)
{
	CLoader* pLoader = (CLoader*)pArg;

	if (FAILED(pLoader->LoadingForNextLevel()))
		return 1;

	return 0;

}

HRESULT CLoader::Initialize(LEVEL eNextLevel)
{
	m_eNextLevel = eNextLevel;
	InitializeCriticalSection(&m_CriticalSection);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadEntry, this, 0, nullptr);

	if (0 == m_hThread)
		return E_FAIL;

	return S_OK;
}

HRESULT CLoader::LoadingForNextLevel()
{
	EnterCriticalSection(&m_CriticalSection);

	HRESULT hr{};
	switch (m_eNextLevel)
	{
	case Client::LEVEL_LOGO:
		hr = Loading_ForLogo();
		break;
	case Client::LEVEL_GAMEPLAY:
		hr = Loading_ForGamePlay();
		break;
	}

	LeaveCriticalSection(&m_CriticalSection);
	return hr;
}

HRESULT CLoader::Loading_ForLogo()
{
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	lstrcpy(m_szLoading, TEXT("텍스쳐를 로딩 중입니다."));


	lstrcpy(m_szLoading, TEXT("모델을 로딩 중입니다."));


	lstrcpy(m_szLoading, TEXT("셰이더를 로딩 중입니다."));


	lstrcpy(m_szLoading, TEXT("객체원형 로딩 중입니다."));

	/* For.Prototype_GameObject_BackGround */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BackGround"),
		CBackGround::Create(m_pGraphic_Device))))
		return E_FAIL;



	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다."));

	Safe_Release(pGameInstance);

	m_bFinished = true;

	return S_OK;
}

HRESULT CLoader::Loading_ForGamePlay()
{
	

	m_bFinished = true;

	return S_OK;
}

CLoader* CLoader::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel)
{
	CLoader* pInstance = new CLoader(pGraphic_Device);

	if (FAILED(pInstance->Initialize(eNextLevel)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Create Failed : CLoader");
	}

	return pInstance;
}

void CLoader::Free()
{
	Safe_Release(m_pGraphic_Device);

	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
	DeleteObject((m_hThread));

	DeleteCriticalSection(&m_CriticalSection);
}

