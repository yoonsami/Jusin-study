#include "Base.h"

CBase::CBase()
{
}

ULONG CBase::AddRef()
{
	return ++m_dwRefCount;
}

ULONG CBase::Release()
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
