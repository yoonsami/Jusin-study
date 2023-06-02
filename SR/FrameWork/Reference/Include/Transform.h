#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CTransform final : public CComponent
{
public:
	enum STATE { STATE_RIGHT, STATE_UP, STATE_LOOK, STATE_POSITION, STATE_END };
public:
	struct TRANSFORMDESC
	{
		_float		fSpeedPerSec = { 0.0f };
		_float		fRotationPerSec = { 0.0f };
	};
protected:
	CTransform(LPDIRECT3DDEVICE9 pGraphic_Device);
	CTransform(const CTransform& rhs);
	virtual ~CTransform() = default;

public:
	_float3 Get_State(STATE eState) const {
		return *(_float3*)&m_WorldMatrix.m[eState][0];
	}
	_float3 Get_Scaled() const;
	_float4x4 Get_WorldMatrix() {
		return m_WorldMatrix;
	}
	_float4x4 Get_WorldMatrix_Inverse() {
		_float4x4	InverseMatrix;
		return *D3DXMatrixInverse(&InverseMatrix, nullptr, &m_WorldMatrix);
	}

	void Set_State(STATE eState, const _float3& vState) {
		memcpy(&m_WorldMatrix.m[eState][0], &vState, sizeof(_float3));
	}

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	void Go_Straight(_float fTimeDelta);
	void Go_Left(_float fTimeDelta);
	void Go_Right(_float fTimeDelta);
	void Go_Backward(_float fTimeDelta);
	void Turn(const _float3& vAxis, _float fTimeDelta);
	void Rotation(const _float3& vAxis, _float fRadian ); 
	void Scaling(const _float3& vScale);
	void LookAt(const _float3& vAt);
	

private:
	_float4x4			m_WorldMatrix;
	TRANSFORMDESC		m_TransformDesc;


public:
	static CTransform* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;

};

END