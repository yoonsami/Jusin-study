#pragma once
#include "Component.h"

BEGIN(Engine)

class CTexture :
    public CComponent
{
private:
    CTexture(LPDIRECT3DDEVICE9 pGraphic_Device);
    virtual ~CTexture() = default;


public:
	virtual	HRESULT Initialize_Prototype() override;
	virtual	HRESULT Initialize(void* pArg) override;


public:
    virtual CComponent* Clone(void* pArg) = 0;
    virtual void Free() override;

};

END