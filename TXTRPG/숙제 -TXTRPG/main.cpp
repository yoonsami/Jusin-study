#include "PCH.h"
#include "Game.h"

float Game::WorldGravity = 1.f;
float Game::WorldSpeed = 1.f;
float Game::COR = 0;//완전비탄성

int main()
{
	Game game;
	game.Init();

	

	while (game.IsKeepPlaying())
	{
		game.Update();
		game.Render();
	}
}