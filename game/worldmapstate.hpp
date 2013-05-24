#ifndef WORLDMAPSTATE_HPP
#define WORLDMAPSTATE_HPP

#include <SDL/SDL.h>
#include "gamestate.hpp"

class WorldMapState : public GameState
{

	public:
		void init();
		void cleanup();

		void pause();
		void resume();
		
		void handleEvents(GameEngine* game);
		void update(GameEngine* game);
		void draw(GameEngine* game);

		static WorldMapState* instance()
		{
			return &game_WorldMapState;
		}

		int playerX, playerY;
		int playerDirection, playerFrame;
		int tilesize;

	protected:
		WorldMapState() { }

	private:
		static WorldMapState game_WorldMapState;


		int mapGrid[32][24];
		bool checkPass(int x, int y);
		bool passable;
		SDL_Rect mapTile[5];

		SDL_Rect playerSpriteUp[3];
		SDL_Rect playerSpriteDown[3];
		SDL_Rect playerSpriteLeft[3];
		SDL_Rect playerSpriteRight[3];

		SDL_Surface* map;
		SDL_Surface* player;
};


#endif
