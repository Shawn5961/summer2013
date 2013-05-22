#include "gameengine.hpp"
#include "mainmenustate.hpp"

int main(int argc, char *argv[])
{
	GameEngine game;

	game.init("Game test");

	game.changeState(MainMenuState::instance());

	while( game.running() )
	{
		game.handleEvents();
		game.update();
		game.draw();
	}

	game.cleanup();

	return 0;
}
