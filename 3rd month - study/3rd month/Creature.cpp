#include "pch.h"
#include "Creature.h"

Creature::Creature()
{
	m_Ui.reserve(10);
}

Creature::~Creature()
{

}


void Creature::OnAttacked(Object& Attacker)
{
}
