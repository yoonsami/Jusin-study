#include "GameObject.h"
#include "GameInstance.h"

CGameObject::CGameObject(LPDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device(pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}

CGameObject::CGameObject(const CGameObject& rhs)
	: m_pGraphic_Device(rhs.m_pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}

CComponent* CGameObject::Find_Component(const wstring& strComTag)
{
	auto iter = m_Components.find(strComTag);
	if (iter == m_Components.end())
		return nullptr;
	return iter->second;
}

HRESULT CGameObject::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CGameObject::Initialize(void* pArg)
{
	return S_OK;
}

void CGameObject::Tick(_float fDeltaTime)
{
}

void CGameObject::Late_Tick(_float fDeltaTime)
{
}

HRESULT CGameObject::Render()
{
	return S_OK;
}

HRESULT CGameObject::Add_Component(_uint iLevelIndex, const wstring& strPrototypeTag, const wstring& strComTag, CComponent** ppOut, void* pArg)
{
	if (Find_Component(strComTag))
		return E_FAIL;

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CComponent* pClone  = pGameInstance->Clone_Component(iLevelIndex, strPrototypeTag, pArg);

	if (pClone == nullptr)
		return E_FAIL;

	m_Components.emplace(strComTag, pClone);

	*ppOut = pClone;
	Safe_AddRef(pClone);

	Safe_Release(pGameInstance);

	return S_OK;
}

void CGameObject::Free()
{
	for (auto& Pair : m_Components)
		Safe_Release(Pair.second);

	m_Components.clear();

	Safe_Release(m_pGraphic_Device);
}
