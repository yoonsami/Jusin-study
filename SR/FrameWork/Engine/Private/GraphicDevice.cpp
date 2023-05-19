#include "GraphicDevice.h"

IMPLEMENT_SINGLETON(CGraphicDevice)

CGraphicDevice::CGraphicDevice()
{
}

HRESULT CGraphicDevice::Ready_GraphicDev(const GRAPHICDESC& graphicDesc, LPDIRECT3DDEVICE9* ppDevice)
{
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9	DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		MSG_BOX("GetDeviceCaps Failed");
		return E_FAIL;
	}

	DWORD	vp = 0;

	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;

	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS	d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	SetParameters(d3dpp, graphicDesc);

	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, graphicDesc.hWnd, vp, &d3dpp, &m_pGraphicDev)))
	{
		MSG_BOX("CreateDevice Failed");
		return E_FAIL;  
	}

	*ppDevice = m_pGraphicDev;
	Safe_AddRef(m_pGraphicDev);

	return S_OK;
}

void CGraphicDevice::Render_Begin()
{
	m_pGraphicDev->Clear(0, nullptr,
		D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 125, 125, 125), 1.f, 0);

	m_pGraphicDev->BeginScene();
}

void CGraphicDevice::Render_End()
{
	m_pGraphicDev->EndScene();
	m_pGraphicDev->Present(nullptr, nullptr, nullptr, nullptr);
}

void CGraphicDevice::Free()
{
	Safe_Release(m_pGraphicDev);
	Safe_Release(m_pSDK);
}

void CGraphicDevice::SetParameters(D3DPRESENT_PARAMETERS& d3dpp, const GRAPHICDESC& graphicDesc)
{
	d3dpp.BackBufferWidth = graphicDesc.iSizeX;
	d3dpp.BackBufferHeight = graphicDesc.iSizeY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = graphicDesc.hWnd;
	d3dpp.Windowed = graphicDesc.eWinMode;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}
