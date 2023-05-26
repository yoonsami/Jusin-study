#pragma once
#include "Base.h"

namespace Engine { class CComponent; }

BEGIN(Engine)
class ENGINE_DLL CGameObject abstract : public CBase
{
protected:
	CGameObject(LPDIRECT3DDEVICE9 pGraphic_Device);
	CGameObject(const CGameObject& rhs);
	virtual ~CGameObject() = default;

public:
	CComponent* Find_Component(const wstring& strComTag);


public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Tick(_float fDeltaTime);
	virtual void Late_Tick(_float fDeltaTime);
	virtual HRESULT Render();

protected:
	LPDIRECT3DDEVICE9 m_pGraphic_Device = nullptr;
	map<wstring, CComponent*> m_Components;

protected:
	HRESULT Add_Component(_uint iLevelIndex, const wstring& strPrototypeTag, const wstring& strComTag, CComponent** ppOut, void* pArg = nullptr);
	



public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;

};

END