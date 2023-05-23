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

HRESULT CObjectMgr::Add_GameObject(const wstring& strPrototypeTag, const wstring& strLayerTag, _uint iLevel, void* pArg)
{
	CGameObject* prototype = Find_Prototype(strPrototypeTag);

	// prototype map 검색
	if (!prototype)
	{
		MSG_BOX("Failed Add_GameObject : CObjectMgr");
		return E_FAIL;
	}
	
	CGameObject* gameObject = prototype->Clone(pArg);
	if (!gameObject)
		return E_FAIL;

	CLayer* pLayer = Find_Layer(strLayerTag, iLevel);
	
	if (!pLayer)
	{
		pLayer = CLayer::Create();
		if (!pLayer)
			return E_FAIL;

		pLayer->Add_GameObject(gameObject);
		m_pLayer[iLevel].emplace(strLayerTag, pLayer);
	}
	else
		pLayer->Add_GameObject(gameObject);

	return S_OK;
}



void CObjectMgr::Tick(_float fDeltaTime)
{
	for (_uint i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayer[i])
		{
			if(Pair.second)
				Pair.second->Tick(fDeltaTime);
		}
	}
}

void CObjectMgr::Late_Tick(_float fDeltaTime)
{
	for (_uint i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayer[i])
		{
			if (Pair.second)
				Pair.second->Late_Tick(fDeltaTime);
		}
	}
}

CGameObject* CObjectMgr::Find_Prototype(const wstring& strPrototypeTag)
{
	auto iter = m_Prototypes.find(strPrototypeTag);

	if (iter == m_Prototypes.end())
		return nullptr;

	return iter->second;
}

CLayer* CObjectMgr::Find_Layer(const wstring& strLayerTag, _uint iLevel)
{
	if (iLevel >= m_iNumLevels)
		return nullptr;

	auto iter = m_pLayer[iLevel].find(strLayerTag);

	if (iter == m_pLayer[iLevel].end())
		return nullptr;


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
