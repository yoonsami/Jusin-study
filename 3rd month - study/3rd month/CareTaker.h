#pragma once
#include "Memento.h"


class CareTaker
{
public:
	~CareTaker();
public:
	list<Object*>* Update();
	void Release();
	void Push_back(Memento* memento) { m_MementoList.push_back(memento); }
	void Key_Input();
	void Set_PlayingIter();
	void Init() {NowPlayingIter = --m_MementoList.end();	}

public:

	list<Memento*>	m_MementoList;
	bool			SpacePressed = false;
	bool			RightPressed = false;
	bool			LeftPressed = false;
	bool			ZPressed = false;
	bool			XPressed = false;
	list<Memento*>::iterator NowPlayingIter;
	INT				CareTakerState = 1;
	
};

