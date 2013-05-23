#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <sstream>
#include "gameengine.hpp"
#include "mainmenustate.hpp"
#include "functions.hpp"

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
