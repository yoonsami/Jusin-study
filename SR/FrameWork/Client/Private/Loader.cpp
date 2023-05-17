#include "pch.h"
#include "Loader.h"

CLoader::CLoader(LPDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device(pGraphic_Device)
	, m_hThread(0)
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
	lstrcpy(m_szLoading, TEXT("�ؽ��ĸ� �ε� ���Դϴ�."));
	for (_uint i = 0; i < 999999999; ++i)
	{
		int a = 10;
	}

	lstrcpy(m_szLoading, TEXT("���� �ε� ���Դϴ�."));
	for (_uint i = 0; i < 999999999; ++i)
	{
		int a = 10;
	}

	lstrcpy(m_szLoading, TEXT("���̴��� �ε� ���Դϴ�."));
	for (_uint i = 0; i < 999999999; ++i)
	{
		int a = 10;
	}

	lstrcpy(m_szLoading, TEXT("��ü���� �ε� ���Դϴ�."));
	for (_uint i = 0; i < 999999999; ++i)
	{
		int a = 10;
	}

	lstrcpy(m_szLoading, TEXT("�ε��� �Ϸ�Ǿ����ϴ�."));

	m_bFinished = true;

	return S_OK;
}

HRESULT CLoader::Loading_ForGamePlay()
{
	lstrcpy(m_szLoading, TEXT("�ؽ��ĸ� �ε� ���Դϴ�."));
	for (_uint i = 0; i < 999999999; ++i)
	{
		int a = 10;
	}

	lstrcpy(m_szLoading, TEXT("���� �ε� ���Դϴ�."));
	for (_uint i = 0; i < 999999999; ++i)
	{
		int a = 10;
	}

	lstrcpy(m_szLoading, TEXT("���̴��� �ε� ���Դϴ�."));
	for (_uint i = 0; i < 999999999; ++i)
	{
		int a = 10;
	}

	lstrcpy(m_szLoading, TEXT("��ü���� �ε� ���Դϴ�."));
	for (_uint i = 0; i < 999999999; ++i)
	{
		int a = 10;
	}

	lstrcpy(m_szLoading, TEXT("�ε��� �Ϸ�Ǿ����ϴ�."));

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

	DeleteObject(m_hThread);

	DeleteCriticalSection(&m_CriticalSection);
}

