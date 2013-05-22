#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <SDL/SDL.h>
#include "gamestate.hpp"

class MainMenuState : public GameState
{
	public:
		void init();
		void cleanup();

		void pause();
		void resume();
		
		void handleEvents(GameEngine* game);
		void update(GameEngine* game);
		void draw(GameEngine* game);

		static MainMenuState* instance()
		{
			return &game_MainMenuState;
		}

		int cursorY;

	protected:
		MainMenuState() { }

	private:
		static MainMenuState game_MainMenuState;

		SDL_Surface* bg;
		SDL_Surface* title;
		SDL_Surface* options;
		SDL_Surface* cursor;
};

#endif
