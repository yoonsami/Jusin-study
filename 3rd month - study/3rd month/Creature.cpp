#include "pch.h"
#include "Creature.h"

Creature::Creature(INT _CreatureType) : Object(OT_CREATURE), m_iCreatureType(_CreatureType)
{
	m_Ui.reserve(10);
}

Creature::Creature(const Creature& _player) : Object(_player), m_iCreatureType(0)
{
	
	m_iCreatureType = _player.m_iCreatureType;
	m_fSpeed = _player.m_fSpeed;
}

Creature::~Creature()
{

}

void Creature::Draw_Figure(HDC hDC)
{
	switch (m_eFigure)
	{
	case FIGURETYPE::FT_RECT:
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		break;
	case FIGURETYPE::FT_CIRCLE:
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		break;
	}
}
