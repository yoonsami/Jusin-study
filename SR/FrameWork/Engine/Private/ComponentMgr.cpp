#include "ComponentMgr.h"

IMPLEMENT_SINGLETON(CComponentMgr)

CComponentMgr::CComponentMgr()
{
}

HRESULT CComponentMgr::Reserve_Manager(_uint iNumLevels)
{
	if (m_pPrototypes)
		return E_FAIL;

	m_iNumLevels = iNumLevels;

	m_pPrototypes = new PROTOTYPE[iNumLevels];

	return S_OK;
}

HRESULT CComponentMgr::Add_Prototypes(_uint iLevelInex, const wstring& strPrototypeTag, CComponent* pPrototype)
{
	if (iLevelInex >= m_iNumLevels)
		return E_FAIL;

	if (Find_Prototype(iLevelInex, strPrototypeTag))
		return E_FAIL;

	m_pPrototypes[iLevelInex].emplace(strPrototypeTag, pPrototype);

	return S_OK;
}

CComponent* CComponentMgr::Clone_Component(_uint iLevelIndex, const wstring& strPrototypeTag, void* pArg)
{
	if (iLevelIndex >= m_iNumLevels)
		return nullptr;

	CComponent* pPrototype = Find_Prototype(iLevelIndex, strPrototypeTag);

	if (!pPrototype)
		return nullptr;

	return pPrototype->Clone(pArg);

}

CComponent* CComponentMgr::Find_Prototype(_uint iLevelInex, const wstring& strPrototypeTag)
{
	if (iLevelInex >= m_iNumLevels)
		return nullptr;

	auto iter = m_pPrototypes[iLevelInex].find(strPrototypeTag);
	if (iter == m_pPrototypes[iLevelInex].end())
		return nullptr;

	return iter->second;
}

void CComponentMgr::Free()
{
	for (_uint i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pPrototypes[i])
			Safe_Release(Pair.second);
		m_pPrototypes[i].clear();
	}

	Safe_Delete_Array(m_pPrototypes);
}
