#include "pch.h"
#include "CareTaker.h"

CareTaker::~CareTaker()
{
	Release();
}

list<Object*>* CareTaker::Update()
{
	Key_Input();
	Set_PlayingIter();
	return (*NowPlayingIter)->m_objList;
}

void CareTaker::Release()
{
	for_each(m_MementoList.begin(), m_MementoList.end(), Safe_Delete<Memento*>);
}

void CareTaker::Key_Input()
{
	if ((GetAsyncKeyState(VK_RIGHT) == (SHORT)0x8000) && !LeftPressed && !RightPressed)
	{
		CareTakerState = clamp(++CareTakerState, CS_REPLAY, CS_PLAY);
		RightPressed = true;
	}
	if ((GetAsyncKeyState(VK_RIGHT) == (SHORT)0x0000) && RightPressed)
	{
		RightPressed = false;
	}

	if ((GetAsyncKeyState(VK_LEFT) == (SHORT)0x8000) && !RightPressed && !LeftPressed)
	{
		CareTakerState = clamp(--CareTakerState, CS_REPLAY, CS_PLAY);
		LeftPressed = true;
	}
	if ((GetAsyncKeyState(VK_LEFT) == (SHORT)0x0000) && LeftPressed)
	{
		LeftPressed = false;
	}
}

void CareTaker::Set_PlayingIter()
{
	if (CareTakerState == CS_REPLAY)
	{
		--NowPlayingIter;
		if (NowPlayingIter == m_MementoList.begin())
		 ++NowPlayingIter;
	}
	if (CareTakerState == CS_PLAY)
	{
		 ++NowPlayingIter;
		 if (NowPlayingIter == m_MementoList.end()) --NowPlayingIter;
	}
}
