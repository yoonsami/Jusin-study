#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Client)

class CBackGround final : public CGameObject
{
private:
	CBackGround(LPDIRECT3DDEVICE9 pGraphic_Device);
	CBackGround(const CBackGround& rhs);
	virtual ~CBackGround() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fDeltaTime) override;
	virtual void Late_Tick(_float fDeltaTime) override;
	virtual HRESULT Render() override;

public:
	static CBackGround* Create(LPDIRECT3DDEVICE9 pGrahpic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;



};

END