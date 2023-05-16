#pragma once

#include "Engine_Define.h"

BEGIN(Engine)

class ENGINE_DLL CBase abstract
{
protected:
	CBase();
	virtual ~CBase() = default;

public:
	_ulong AddRef();
	_ulong Release();


	virtual void Free() = 0;

private:
	_ulong m_dwRefCount = 0;
};

END