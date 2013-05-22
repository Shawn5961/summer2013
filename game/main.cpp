#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <string>
#include <iostream>
#include <sstream>
#include "timer.hpp"
#include "timer.cpp"

const int SCREEN_WIDTH		= 1280;
const int SCREEN_HEIGHT		= 720;
const int SCREEN_BPP		= 32;
const int FRAMES_PER_SECOND = 60;

SDL_Surface *screen			= NULL;
SDL_Surface *background		= NULL;
SDL_Surface *player			= NULL;

SDL_Event event;


SDL_Rect playerSprite[12];

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
			Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0x00, 0x00, 0x00);
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

bool init()
{
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		return false;
	}

	//Set up the screen
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	// If there was an error setting up the screen
	if(screen == NULL)
	{
		return false;
	}

	//Sets the window caption
	SDL_WM_SetCaption("Game", NULL);

	return true;
}

bool load_files()
{
	background 	= load_image("images/background.png");
	player     	= load_image("images/sprite1.png");

	if(background == NULL)
	{
		return (false);
	}

	if(player == NULL)
	{
		return (false);
	}

	
	return (true);
}

void clean_up()
{
	SDL_FreeSurface(screen);
	SDL_FreeSurface(background);
	SDL_FreeSurface(player);

	SDL_Quit();
}

int main(int argc, char** argv)
{
	bool quit = false;
	
	int frame = 0;
	bool cap = true;
	Timer fps;
	Timer update;
	
	int x = 96, y = 96;
	int f = 0;
		
	if(init() == false)
	{
		return 1;
	}
	
	if(load_files() == false)
	{
		return 1;
	}

	playerSprite[0].x = 0;
	playerSprite[0].y = 0;
	playerSprite[0].w = 32;
	playerSprite[0].h = 48;

	playerSprite[1].x = 32;
	playerSprite[1].y = 0;
	playerSprite[1].w = 32;
	playerSprite[1].h = 48;

	playerSprite[2].x = 64;
	playerSprite[2].y = 0;
	playerSprite[2].w = 32;
	playerSprite[2].h = 48;

	playerSprite[3].x = 0;
	playerSprite[3].y = 48;
	playerSprite[3].w = 32;
	playerSprite[3].h = 48;

	playerSprite[4].x = 32;
	playerSprite[4].y = 48;
	playerSprite[4].w = 32;
	playerSprite[4].h = 48;

	playerSprite[5].x = 64;
	playerSprite[5].y = 48;
	playerSprite[5].w = 32;
	playerSprite[5].h = 48;

	playerSprite[6].x = 0;
	playerSprite[6].y = 96;
	playerSprite[6].w = 32;
	playerSprite[6].h = 48;

	playerSprite[7].x = 32;
	playerSprite[7].y = 96;
	playerSprite[7].w = 32;
	playerSprite[7].h = 48;

	playerSprite[8].x = 64;
	playerSprite[8].y = 96;
	playerSprite[8].w = 32;
	playerSprite[8].h = 48;

	playerSprite[9].x = 0;
	playerSprite[9].y = 144;
	playerSprite[9].w = 32;
	playerSprite[9].h = 48;

	playerSprite[10].x = 32;
	playerSprite[10].y = 144;
	playerSprite[10].w = 32;
	playerSprite[10].h = 48;

	playerSprite[11].x = 64;
	playerSprite[11].y = 144;
	playerSprite[11].w = 32;
	playerSprite[11].h = 48;
	
	update.start();

	while(quit == false)
	{
		fps.start();
		if(SDL_PollEvent(&event))
		{
			if(event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_UP:
						y = y - 48;
						if(f == 0 || f == 1)
						{
							f++;
						}
						else
						{
							f = 0;
						}
						printf("debug");
						break;

					case SDLK_DOWN:
						y = y + 48;
						if(f == 3 || f == 4)
							f++;
						else
							f = 3;
						break;

					case SDLK_LEFT:
						x = x - 32;
						if(f == 6 || f == 7)
							f++;
						else
							f = 6;
						break;

					case SDLK_RIGHT:
						x = x + 32;
						if(f == 9 || f == 10)
							f++;
						else
							f = 9;
						break;
						
					case SDLK_RETURN:
						cap = (!cap);
						update.start();

					default:
						break;
				}
			}
			else if(event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		apply_surface(0, 0, background, screen);
		


		if(y < 0)
			y = 0;

		if(y >= SCREEN_HEIGHT)
			y = SCREEN_HEIGHT - 48;

		if(x < 0)
			x = 0;

		if(x >= SCREEN_WIDTH)
			x = SCREEN_WIDTH - 32;

		apply_surface(x, y, player, screen, &playerSprite[f]);
		
		if(SDL_Flip(screen) == -1)
		{
			return 1;
		}

		frame++;
		
		if((cap == true) && (fps.get_ticks() < 1000 / FRAMES_PER_SECOND))
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
		}
		
		std::stringstream fpsstream;
		
		fpsstream << "FPS: " << frame  / (update.get_ticks() / 1000.f);
		SDL_WM_SetCaption(fpsstream.str().c_str(), NULL);
	}

	clean_up();

	return 0;
}