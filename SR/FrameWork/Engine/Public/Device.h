#pragma once
#include "Base.h"

class ENGINE_DLL CDevice :public CBase
{
	DECLARE_SINGLETON(CDevice);

private:
	CDevice();
	virtual ~CDevice() = default;

public:
	LPDIRECT3DDEVICE9		Get_Device(void) { return m_pDevice; }
	LPD3DXSPRITE			Get_Sprite(void) { return m_pSprite; }
	LPD3DXFONT				Get_Font(void) { return m_pFont; }

public:
	HRESULT		Create(HWND hWnd);
	void		Render_Begin(void);
	void		Render_End(HWND hWnd = nullptr);
	virtual void Free() override;

	
private:
	void		SetParameters(D3DPRESENT_PARAMETERS& d3dpp);

private:
	LPDIRECT3D9			m_pSDK = nullptr; // ��ġ(�׷��� ī�� ����) ������ ��ü
	LPDIRECT3DDEVICE9	m_pDevice = nullptr; // �׷��� ��ġ�� ���� �������� �����ϴ� ��ü
	LPD3DXSPRITE		m_pSprite = nullptr;
	LPD3DXFONT			m_pFont = nullptr;

	HWND				m_hWnd = nullptr;

};

