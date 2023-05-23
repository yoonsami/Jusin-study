#include "ObjectMgr.h"
#include "Layer.h"
#include "GameObject.h"

IMPLEMENT_SINGLETON(CObjectMgr)

CObjectMgr::CObjectMgr()
{
}

HRESULT CObjectMgr::Reserve_ObjMgr(_uint iNumLevels)
{
	if (m_pLayer)
	{
		MSG_BOX("ObjMgr Already Reserved");
		return E_FAIL;
	}
	m_iNumLevels = iNumLevels;

	m_pLayer = new LAYERS[m_iNumLevels];

	return S_OK;
}

HRESULT CObjectMgr::Add_Prototype(const wstring& strPrototypeTag, CGameObject* pPrototype)
{
	// map 
	if (Find_Prototype(strPrototypeTag) != nullptr)
	{
		MSG_BOX("Failed Add_Prototype : CObjectMgr");
		return E_FAIL;
	}

	m_Prototypes.emplace(strPrototypeTag, pPrototype);

	return S_OK;
}

HRESULT CObjectMgr::Clone_GameObject(const wstring& strGameObjectTag, _uint iLevel)
{
	CGameObject* prototype = Find_Prototype(strGameObjectTag);

	// prototype map 검색
	if (!prototype)
	{
		MSG_BOX("Failed Clone_GameObject : CObjectMgr");
		return E_FAIL;
	}
	
	CLayer* pLayer = Find_Layer(strGameObjectTag, iLevel);
	
	pLayer->Add_GameObject(prototype->Clone());

	return S_OK;
}



void CObjectMgr::Tick(_float fDeltaTime)
{
	int a = 10;
}

void CObjectMgr::Late_Tick(_float fDeltaTime)
{
}

CGameObject* CObjectMgr::Find_Prototype(const wstring& strPrototypeTag)
{
	auto iter = m_Prototypes.find(strPrototypeTag);

	if (iter == m_Prototypes.end())
		return nullptr;

	return iter->second;
}

CLayer* CObjectMgr::Find_Layer(const wstring& strGameObjectTag, _uint iLevel)
{
	auto iter = m_pLayer[iLevel].find(strGameObjectTag);

	if (iter == m_pLayer[iLevel].end())
	{
		CLayer* pLayer = CLayer::Create();
		m_pLayer[iLevel].emplace(strGameObjectTag, pLayer);
		return pLayer;
	}

	if (iter->second == nullptr)
		iter->second = CLayer::Create();

	return iter->second;
}



void CObjectMgr::Free()
{
	for (_uint i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayer[i])
		{
			Safe_Release(Pair.second);
		}
		m_pLayer[i].clear();
	}
	Safe_Delete_Array(m_pLayer);

	for (auto& Pair : m_Prototypes)
		Safe_Release(Pair.second);

	m_Prototypes.clear();

}
