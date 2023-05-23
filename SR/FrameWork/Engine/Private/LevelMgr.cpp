#include "LevelMgr.h"
#include "Level.h"
#include "GameInstance.h"

IMPLEMENT_SINGLETON(CLevelMgr)

CLevelMgr::CLevelMgr()
{
}

HRESULT CLevelMgr::Open_Level(_uint iLevelIndex, CLevel* pLevel)
{
	if (Safe_Release(m_pCurLevel) != 0)
	{
		MSG_BOX("Failed Release Scene : Open_Level , CLevelMgr");
		return E_FAIL;
	}

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	pGameInstance->Clear(m_iLevelIndex);

	Safe_Release(pGameInstance);

	m_pCurLevel = pLevel;

	m_iLevelIndex = iLevelIndex;

	return S_OK;
}

void CLevelMgr::Tick(_float fDeltaTime)
{
	if (m_pCurLevel)
		m_pCurLevel->Tick(fDeltaTime);
}

void CLevelMgr::Late_Tick(_float fDeltaTime)
{
	if (m_pCurLevel)
		m_pCurLevel->Late_Tick(fDeltaTime);
}

void CLevelMgr::Free()
{
	Safe_Release(m_pCurLevel);
}

