#include "Base.h"

CBase::CBase()
{
}

_ulong CBase::AddRef()
{
	return ++m_dwRefCount;
}

_ulong CBase::Release()
{
	if (m_dwRefCount == 0)
	{

		Free();

		delete this;

		return 0;
	}
	else
		return m_dwRefCount--;
}
