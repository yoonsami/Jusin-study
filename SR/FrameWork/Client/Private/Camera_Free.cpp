#include "pch.h"
#include "Camera_Free.h"

#include "GameInstance.h"
#include "InputMgr.h"

CCamera_Free::CCamera_Free(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCamera(pGraphic_Device)
{

}

CCamera_Free::CCamera_Free(const CCamera_Free& rhs)
	: CCamera(rhs)
{

}

HRESULT CCamera_Free::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCamera_Free::Initialize(void* pArg)
{
	CAMERAFREEDESC* pCameraFreeDesc = (CAMERAFREEDESC*)pArg;

	m_iData = pCameraFreeDesc->iData;

	if (FAILED(__super::Initialize(&pCameraFreeDesc->CameraDesc)))
		return E_FAIL;

	return S_OK;
}

void CCamera_Free::Tick(_float fTimeDelta)
{
	if (GetKeyState('W') & 0x8000)
	{
		m_pTransform->Go_Straight(fTimeDelta);
	}
	if (GetKeyState('S') & 0x8000)
	{
		m_pTransform->Go_Backward(fTimeDelta);
	}

	if (GetKeyState('A') & 0x8000)
	{
		m_pTransform->Go_Left(fTimeDelta);
	}

	if (GetKeyState('D') & 0x8000)
	{
		m_pTransform->Go_Right(fTimeDelta);
	}

	const _float2& mouseDir = CInputMgr::GetInstance()->GetMouseDir();

	if(mouseDir.x)
		m_pTransform->Turn(_float3(0.f,1.f,0.f), fTimeDelta * mouseDir.x);

	if(mouseDir.y)
		m_pTransform->Turn(m_pTransform->Get_State(CTransform::STATE_RIGHT), fTimeDelta * mouseDir.y);


	__super::Set_Transform();

}

void CCamera_Free::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

}

CCamera_Free* CCamera_Free::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CCamera_Free* pInstance = new CCamera_Free(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Failed to Created : CCamera_Free");
	}

	return pInstance;
}

CGameObject* CCamera_Free::Clone(void* pArg)
{
	CCamera_Free* pInstance = new CCamera_Free(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Failed to Cloned : CCamera_Free");
	}

	return pInstance;
}

void CCamera_Free::Free()
{
	__super::Free();



}
