#pragma once
#include "define.h"


class Object
{
public:
	Object(int objectType);
	virtual ~Object();

public:
	virtual void PrintInfo() = 0;

protected:
	int m_iObjectType;
	StatInfo m_statInfo;
};

