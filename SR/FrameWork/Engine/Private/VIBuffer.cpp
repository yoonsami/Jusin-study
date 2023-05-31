#include "VIBuffer.h"

CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CComponent(pGraphic_Device)
{
}

CVIBuffer::CVIBuffer(const CVIBuffer& rhs)
	:CComponent(rhs)
{
	m_pVB = rhs.m_pVB;
	Safe_AddRef(m_pVB);
	m_pIB = rhs.m_pIB;
	Safe_AddRef(m_pIB);

	m_iVertexStride = rhs.m_iVertexStride;
	m_iNumVertices = rhs.m_iNumVertices;
	m_dwFVF = rhs.m_dwFVF;
	m_PrimitiveType = rhs.m_PrimitiveType; 
	m_iNumPrimitive = rhs.m_iNumPrimitive; 

	m_iIndexStride	= rhs.m_iIndexStride;
	m_iNumIndices  = rhs.m_iNumIndices;
	m_eIndexFormat = rhs.m_eIndexFormat;

}

HRESULT CVIBuffer::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CVIBuffer::Initialize(void* pArg)
{
	return S_OK;
}

HRESULT CVIBuffer::Render()
{
	if (!m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetStreamSource(0, m_pVB, 0, m_iVertexStride);
	m_pGraphic_Device->SetFVF(m_dwFVF);
	m_pGraphic_Device->SetIndices(m_pIB);
	m_pGraphic_Device->DrawIndexedPrimitive(m_PrimitiveType, 0, 0, m_iNumVertices,0, m_iNumPrimitive);
	return S_OK;
}

HRESULT CVIBuffer::Create_VertexBuffer()
{
	if (!m_pGraphic_Device)
		return E_FAIL;

	if (FAILED(m_pGraphic_Device->CreateVertexBuffer(m_iVertexStride * m_iNumVertices, 0, m_dwFVF, D3DPOOL_MANAGED, &m_pVB, 0)))
	{
		MSG_BOX("Failed to Create Vertex Buffer");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CVIBuffer::Create_IndexBuffer()
{
	if (!m_pGraphic_Device)
		return E_FAIL;

	if (FAILED(m_pGraphic_Device->CreateIndexBuffer(m_iIndexStride * m_iNumIndices, 0, m_eIndexFormat, D3DPOOL_MANAGED, &m_pIB, 0)))
	{
		MSG_BOX("Failed to Create Index Buffer");
		return E_FAIL;
	}

	return S_OK;
}

void CVIBuffer::Free()
{
	__super::Free();
	Safe_Release(m_pVB);
	Safe_Release(m_pIB);
}

