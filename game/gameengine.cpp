#include <stdio.h>
#include <SDL/SDL.h>
#include "gameengine.hpp"
#include "gamestate.hpp"

void GameEngine::init(const char* title, int width, int height, int bpp, bool fullscreen)
{
	int flags = 0;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_WM_SetCaption(title, title);

	if( fullscreen )
	{
		flags = SDL_FULLSCREEN;
	}

	screen = SDL_SetVideoMode(width, height, bpp, flags);

	game_fullscreen = fullscreen;
	game_running = true;

	printf("GameEngine init\n");
}

void GameEngine::cleanup()
{
	while( !states.empty() )
	{
		states.back()->cleanup();
		states.pop_back();
	}

	if( game_fullscreen)
	{
		screen = SDL_SetVideoMode(640, 480, 0, 0);
	}

	printf("GameEngine cleanup\n");

	SDL_Quit();
}

void GameEngine::changeState(GameState* state)
{
	if( !states.empty() )
	{
		states.back()->cleanup();
		states.pop_back();
	}

	states.push_back(state);
	states.back()->init();
}

void GameEngine::pushState(GameState* state)
{
	if( !states.empty() )
	{
		states.back()->pause();
	}

	states.push_back(state);
	states.back()->init();
}

void GameEngine::popState()
{
	if( !states.empty() )
	{
		states.back()->cleanup();
		states.pop_back();
	}

	if( !states.empty() )
	{
		states.back()->resume();
	}
}

void GameEngine::handleEvents()
{
	states.back()->handleEvents(this);
}

void GameEngine::update()
{
	states.back()->update(this);
}

void GameEngine::draw()
{
	states.back()->draw(this);
}

bool GameEngine::running()
{
	return game_running;
}

void GameEngine::quit()
{
	game_running = false;
}
