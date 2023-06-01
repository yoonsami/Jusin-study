#include "Camera.h"
#include "ComponentMgr.h"

CCamera::CCamera(LPDIRECT3DDEVICE9 pGraphic_Device)
    :CGameObject(pGraphic_Device)
{
}

CCamera::CCamera(const CCamera& rhs)
    : CGameObject(rhs)
{
}

HRESULT CCamera::Initialize_Prototype()
{
    return S_OK;
}

HRESULT CCamera::Initialize(void* pArg)
{
    CAMERADESC* pCameraDesc = (CAMERADESC*)pArg;

    CComponentMgr* pComponentMgr = CComponentMgr::GetInstance();
    Safe_AddRef(pComponentMgr);

    m_pTransformCom = (CTransform*)pComponentMgr->Clone_Component(pCameraDesc->iLevelIndex, pCameraDesc->strTransformTag, &pCameraDesc->TransformDesc);
    if (!m_pTransformCom)
        return E_FAIL;

    Safe_Release(pComponentMgr);

    m_pTransformCom->Set_State(CTransform::STATE_POSITION, pCameraDesc->vEye);
    m_pTransformCom->LookAt(pCameraDesc->vAt);

    m_fFovy = pCameraDesc->fFovy;
    m_fAspect = pCameraDesc->fAspect;
    m_fNear = pCameraDesc->fNear;
    m_fFar = pCameraDesc->fFar;

    return S_OK;
}

void CCamera::Tick(_float fTimeDelta)
{
}

void CCamera::Late_Tick(_float fTimeDelta)
{
}

HRESULT CCamera::Set_Transform()
{
    if (!m_pGraphic_Device)
        return E_FAIL;
    
    m_pGraphic_Device->SetTransform(D3DTS_VIEW, &m_pTransformCom->Get_WorldMatrix_Inverse());

    _float4x4 matProj;
    m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, D3DXMatrixPerspectiveFovLH(&matProj, m_fFovy, m_fAspect, m_fNear, m_fFar));
    
    return E_NOTIMPL;
}

void CCamera::Free()
{
    __super::Free();
    Safe_Release(m_pTransformCom);
}
