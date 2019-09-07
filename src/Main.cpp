#include "core/Game.h"

// Calling point of the program
// It creates an instance of the game and runs it

int main() 
{	
	Game game(1280,720);
	game.run();

	return 0;
}