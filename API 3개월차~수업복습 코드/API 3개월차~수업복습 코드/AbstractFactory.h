#pragma once
#include "Object.h"
template <typename T>
class CAbstractFactory
{
public:
	static CObject* Create()
	{
		CObject* obj = new T;
		obj->Init();
		return obj;
	}
};

