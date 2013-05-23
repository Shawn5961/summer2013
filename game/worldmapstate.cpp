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

WorldMapState WorldMapState::game_WorldMapState;

void WorldMapState::init()
{
	map			= load_image("images/worldmap/tilesheet.png");
	player		= load_image("images/worldmap/playersheet.png");

	tilesize = 32;

	playerX = tilesize * 14;
	playerY = tilesize * 14;
	playerDirection = 1;
	playerFrame = 0;
	//Set up map tiles
	//Grass
	mapTile[0].x = 0;
	mapTile[0].y = 0;
	mapTile[0].w = tilesize;
	mapTile[0].h = tilesize;

	//Forest
	mapTile[1].x = tilesize;
	mapTile[1].y = 0;
	mapTile[1].w = tilesize;
	mapTile[1].h = tilesize;

	//Mountain
	mapTile[2].x = tilesize * 2;
	mapTile[2].y = 0;
	mapTile[2].w = tilesize;
	mapTile[2].h = tilesize;

	//Water
	mapTile[3].x = tilesize * 3;
	mapTile[3].y = 0;
	mapTile[3].w = tilesize;
	mapTile[3].h = tilesize;

	//Town
	mapTile[4].x = tilesize * 4;
	mapTile[4].y = 0;
	mapTile[4].w = tilesize;
	mapTile[4].h = tilesize;

	//Set up player animations
	//UP animation 1
	playerSpriteUp[0].x = 0;
	playerSpriteUp[0].y = 0;
	playerSpriteUp[0].w = tilesize;
	playerSpriteUp[0].h = tilesize;
	//UP animation 2
	playerSpriteUp[1].x = tilesize;
	playerSpriteUp[1].y = 0;
	playerSpriteUp[1].w = tilesize;
	playerSpriteUp[1].h = tilesize;
	//UP animation 3
	playerSpriteUp[2].x = tilesize * 2;
	playerSpriteUp[2].y = 0;
	playerSpriteUp[2].w = tilesize;
	playerSpriteUp[2].h = tilesize;

	//DOWN animation 1
	playerSpriteDown[0].x = 0;
	playerSpriteDown[0].y = tilesize;
	playerSpriteDown[0].w = tilesize;
	playerSpriteDown[0].h = tilesize;
	//DOWN animation 2
	playerSpriteDown[1].x = tilesize;
	playerSpriteDown[1].y = tilesize;
	playerSpriteDown[1].w = tilesize;
	playerSpriteDown[1].h = tilesize;
	//DOWN animation 3
	playerSpriteDown[2].x = tilesize * 2;
	playerSpriteDown[2].y = tilesize;
	playerSpriteDown[2].w = tilesize;
	playerSpriteDown[2].h = tilesize;

	//LEFT animation 1
	playerSpriteLeft[0].x = 0;
	playerSpriteLeft[0].y = tilesize * 2;
	playerSpriteLeft[0].w = tilesize;
	playerSpriteLeft[0].h = tilesize;
	//LEFT animation 2
	playerSpriteLeft[1].x = tilesize;
	playerSpriteLeft[1].y = tilesize * 2;
	playerSpriteLeft[1].w = tilesize;
	playerSpriteLeft[1].h = tilesize;
	//LEFT animation 3
	playerSpriteLeft[2].x = tilesize * 2;
	playerSpriteLeft[2].y = tilesize * 2;
	playerSpriteLeft[2].w = tilesize;
	playerSpriteLeft[2].h = tilesize;

	//RIGHT animation 1
	playerSpriteRight[0].x = 0;
	playerSpriteRight[0].y = tilesize * 3;
	playerSpriteRight[0].w = tilesize;
	playerSpriteRight[0].h = tilesize;
	//RIGHT animation 2
	playerSpriteRight[1].x = tilesize;
	playerSpriteRight[1].y = tilesize * 3;
	playerSpriteRight[1].w = tilesize;
	playerSpriteRight[1].h = tilesize;
	//RIGHT animation 3
	playerSpriteRight[2].x = tilesize * 2;
	playerSpriteRight[2].y = tilesize * 3;
	playerSpriteRight[2].w = tilesize;
	playerSpriteRight[2].h = tilesize;

	for( int yCoord = 0; yCoord < 24; yCoord++ )
	{
		for( int xCoord = 0; xCoord < 32; xCoord++ )
		{
			//Mountains
			if( (xCoord <= 7 && yCoord <= 17) || (xCoord <= 5 && yCoord <= 19) || (xCoord <= 2 && yCoord <= 22) )
			{	
				mapGrid[xCoord][yCoord] = 2;
			}
			//Water
			else if( (xCoord >= 17 && yCoord >= 17) || (xCoord >= 19 && yCoord >= 15) || (xCoord >= 23 && yCoord >= 13) || (xCoord >= 25 && yCoord >= 12) || (xCoord >= 28) )
			{
				mapGrid[xCoord][yCoord] = 3;
			}
			//Forest
			else if( (xCoord <= 10 && yCoord <= 17) || (xCoord <= 6 && yCoord <= 24) || (xCoord <= 8 && yCoord <= 22) )
			{
				mapGrid[xCoord][yCoord] = 1;
			}
			//Town
			else if( (xCoord == 14 && yCoord == 14) )
			{
				mapGrid[xCoord][yCoord] = 4;
			}
			//Grass
			else
			{
				mapGrid[xCoord][yCoord] = 0;
			}
		}
	}



	printf("WorldMapState init\n");
}

bool WorldMapState::checkPass(int x, int y)
{
	if( mapGrid[x][y] == 2 || mapGrid[x][y] == 3 )
		passable = false;
	else
		passable = true;

	return passable;
}

void WorldMapState::cleanup()
{
	SDL_FreeSurface(map);
	SDL_FreeSurface(player);

	printf("WorldMapState cleanup\n");
}

void WorldMapState::pause()
{
	printf("WorldMapState pause\n");
}

void WorldMapState::resume()
{
	printf("WorldMapState resume\n");
}

void WorldMapState::handleEvents(GameEngine* game)
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
					case SDLK_UP:
						if( (mapGrid[playerX / 32][(playerY - 32) / 32] == 0) || (mapGrid[playerX / 32][(playerY - 32) / 32] == 1) || (mapGrid[playerX / 32][(playerY - 32) / 32] == 4) )
							playerY -= 32;
						playerDirection = 0;
						if( (playerFrame == 0) || (playerFrame == 1) )
							playerFrame++;
						else
							playerFrame = 0;
						break;

					case SDLK_DOWN:
						if( (mapGrid[playerX / 32][(playerY + 32) / 32] == 0) || (mapGrid[playerX / 32][(playerY + 32) / 32] == 1) || (mapGrid[playerX / 32][(playerY + 32) / 32] == 4) )
							playerY += 32;
						playerDirection = 1;
						if( (playerFrame == 0) || (playerFrame == 1) )
							playerFrame++;
						else
							playerFrame = 0;
						break;

					case SDLK_LEFT:
						if( (mapGrid[(playerX - 32) / 32][playerY / 32] == 0) || (mapGrid[(playerX - 32) / 32][playerY / 32] == 1) || (mapGrid[(playerX - 32) / 32][playerY / 32] == 4) )
							playerX -= 32;
						playerDirection = 2;
						if( (playerFrame == 0) || (playerFrame == 1) )
							playerFrame++;
						else
							playerFrame = 0;
						break;

					case SDLK_RIGHT:
						if( (mapGrid[(playerX + 32) / 32][playerY / 32] == 0) || (mapGrid[(playerX + 32) / 32][playerY / 32] == 1) || (mapGrid[(playerX + 32) / 32][playerY / 32] == 4) )
							playerX += 32;
						playerDirection = 3;
						if( (playerFrame == 0) || (playerFrame == 1) )
							playerFrame++;
						else
							playerFrame = 0;
						break;
				}
				break;
		}
	}
}

void WorldMapState::update(GameEngine* game)
{
}

void WorldMapState::draw(GameEngine* game)
{
	for( int yCoord = 0; yCoord < 24; yCoord++ )
	{
		for( int xCoord = 0; xCoord < 32; xCoord++ )
		{
			if( mapGrid[xCoord][yCoord] == 0 )
				apply_surface(xCoord * 32, yCoord * 32, map, game->screen, &mapTile[0]);
			else if( mapGrid[xCoord][yCoord] == 1 )
				apply_surface(xCoord * 32, yCoord * 32, map, game->screen, &mapTile[1]);
			else if( mapGrid[xCoord][yCoord] == 2 )
				apply_surface(xCoord * 32, yCoord * 32, map, game->screen, &mapTile[2]);
			else if( mapGrid[xCoord][yCoord] == 3 )
				apply_surface(xCoord * 32, yCoord * 32, map, game->screen, &mapTile[3]);
			else if( mapGrid[xCoord][yCoord] == 4 )
				apply_surface(xCoord * 32, yCoord * 32, map, game->screen, &mapTile[4]);
		}
	}
	if( playerDirection == 0 )
		apply_surface(playerX, playerY, player, game->screen, &playerSpriteUp[playerFrame]);
	else if( playerDirection == 1 )
		apply_surface(playerX, playerY, player, game->screen, &playerSpriteDown[playerFrame]);
	else if( playerDirection == 2 )
		apply_surface(playerX, playerY, player, game->screen, &playerSpriteLeft[playerFrame]);
	else if( playerDirection == 3 )
		apply_surface(playerX, playerY, player, game->screen, &playerSpriteRight[playerFrame]);

	SDL_Flip(game->screen);
}

