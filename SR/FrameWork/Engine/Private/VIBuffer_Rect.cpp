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

	m_iNumVertices = 4;
	m_iNumIndices = 6;

	m_iVertexStride = sizeof(VTXPOSTEX);
	m_iIndexStride = m_iNumVertices > 65535 ? sizeof(_ulong) : sizeof(_ushort);

	m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0);
	m_PrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitive = 2;

	m_eIndexFormat = m_iIndexStride == sizeof(_ushort) ? D3DFMT_INDEX16 : D3DFMT_INDEX32;

	if (FAILED(__super::Create_VertextBuffer()))
		return E_FAIL;

	

	VTXPOSTEX* pVertices =  nullptr ;
	
	m_pVB->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].vPosition = { -0.5f,0.5f,0.f };
	pVertices[0].vTexcoord = { 0.f,0.f };

	pVertices[1].vPosition = { 0.5f,0.5f,0.f };
	pVertices[1].vTexcoord = { 1.f,0.f };

	pVertices[2].vPosition = { 0.5f,-0.5f,0.f };
	pVertices[2].vTexcoord = { 1.f,1.f };

	pVertices[3].vPosition = { -0.5f,-0.5f,0.f };
	pVertices[3].vTexcoord = { 0.f,1.f };

	m_pVB->Unlock();

	if (FAILED(__super::Create_IndexBuffer()))
		return E_FAIL;

	if(m_eIndexFormat == D3DFMT_INDEX16)
	{
		_ushort* pIndices = nullptr;

		m_pIB->Lock(0, 0, (void**)&pIndices, 0);

		pIndices[0] = 0;
		pIndices[1] = 1;
		pIndices[2] = 2;
		pIndices[3] = 0;
		pIndices[4] = 2;
		pIndices[5] = 3;

	}
	else if(m_eIndexFormat == D3DFMT_INDEX32)     
	{
		_ulong* pIndices = nullptr;

		m_pIB->Lock(0, 0, (void**)&pIndices, 0);

		pIndices[0] = 0;
		pIndices[1] = 1;
		pIndices[2] = 2;
		pIndices[3] = 0;
		pIndices[4] = 2;
		pIndices[5] = 3;
	}
	
	m_pIB->Unlock();

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
	{
		MSG_BOX("Failed to Create : CVIBuffer_Rect");
		Safe_Release(pInstance);		
	}

	return pInstance;
}

CComponent* CVIBuffer_Rect::Clone(void* pArg)
{
	CVIBuffer_Rect* pClone = new CVIBuffer_Rect(*this);
	if (FAILED(pClone->Initialize(pArg)))
	{
		MSG_BOX("Failed to Clone : CVIBuffer_Rect");
		Safe_Release(pClone);
	}
	return pClone;
}

void CVIBuffer_Rect::Free()
{
	__super::Free();
}
