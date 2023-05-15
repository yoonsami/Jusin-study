#pragma once

#include "Engine_Define.h"

BEGIN(Engine)

class ENGINE_DLL CBase abstract
{
protected:
	CBase();
	virtual ~CBase() = default;

public:
	ULONG AddRef();
	ULONG Release();


	virtual void Free() = 0;

private:
	ULONG m_dwRefCount = 0;
};

END