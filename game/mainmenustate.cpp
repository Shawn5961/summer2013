#include <stdio.h>
#include <string>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "gameengine.hpp"
#include "gamestate.hpp"
#include "mainmenustate.hpp"

SDL_Surface *load_image(std::string filename)
{
	//This is temporary storage for the image that's loaded
	SDL_Surface* loadedImage    = NULL;

	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;

	//Load the image
	loadedImage = IMG_Load(filename.c_str());

	//If nothing went wrong in loading the image, then--
	if(loadedImage != NULL)
	{
		//Create an optimized image!
		optimizedImage = SDL_DisplayFormat(loadedImage);

		//Free the old image
		SDL_FreeSurface(loadedImage);
		//if the image was optimized
		if(optimizedImage != NULL)
		{
			Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0xFF, 0xFF, 0xFF);
			//set all pixles of colors that we put in to be transperent
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
		}

	}
	//Return the optimized image!
	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)
{
	//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;

	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface(source, clip, destination, &offset);
}

MainMenuState MainMenuState::game_MainMenuState;

void MainMenuState::init()
{
	SDL_Surface* bg 		= NULL;
	SDL_Surface* cursor		= NULL;
	SDL_Surface* options 	= NULL;
	SDL_Surface* title	 	= NULL;

	bg 			= load_image("images/mainmenu/bg.png");
	cursor		= load_image("images/mainmenu/cursor.png");
	options 	= load_image("images/mainmenu/options.png");
	title	 	= load_image("images/mainmenu/title.png");

	cursorY = 600;

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
						if( cursorY != 700 )
							cursorY += 50;
						else
							cursorY = 600;
						break;

					case SDLK_UP:
						if( cursorY != 600 )
							cursorY -= 50;
						else
							cursorY = 700;
						break;

					case SDLK_RETURN:
						if( cursorY == 600 )
							//game->changeState( PlayState::instance() );
							printf("Should play the game\n");
						else if( cursorY == 650 )
							game->quit();
						else if( cursorY == 700 )
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

	apply_surface(0, 0, bg, game->screen, NULL);
	apply_surface(312, 100, title, game->screen, NULL);
	apply_surface(412, 600, options, game->screen, NULL);
	apply_surface(362, cursorY, cursor, game->screen, NULL);

	//For debug purposes
//	SDL_FillRect(game->screen, NULL, 0x521122);

	//SDL_UpdateRect(game->screen, 0, 0, 0, 0);
	SDL_Flip(game->screen);
}

