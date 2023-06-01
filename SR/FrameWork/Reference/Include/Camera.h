#pragma once

#include "GameObject.h"
#include "Transform.h"

BEGIN(Engine)
class ENGINE_DLL CCamera abstract : public CGameObject
{
public:
	struct CAMERADESC
	{
		_uint iLevelIndex;
		wstring strTransformTag;
		_float3 vEye, vAt;
		_float fFovy, fAspect, fNear, fFar;
		CTransform::TRANSFORMDESC	TransformDesc;
	};

protected:
	CCamera(LPDIRECT3DDEVICE9 pGraphic_Device);
	CCamera(const CCamera& rhs);
	virtual ~CCamera() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;

protected:
	_float				m_fFovy, m_fAspect, m_fNear, m_fFar;
	class CTransform*	m_pTransformCom = { nullptr };

protected:
	HRESULT Set_Transform();


public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;


};


END