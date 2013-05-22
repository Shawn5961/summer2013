#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <string>
#include <iostream>
#include <sstream>
#include "timer.hpp"
#include "timer.cpp"

//Screen attributes
const int SCREEN_WIDTH		= 1024;
const int SCREEN_HEIGHT		= 768;
const int SCREEN_BPP		= 32;

//FPS
const int FRAMES_PER_SECOND = 60;

//Tile dimensions
const int TILE_WIDTH		= 32;
const int TILE_HEIGHT		= 32;

const int PLAYER_UP			= 0;
const int PLAYER_DOWN		= 1;
const int PLAYER_LEFT		= 2;
const int PLAYER_RIGHT		= 3;

SDL_Surface *screen			= NULL;
SDL_Surface *background		= NULL;
SDL_Surface *player			= NULL;

SDL_Event event;


SDL_Rect playerSpriteUp[3];
SDL_Rect playerSpriteDown[3];
SDL_Rect playerSpriteLeft[3];
SDL_Rect playerSpriteRight[3];

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
			Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0xFF, 0x00, 0xDE);
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

void set_clips()
{
	//UP animation 1
	playerSpriteUp[0].x = 0;
	playerSpriteUp[0].y = 0;
	playerSpriteUp[0].w = TILE_WIDTH;
	playerSpriteUp[0].h = TILE_HEIGHT;
	//UP animation 2
	playerSpriteUp[1].x = TILE_WIDTH;
	playerSpriteUp[1].y = 0;
	playerSpriteUp[1].w = TILE_WIDTH;
	playerSpriteUp[1].h = TILE_HEIGHT;
	//UP animation 3
	playerSpriteUp[2].x = TILE_WIDTH * 2;
	playerSpriteUp[2].y = 0;
	playerSpriteUp[2].w = TILE_WIDTH;
	playerSpriteUp[2].h = TILE_HEIGHT;

	//DOWN animation 1
	playerSpriteDown[0].x = 0;
	playerSpriteDown[0].y = TILE_HEIGHT;
	playerSpriteDown[0].w = TILE_WIDTH;
	playerSpriteDown[0].h = TILE_HEIGHT;
	//DOWN animation 2
	playerSpriteDown[1].x = TILE_WIDTH;
	playerSpriteDown[1].y = TILE_HEIGHT;
	playerSpriteDown[1].w = TILE_WIDTH;
	playerSpriteDown[1].h = TILE_HEIGHT;
	//DOWN animation 3
	playerSpriteDown[2].x = TILE_WIDTH * 2;
	playerSpriteDown[2].y = TILE_HEIGHT;
	playerSpriteDown[2].w = TILE_WIDTH;
	playerSpriteDown[2].h = TILE_HEIGHT;

	//LEFT animation 1
	playerSpriteLeft[0].x = 0;
	playerSpriteLeft[0].y = TILE_HEIGHT * 2;
	playerSpriteLeft[0].w = TILE_WIDTH;
	playerSpriteLeft[0].h = TILE_HEIGHT;
	//LEFT animation 2
	playerSpriteLeft[1].x = TILE_WIDTH;
	playerSpriteLeft[1].y = TILE_HEIGHT * 2;
	playerSpriteLeft[1].w = TILE_WIDTH;
	playerSpriteLeft[1].h = TILE_HEIGHT;
	//LEFT animation 3
	playerSpriteLeft[2].x = TILE_WIDTH * 2;
	playerSpriteLeft[2].y = TILE_HEIGHT * 2;
	playerSpriteLeft[2].w = TILE_WIDTH;
	playerSpriteLeft[2].h = TILE_HEIGHT;

	//RIGHT animation 1
	playerSpriteRight[0].x = 0;
	playerSpriteRight[0].y = TILE_HEIGHT * 3;
	playerSpriteRight[0].w = TILE_WIDTH;
	playerSpriteRight[0].h = TILE_HEIGHT;
	//RIGHT animation 2
	playerSpriteRight[1].x = TILE_WIDTH;
	playerSpriteRight[1].y = TILE_HEIGHT * 3;
	playerSpriteRight[1].w = TILE_WIDTH;
	playerSpriteRight[1].h = TILE_HEIGHT;
	//RIGHT animation 3
	playerSpriteRight[2].x = TILE_WIDTH * 2;
	playerSpriteRight[2].y = TILE_HEIGHT * 3;
	playerSpriteRight[2].w = TILE_WIDTH;
	playerSpriteRight[2].h = TILE_HEIGHT;
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
	player     	= load_image("images/testsprite2.png");

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

class Player
{
	private:
		//X and Y coordinates of the player
		int x, y;

		//Velocity of the player
		int xVel, yVel;

		//Direction the player is facing
		int direction;

		//Animation frame
		int frame;

	public:
		//Initialize the player
		Player();

		//Handle keypresses passed to the player
		void handle_input();

		//Move the player
		void move();

		//Show the player
		void show();
};

Player::Player()
{
	//Initialize the player's coordinates
	x = 0;
	y = 0;

	//Initialize the player's velocity
	xVel = 0;
	yVel = 0;
}

void Player::handle_input()
{
	//Check if a key was pressed
	if(event.type == SDL_KEYDOWN)
	{
		//Adjust the velocity
		switch(event.key.keysym.sym)
		{
			case SDLK_UP:
				yVel -= TILE_HEIGHT /8;
				break;

			case SDLK_DOWN:
				yVel += TILE_HEIGHT /8;
				break;

			case SDLK_LEFT:
				xVel -= TILE_WIDTH /8;
				break;

			case SDLK_RIGHT:
				xVel += TILE_WIDTH /8;
				break;
		}
	}
	//Check if a key was released
	else if(event.type == SDL_KEYUP)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_UP:
				yVel += TILE_HEIGHT /8;
				break;

			case SDLK_DOWN:
				yVel -= TILE_HEIGHT /8;
				break;

			case SDLK_LEFT:
				xVel += TILE_WIDTH /8;
				break;

			case SDLK_RIGHT:
				xVel -= TILE_WIDTH /8;
				break;
		}
	}
}

void Player::move()
{
	//Move the player left or right
	x += xVel;

	//If the player moves offscreen horizontally, move them back
	if((x < 0) || (x + TILE_WIDTH > SCREEN_WIDTH))
	{
		x -= xVel;
	}

	//Move the player up or down
	y += yVel;

	//If the player moves offscreen horizontally, move them back
	if((y < 0) || (y + TILE_HEIGHT > SCREEN_HEIGHT))
	{
		y -= yVel;
	}
}

void Player::show()
{
	//Check if the player is moving right
	if(xVel > 0)
	{
		direction = PLAYER_RIGHT;

		frame++;
	}
	//Check if the player is moving left
	else if(xVel < 0)
	{
		direction = PLAYER_LEFT;

		frame++;
	}
	//Check if the player is moving up
	else if(yVel > 0)
	{
		direction = PLAYER_DOWN;

		frame++;
	}
	//Check if the player is moving down
	else if(yVel < 0)
	{
		direction = PLAYER_UP;

		frame++;
	}
	//If standing still, restart the animation
	else
	{
		frame = 0;
	}

	//Loop the animation
	if(frame >= 60)
	{
		frame = 0;
	}

	//Show the player
	switch(direction)
	{
		//Up
		case 0:
			apply_surface(x, y, player, screen, &playerSpriteUp[frame/20]);
			break;

		//Down
		case 1:
			apply_surface(x, y, player, screen, &playerSpriteDown[frame/20]);
			break;

		//Left
		case 2:
			apply_surface(x, y, player, screen, &playerSpriteLeft[frame/20]);
			break;
		
		//Right
		case 3:
			apply_surface(x, y, player, screen, &playerSpriteRight[frame/20]);
			break;
	}
}
int main(int argc, char** argv)
{
	bool quit = false;
	bool cap = true;
	int framerate = 0;

	Timer fps;
	Timer update;
	
		
	if(init() == false)
	{
		return 1;
	}
	
	if(load_files() == false)
	{
		return 1;
	}

	set_clips();
	
	Player player;

	update.start();

	while(quit == false)
	{
		fps.start();
		while(SDL_PollEvent(&event))
		{
			player.handle_input();

			if(event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		player.move();

		apply_surface(0, 0, background, screen);

		player.show();

		if(SDL_Flip(screen) == -1)
		{
			return 1;
		}

		framerate++;

		if((cap == true) && (fps.get_ticks() < 1000 / FRAMES_PER_SECOND))
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
		}
		
		std::stringstream fpsstream;
		
		fpsstream << "FPS: " << framerate  / (update.get_ticks() / 1000.f);
		SDL_WM_SetCaption(fpsstream.str().c_str(), NULL);
	}

	clean_up();

	return 0;
}
