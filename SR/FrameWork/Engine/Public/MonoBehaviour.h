#pragma once
#include "Base.h"

BEGIN(Engine)
class ENGINE_DLL CMonoBehaviour abstract :
    public CBase
{
private:
protected:
	CMonoBehaviour(LPDIRECT3DDEVICE9 pGraphic_Device);
	CMonoBehaviour(const CMonoBehaviour& rhs);
	virtual ~CMonoBehaviour() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);

	virtual void Tick(_float fDeltaTime) = 0;
	virtual void Late_Tick(_float fDeltaTime) = 0;

protected:
	LPDIRECT3DDEVICE9 m_pGraphic_Device = nullptr;

public:
	virtual CMonoBehaviour* Clone(void* pArg) = 0;
	virtual void Free() override;

};

END