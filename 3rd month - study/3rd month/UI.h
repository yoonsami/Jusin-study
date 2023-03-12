#pragma once
#include "Include.h"
#include "Object.h"

class UI : public Object
{
public:
	UI(int uiType, Object* m_pOwner);
	virtual ~UI() {}


public:
	virtual void		Init()PURE;
	virtual int			Update()PURE;
	virtual void		Late_Update()PURE;
	virtual void		Render(HDC hDC)PURE;
	virtual void		Release()PURE;

public:

protected:
	INT			m_iUIType;
	Object*		m_pOwner;
};

