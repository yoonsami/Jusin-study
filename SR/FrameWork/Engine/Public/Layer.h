#pragma once

#include "Base.h"
BEGIN(Engine)
class CGameObject;
class CLayer final : public CBase
{
private:
	CLayer();
	virtual ~CLayer() = default;

public:
	void Add_GameObject(CGameObject* gameObject) { m_GameObject.push_back(gameObject); }

private:
	list<CGameObject*>		m_GameObject;



public:
	static CLayer* Create();
	virtual void Free() override;
};

END