#pragma once
#include "Include.h"
#include "Object.h"

class Memento
{
public:
	Memento(list<Object*>	objList[CT_END]);
	~Memento();

public:
	list<Object*>	m_objList[CT_END];

};

