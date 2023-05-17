#pragma once
#include "Base.h"


BEGIN(Engine)

class ENGINE_DLL CGraphicDevice :public CBase
{
	DECLARE_SINGLETON(CGraphicDevice)

private:
	CGraphicDevice();
	virtual ~CGraphicDevice() = default;

public:


public:
	HRESULT			Ready_GraphicDev(const GRAPHICDESC& graphicDesc, LPDIRECT3DDEVICE9* ppDevice);
	void			Render_Begin(void);
	void			Render_End();

	virtual void	Free() override;

	
private:
	void		SetParameters(D3DPRESENT_PARAMETERS& d3dpp, const GRAPHICDESC& graphicDesc);

private:
	LPDIRECT3D9			m_pSDK = nullptr; // 장치(그래픽 카드 성능) 조사할 객체
	LPDIRECT3DDEVICE9	m_pGraphicDev = nullptr; // 그래픽 장치를 통한 렌더링을 제어하는 객체

};

END