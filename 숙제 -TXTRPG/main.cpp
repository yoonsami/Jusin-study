#include "PCH.h"
#include "Game.h"

float Game::WorldGravity = 1.f;
float Game::WorldSpeed = 1.f;
float Game::COR = 0;//������ź��

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