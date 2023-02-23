#include "PCH.h"
#include "Game.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif


float Game::WorldGravity = 1.f;
float Game::WorldSpeed = 1.f;
float Game::COR = 0;//완전비탄성

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game game;
	game.Init();

	

	while (game.IsKeepPlaying())
	{
		game.Update();
		game.Render();
	}
}