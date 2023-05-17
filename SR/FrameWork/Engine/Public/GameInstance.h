#pragma once
#include "Base.h"

namespace Engine { class CLevel; }

namespace Engine { class CLevelMgr; }

namespace Engine { class CInputMgr; }

namespace Engine { class CGraphicDevice; }

BEGIN(Engine)

class ENGINE_DLL CGameInstance final :
    public CBase
{
    DECLARE_SINGLETON(CGameInstance)
private:
    CGameInstance();
    virtual ~CGameInstance() = default;

public: // for Engine
    HRESULT Initialize_Engine(const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut);

    void Tick_Engine(_float fDeltaTime);


public: // for GraphicDevice
	void		Render_Begin();
	void		Render_End();

public: // for InputMgr
	bool GetButtonHold(KEY_TYPE key);
	bool GetButtonTap(KEY_TYPE key);
	bool GetButtonAway(KEY_TYPE key);
    const POINT& GetMousePos();

public: // for LevelMgr
    HRESULT Open_Level(_uint iLevelIndex, CLevel* pLevel);


private:
    CInputMgr* m_pInputMgr = nullptr;
    CLevelMgr* m_pLevelMgr = nullptr;
    CGraphicDevice* m_pGraphic_Device = nullptr;

public:
    static void Release_Engine();
    virtual void Free() override;
};

END