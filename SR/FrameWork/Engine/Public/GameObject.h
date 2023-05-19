#pragma once
#include "Base.h"

BEGIN(Engine)
class ENGINE_DLL CGameObject abstract : public CBase
{
protected:
	CGameObject(LPDIRECT3DDEVICE9 pGraphic_Device);
	CGameObject(const CGameObject& rhs);
	virtual ~CGameObject() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize();
	virtual void Tick(_float fDeltaTime);
	virtual void Late_Tick(_float fDeltaTime);
	virtual HRESULT Render(_float fDeltaTime);

protected:
	LPDIRECT3DDEVICE9 m_pGraphic_Device = nullptr;


public:
	virtual CGameObject* Clone() = 0;
	virtual void Free() override;

};

END