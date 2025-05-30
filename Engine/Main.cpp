#include <iostream>

#include "GameSystem.h"


int main()
{
	Game game;

	game.Setup();

	game.Start();

	game.Run();

	game.End();


	return 0;
}
