#include "Layer.h"
#include "GameObject.h"

CLayer::CLayer()
{
}

void CLayer::Tick(_float fDeltaTime)
{
	for (auto& gameObject : m_GameObject)
		if (gameObject)
			gameObject->Tick(fDeltaTime);
}

void CLayer::Late_Tick(_float fDeltaTime)
{
	for (auto& gameObject : m_GameObject)
		if (gameObject)
			gameObject->Late_Tick(fDeltaTime);
}

CLayer* CLayer::Create()
{
	CLayer* pInstance = new CLayer;

	return pInstance;
}

void CLayer::Free()
{
	for (auto& pGameObject : m_GameObject)
		Safe_Release(pGameObject);
}

