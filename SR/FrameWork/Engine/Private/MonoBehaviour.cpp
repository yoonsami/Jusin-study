#include "MonoBehaviour.h"

CMonoBehaviour::CMonoBehaviour(LPDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device(pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}

CMonoBehaviour::CMonoBehaviour(const CMonoBehaviour& rhs)
	: m_pGraphic_Device(rhs.m_pGraphic_Device)
{
}

HRESULT CMonoBehaviour::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CMonoBehaviour::Initialize(void* pArg)
{
	return S_OK;
}

void CMonoBehaviour::Free()
{
	Safe_Release(m_pGraphic_Device);
}
