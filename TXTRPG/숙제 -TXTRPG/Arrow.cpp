#include "PCH.h"
#include "Arrow.h"
#include "Creature.h"
#include "Game.h"

Arrow::Arrow(Creature* owner, Creature* target)
	: _posCrd{}, _Vel{}, m_owner(owner), m_target(target), _startedPos{}, _flyingDistance(0)
{
	_startedPos = owner->GetPos();
	_posCrd = owner->GetPos();
}

Arrow::~Arrow()
{

}

void Arrow::FireArrow()
{
	if (m_owner->GetLookingDir() == RIGHT)
		_Vel._crdX += 1.f;
	else
		_Vel._crdX -= 1.f;
}

void Arrow::SetArrowPos()
{
	
	_posCrd._crdX += _Vel._crdX * Game::WorldSpeed;
	++_flyingDistance;
}

void Arrow::CorrectPos()
{
	
	
}

