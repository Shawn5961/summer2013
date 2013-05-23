#include <stdio.h>
#include <string>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "gameengine.hpp"
#include "gamestate.hpp"
#include "mainmenustate.hpp"
#include "worldmapstate.hpp"
#include "functions.hpp"

MainMenuState MainMenuState::game_MainMenuState;

void MainMenuState::init()
{
	bg			= load_image("images/mainmenu/bg.png");
	cursor		= load_image("images/mainmenu/cursor.png");
	options 	= load_image("images/mainmenu/options.png");
	title	 	= load_image("images/mainmenu/title.png");

	cursorY = 550;

	printf("MainMenuState init\n");
}

void MainMenuState::cleanup()
{
	SDL_FreeSurface(bg);
	SDL_FreeSurface(cursor);
	SDL_FreeSurface(options);
	SDL_FreeSurface(title);

	printf("MainMenuState cleanup\n");
}

void MainMenuState::pause()
{
	printf("MainMenuState pause\n");
}

void MainMenuState::resume()
{
	printf("MainMenuState resume\n");
}

void MainMenuState::handleEvents(GameEngine* game)
{
	SDL_Event event;

	if ( SDL_PollEvent(&event) )
	{
		switch (event.type)
		{
			case SDL_QUIT:
				game->quit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_DOWN:
						if( cursorY != 650 )
							cursorY += 50;
						else
							cursorY = 550;
						break;

					case SDLK_UP:
						if( cursorY != 550 )
							cursorY -= 50;
						else
							cursorY = 650;
						break;

					case SDLK_RETURN:
						if( cursorY == 550 )
							game->changeState( WorldMapState::instance() );
						else if( cursorY == 600 )
							game->quit();
						else if( cursorY == 650 )
							printf("Picked the third option, eh?\n");
						break;
				}
				break;
		}
	}
}

void MainMenuState::update(GameEngine* game)
{
}

void MainMenuState::draw(GameEngine* game)
{
	//For debug purposes
//	SDL_FillRect(game->screen, NULL, 0x521122);

//	apply_surface(0, 0, bg, game->screen, NULL);
	SDL_BlitSurface(bg, NULL, game->screen, NULL);
	apply_surface(312, 100, title, game->screen, NULL);
	apply_surface(362, cursorY, cursor, game->screen, NULL);
	apply_surface(412, 560, options, game->screen, NULL);

	//For debug purposes
//	SDL_FillRect(game->screen, NULL, 0x521122);

	//SDL_UpdateRect(game->screen, 0, 0, 0, 0);
	SDL_Flip(game->screen);
}

