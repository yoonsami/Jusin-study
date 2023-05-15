#pragma once
#include "Base.h"

namespace Engine { class CGraphicDevice; }

BEGIN(Engine)

class ENGINE_DLL CGameInstance final :
    public CBase
{
    DECLARE_SINGLETON(CGameInstance);
private:
    CGameInstance();
    virtual ~CGameInstance() = default;

public: // for Engine
    HRESULT Initialize_Engine(const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut);

public: // for GraphicDevice
	void		Render_Begin();
	void		Render_End();

private:

    CGraphicDevice* m_pDevice = nullptr;
public:
    virtual void Free() override;
};

END