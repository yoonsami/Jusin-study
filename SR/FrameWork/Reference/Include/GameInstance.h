#pragma once
#include "ComponentMgr.h"

BEGIN(Engine)

class CLevel;
class CObjectMgr;
class CLevelMgr;
class CInputMgr;
class CGraphicDevice;
class CGameObject;
class CTimeMgr;

class ENGINE_DLL CGameInstance final :
    public CBase
{
    DECLARE_SINGLETON(CGameInstance)
private:
    CGameInstance();
    virtual ~CGameInstance() = default;

public: // for Engine
    HRESULT Initialize_Engine(_uint iNumLevels, const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut);

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

public: // for ObjMgr
	HRESULT Add_Prototype(const wstring& strPrototypeTag, CGameObject* pPrototype);
	HRESULT Add_GameObject(_uint iLevel, const wstring& strPrototypeTag, const wstring& strLayerTag,void* pArg = nullptr);
    void Clear(_uint iLevelIndex);

public: // for ComponentMgr
	HRESULT Add_Prototype(_uint iLevelInex, const wstring& strPrototypeTag, CComponent* pPrototype);
	CComponent* Clone_Component(_uint iLevelIndex, const wstring& strPrototypeTag, void* pArg = nullptr);


private:

private:
	CInputMgr*          m_pInputMgr = nullptr;
	CLevelMgr*          m_pLevelMgr = nullptr;
    CObjectMgr*         m_pObjectMgr = nullptr;
    CComponentMgr*      m_pComponentMgr = nullptr;
    CGraphicDevice*     m_pGraphic_Device = nullptr;

public:
    static void Release_Engine();
    virtual void Free() override;
};

END