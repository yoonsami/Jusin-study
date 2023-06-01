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

	m_fSizeX = g_iWinSizeX;
	m_fSizeY = g_iWinSizeY;
	m_fX = g_iWinSizeX * 0.5f;
	m_fY = g_iWinSizeY * 0.5f;

	_float4x4		Scaling, Translation;

	m_WorldMatrix = *D3DXMatrixScaling(&Scaling, m_fSizeX, m_fSizeY, 1.f) *
		*D3DXMatrixTranslation(&Translation, m_fX - g_iWinSizeX * 0.5f, -m_fY + g_iWinSizeY * 0.5f, 0.f);

	m_ViewMatrix = *D3DXMatrixIdentity(&m_ViewMatrix);

	D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinSizeX, g_iWinSizeY, 0.0f, 1.f);

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
	
	m_pGraphic_Device->SetTransform(D3DTS_WORLD, &m_WorldMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &m_ViewMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

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

