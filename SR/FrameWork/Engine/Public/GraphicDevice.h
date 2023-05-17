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
	LPDIRECT3D9			m_pSDK = nullptr; // ��ġ(�׷��� ī�� ����) ������ ��ü
	LPDIRECT3DDEVICE9	m_pGraphicDev = nullptr; // �׷��� ��ġ�� ���� �������� �����ϴ� ��ü

};

END