#include "pch.h"
#include "BackGround.h"

CBackGround::CBackGround(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CBackGround::CBackGround(const CBackGround& rhs)
	:CGameObject(rhs)
{
}

HRESULT CBackGround::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CBackGround::Initialize()
{
	return S_OK;
}

void CBackGround::Tick(_float fDeltaTime)
{
}

void CBackGround::Late_Tick(_float fDeltaTime)
{
}

HRESULT CBackGround::Render(_float fDeltaTime)
{
	return S_OK;
}

CBackGround* CBackGround::Create(LPDIRECT3DDEVICE9 pGrahpic_Device)
{
	CBackGround* pInstance = new CBackGround(pGrahpic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Failed to Create : CBackGround");
	}
	return pInstance;
}

CGameObject* CBackGround::Clone()
{
	CBackGround* pInstance = new CBackGround(*this);

	if (FAILED(pInstance->Initialize()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Failed to Clone : CBackGround");
	}
	return pInstance;
}

void CBackGround::Free()
{
}

