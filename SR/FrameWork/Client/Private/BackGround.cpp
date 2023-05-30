#include "pch.h"
#include "BackGround.h"
#include "GameInstance.h"

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

HRESULT CBackGround::Initialize(void* pArg)
{
	if(FAILED(Add_Components()))
		return E_FAIL;


	_float4x4 matWorld, matView, matProj, matScale,matTrans;
	_float fSizeX, fSizeY, fX, fY;
	fSizeX = g_iWinSizeX;
	fSizeY = g_iWinSizeY;
	fX = 0.f + fSizeX * 0.5f;
	fY = 0.f + fSizeY * 0.5f;

	matWorld = *D3DXMatrixScaling(&matScale, fSizeX, fSizeY, 1.f) * *D3DXMatrixTranslation(&matTrans, fX - g_iWinSizeX * 0.5f, -fY + g_iWinSizeY * 0.5f, 0.f);

	D3DXMatrixIdentity(&matView);
	//D3DXMatrixIdentity(&matProj);
	
	//D3DXMatrixLookAtLH(&matView, &_float3(0.f, 0.f, -5.f), &_float3(0.f, 0.f, 0.f), &_float3(0.f, 1.f, 0.f));
	//D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(60.f), (_float)g_iWinSizeX / g_iWinSizeY, 0.2f, 300.f);

	D3DXMatrixOrthoLH(&matProj, g_iWinSizeX, g_iWinSizeY, 0.f, 1.f);

	m_pGraphic_Device->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &matProj);

	return S_OK;
}

void CBackGround::Tick(_float fDeltaTime)
{
	__super::Tick(fDeltaTime);
}

void CBackGround::Late_Tick(_float fDeltaTime)
{
	__super::Late_Tick(fDeltaTime);

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_PRIORITY, this);

}

HRESULT CBackGround::Render()
{
	if (!m_pVIBufferCom)
		return E_FAIL;
	
	if (FAILED(m_pTextureCom->Bind_OnGraphicDevice(0)))
		return E_FAIL;

	m_pVIBufferCom->Render();
	
	return S_OK;
}

HRESULT CBackGround::Add_Components()
{
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Renderer"),
		TEXT("Com_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"),
		TEXT("Com_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_LOGO, TEXT("Prototype_Component_Texture_BackGround"),
		TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;
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

CGameObject* CBackGround::Clone(void* pArg)
{
	CBackGround* pInstance = new CBackGround(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Failed to Clone : CBackGround");
	}
	return pInstance;
}

void CBackGround::Free()
{
	__super::Free();
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pTextureCom);

}

