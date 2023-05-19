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
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize();
	virtual void Tick(_float fDeltaTime);
	virtual void Late_Tick(_float fDeltaTime);
	virtual HRESULT Render(_float fDeltaTime);

public:
	static CBackGround* Create(LPDIRECT3DDEVICE9 pGrahpic_Device);
	virtual CGameObject* Clone() override;
	virtual void Free() override;

};

END