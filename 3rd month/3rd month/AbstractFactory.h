#pragma once
#include "Object.h"
template<typename T>
class AbstractFactory
{
public:
	static Object* Create()
	{
		Object* pObj = new T;
		pObj->Init();
		return pObj;
	}

	static Object* Create(float _fX, float _fY, DIRECTION _dir)
	{
		Object* pObj = new T;
		pObj->Init();
		pObj->Set_PosDir(_fX, _fY, _dir);
		return pObj;
	}
};

