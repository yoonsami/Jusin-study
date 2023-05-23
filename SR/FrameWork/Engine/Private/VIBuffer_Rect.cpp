#include "VIBuffer_Rect.h"

CVIBuffer_Rect::CVIBuffer_Rect(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CVIBuffer(pGraphic_Device)
{
}

CVIBuffer_Rect::CVIBuffer_Rect(const CVIBuffer& rhs)
	:CVIBuffer(rhs)
{
}

HRESULT CVIBuffer_Rect::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;
	return S_OK;
}

HRESULT CVIBuffer_Rect::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;
	return S_OK;
}

CVIBuffer_Rect* CVIBuffer_Rect::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Rect* pInstance = new CVIBuffer_Rect(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
		return nullptr;

	return pInstance;
}

CComponent* CVIBuffer_Rect::Clone(void* pArg)
{
	return nullptr;
}

void CVIBuffer_Rect::Free()
{
	__super::Free();
}
