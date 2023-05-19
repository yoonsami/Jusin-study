#pragma once
#include "Base.h"

BEGIN(Engine)
class CGameObject;
class CLayer;
class CObjectMgr final : public CBase
{
	DECLARE_SINGLETON(CObjectMgr)
private:
	CObjectMgr();
	virtual ~CObjectMgr() = default;

public:
	HRESULT Reserve_ObjMgr(_uint iNumLevels);
	HRESULT Add_Prototype(const wstring& strPrototypeTag, CGameObject* pPrototype);
	HRESULT Clone_GameObject(const wstring& strGameObjectTag, _uint iLevel);

	void Tick(_float fDeltaTime);
	void Late_Tick(_float fDeltaTime);


private: // 객체 원형 저장
	map<wstring, CGameObject*>			m_Prototypes;

private:
	_uint								m_iNumLevels = 0;
	map<wstring, CLayer*>*				m_pLayer = nullptr;
	using LAYERS = map<wstring, CLayer*>;

private:
	CGameObject*	Find_Prototype(const wstring& strPrototypeTag);
	CLayer*			Find_Layer(const wstring& strGameObjectTag, _uint iLevel);
public:
	virtual void Free() override;
};

END