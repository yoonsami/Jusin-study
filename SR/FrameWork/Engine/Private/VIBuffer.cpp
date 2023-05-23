#include "VIBuffer.h"

CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CComponent(pGraphic_Device)
{
}

CVIBuffer::CVIBuffer(const CVIBuffer& rhs)
	:CComponent(rhs)
{
}

HRESULT CVIBuffer::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CVIBuffer::Initialize(void* pArg)
{
	return S_OK;
}

void CVIBuffer::Free()
{
	__super::Free();
}

