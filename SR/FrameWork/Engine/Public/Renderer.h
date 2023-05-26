#pragma once
#include "Component.h"

namespace Engine { class CGameObject; }

BEGIN(Engine)
class ENGINE_DLL CRenderer final :
    public CComponent
{
public:
    enum RENDERGROUP
    {
        RENDER_PRIORITY,
        RENDER_NONBLEND, 
        RENDER_BLEND, 
        RENDER_UI, 
        RENDER_END
    };

private:
    CRenderer(LPDIRECT3DDEVICE9 pGraphic_Device);
    virtual ~CRenderer() = default;


public:
	virtual HRESULT Initialize_Prototype() override;

public:
    HRESULT Add_RenderGroup(RENDERGROUP eRenderGroup,CGameObject* pGameObject);
    HRESULT Draw_RenderGroup();

private:
    HRESULT Render_Priority();
    HRESULT Render_NonBlend();
    HRESULT Render_Blend();
    HRESULT Render_UI();

private:
    list<CGameObject* > m_RenderGroup[RENDER_END];

public:
    static CRenderer* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
    virtual CComponent* Clone(void* pArg) override;
    virtual void Free() override;


};

END