#pragma once
#include "Base.h"


BEGIN(Engine)

class ENGINE_DLL CDevice :public CBase
{
	DECLARE_SINGLETON(CDevice);

private:
	CDevice();
	virtual ~CDevice() = default;

public:


public:
	HRESULT		Create_Device(const GRAPHICDESC& graphicDesc, LPDIRECT3DDEVICE9* ppDevice);
	void		Render_Begin(void);
	void		Render_End();
	virtual void Free() override;

	
private:
	void		SetParameters(D3DPRESENT_PARAMETERS& d3dpp, const GRAPHICDESC& graphicDesc);

private:
	LPDIRECT3D9			m_pSDK = nullptr; // ��ġ(�׷��� ī�� ����) ������ ��ü
	LPDIRECT3DDEVICE9	m_pDevice = nullptr; // �׷��� ��ġ�� ���� �������� �����ϴ� ��ü

};

END