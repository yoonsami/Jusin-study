#include "VIBuffer_Cube.h"

CVIBuffer_Cube::CVIBuffer_Cube(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CVIBuffer(pGraphic_Device)
{
}

CVIBuffer_Cube::CVIBuffer_Cube(const CVIBuffer& rhs)
	:CVIBuffer(rhs)
{
}

HRESULT CVIBuffer_Cube::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	m_iNumVertices = 6;
	m_iVertexStride = sizeof(VTXPOSTEX);

	m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0);
	m_PrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitive = 2;

	if (FAILED(__super::Create_VertextBuffer()))
		return E_FAIL;

	VTXPOSTEX* pVertices =  nullptr ;
	
	m_pVB->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].vPosition = { -0.5f,0.5f,0.f };
	pVertices[0].vTexcoord = { 0.f,0.f };


	m_pVB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_Cube::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;
	return S_OK;
}

CVIBuffer_Cube* CVIBuffer_Cube::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Cube* pInstance = new CVIBuffer_Cube(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Create : CVIBuffer_Cube");
		Safe_Release(pInstance);		
	}

	return pInstance;
}

CComponent* CVIBuffer_Cube::Clone(void* pArg)
{
	CVIBuffer_Cube* pClone = new CVIBuffer_Cube(*this);
	if (FAILED(pClone->Initialize(pArg)))
	{
		MSG_BOX("Failed to Clone : CVIBuffer_Cube");
		Safe_Release(pClone);
	}
	return pClone;
}

void CVIBuffer_Cube::Free()
{
	__super::Free();
}
