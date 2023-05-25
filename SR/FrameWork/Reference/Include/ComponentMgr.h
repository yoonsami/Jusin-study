#pragma once


#include "VIBuffer_Rect.h"


BEGIN(Engine)
class CComponentMgr :
    public CBase
{
    DECLARE_SINGLETON(CComponentMgr)

private:
    CComponentMgr();
    virtual ~CComponentMgr() = default;

public:
    HRESULT Reserve_Manager(_uint iNumLevels);
    HRESULT Add_Prototypes(_uint iLevelInex, const wstring& strPrototypeTag, CComponent* pPrototype);
    CComponent* Clone_Component(_uint iLevelIndex, const wstring& strPrototypeTag,void* pArg);

private:
    map<wstring, CComponent*>*   m_pPrototypes = nullptr;
    using PROTOTYPE = map<wstring, CComponent*>;

    _uint                       m_iNumLevels = 0;

    CComponent* Find_Prototype(_uint iLevelInex, const wstring& strPrototypeTag);

public:
    virtual void Free() override;



};

END