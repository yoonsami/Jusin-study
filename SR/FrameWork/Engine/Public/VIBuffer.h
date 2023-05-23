#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer abstract : public CComponent
{
protected:
	CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device);
	CVIBuffer(const CVIBuffer& rhs);
	virtual ~CVIBuffer() = default;

public:
	HRESULT Initialize_Prototype();
	HRESULT Initialize(void* pArg);

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVB = nullptr;
	LPDIRECT3DINDEXBUFFER9	m_pIB = nullptr;

public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END