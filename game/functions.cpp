#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include "functions.hpp"

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

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;

	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface(source, clip, destination, &offset);
}
