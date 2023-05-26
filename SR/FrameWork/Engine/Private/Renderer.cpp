#include "Renderer.h"
#include "GameObject.h"

CRenderer::CRenderer(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CComponent(pGraphic_Device)
{
}

HRESULT CRenderer::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;
	return S_OK;
}

HRESULT CRenderer::Add_RenderGroup(RENDERGROUP eRenderGroup, CGameObject* pGameObject)
{
	if (eRenderGroup >= RENDER_END || eRenderGroup < 0)
		return E_FAIL;

	m_RenderGroup[eRenderGroup].push_back(pGameObject);
	Safe_AddRef(pGameObject);
	return S_OK;
}

HRESULT CRenderer::Draw_RenderGroup()
{
	if (FAILED(Render_Priority()))
		return E_FAIL;

	if (FAILED(Render_NonBlend()))
		return E_FAIL;

	if (FAILED(Render_Blend()))
		return E_FAIL;

	if (FAILED(Render_UI()))
		return E_FAIL;



	return S_OK;
}

HRESULT CRenderer::Render_Priority()
{
	for (auto& pGameObject : m_RenderGroup[RENDER_PRIORITY])
	{
		if(pGameObject)
			pGameObject->Render();
		Safe_Release(pGameObject);
	}
	m_RenderGroup[RENDER_PRIORITY].clear();
	return S_OK;
}

HRESULT CRenderer::Render_NonBlend()
{
	for (auto& pGameObject : m_RenderGroup[RENDER_NONBLEND])
	{
		if (pGameObject)
			pGameObject->Render();
		Safe_Release(pGameObject);
	}
	m_RenderGroup[RENDER_NONBLEND].clear();
	return S_OK;
}

HRESULT CRenderer::Render_Blend()
{
	for (auto& pGameObject : m_RenderGroup[RENDER_BLEND])
	{
		if (pGameObject)
			pGameObject->Render();
		Safe_Release(pGameObject);
	}
	m_RenderGroup[RENDER_BLEND].clear();
	return S_OK;
}

HRESULT CRenderer::Render_UI()
{
	for (auto& pGameObject : m_RenderGroup[RENDER_UI])
	{
		if (pGameObject)
			pGameObject->Render();
		Safe_Release(pGameObject);
	}
	m_RenderGroup[RENDER_UI].clear();
	return S_OK;
}

CRenderer* CRenderer::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CRenderer* pInstance = new CRenderer(pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Create : CRenderer");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CRenderer::Clone(void* pArg)
{
	AddRef();
	return this;
}

void CRenderer::Free()
{
	__super::Free();
	for (int i = 0; i < RENDER_END; ++i)
	{
		for (auto& pGameObejct : m_RenderGroup[i])
			Safe_Release(pGameObejct);
		m_RenderGroup[i].clear();
	}
}
