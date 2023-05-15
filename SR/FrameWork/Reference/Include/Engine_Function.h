#pragma once

namespace Engine
{
	template<typename T>
	ULONG Safe_AddRef(T& pInstance)
	{
		ULONG dwRefCount = 0;
		if (pInstance != nullptr)
		{
			dwRefCount = pInstance->AddRef();
		}

		return dwRefCount;
	}

	template<typename T>
	ULONG Safe_Release(T& pInstance)
	{
		ULONG dwRefCount = 0;
		if (pInstance != nullptr)
		{
			dwRefCount = pInstance->Release();
			if (dwRefCount == 0)
				pInstance = nullptr;
		}
		return dwRefCount;
	}

	template<typename T>
	void Safe_Delete(T& pPointer)
	{
		if (pPointer != nullptr)
		{
			delete pPointer;
			pPointer = nullptr;
		}
	}

}