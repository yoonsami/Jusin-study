#include "pch.h"
#include "Memento.h"
#include "Player.h"
#include "Monster.h"
#include "Bullet.h"

Memento::Memento(list<Object*> objList[CT_END])
{
	for (int i = 0; i < CT_END; ++i)
	{
		for (auto it = objList[i].begin(); it != objList[i].end(); ++it)
		{
			switch (i)
			{
			case CT_PLAYER:
				m_objList[i].push_back(new Player(*(dynamic_cast<Player*>(*it))));
				break;
			case CT_MONSTER:
				m_objList[i].push_back(new Monster(*(dynamic_cast<Monster*>(*it))));
				break;
			case CT_BULLET:
				m_objList[i].push_back(new Bullet(*(dynamic_cast<Bullet*>(*it))));
				break;
			}
		}
	}
	
}

Memento::~Memento()
{
	for (size_t i = 0; i < CT_END; ++i)
	{
		for_each(m_objList[i].begin(), m_objList[i].end(), Safe_Delete<Object*>);
	}
}
