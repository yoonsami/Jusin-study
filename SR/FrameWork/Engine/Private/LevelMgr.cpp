#include "LevelMgr.h"
#include "Level.h"

IMPLEMENT_SINGLETON(CLevelMgr)

CLevelMgr::CLevelMgr()
{
}

HRESULT CLevelMgr::Open_Level(_uint iLevelIndex, CLevel* pLevel)
{
	if (Safe_Release(m_pCurLevel) != 0)
		return E_FAIL;

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

