#pragma once
#include "Include.h"
#include "Object.h"

class UI : public Object
{
public:
	UI(int uiType);
	virtual ~UI() {}


public:
	virtual void		Init()PURE;
	virtual int			Update()PURE;
	virtual void		Late_Update()PURE;
	virtual void		Render(HDC hDC)PURE;
	virtual void		Release()PURE;

public:

protected:
	INT			m_iUIType	= 0;
	Object*		m_pOwner	= nullptr;
};

