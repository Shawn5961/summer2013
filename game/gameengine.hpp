#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <SDL/SDL.h>
#include <vector>
using namespace std;

class GameState;

class GameEngine
{
	public:
		void init(const char* title, int width=1024, int height=768, int bpp=0, bool fullscreen=false);
		void cleanup();

		void changeState(GameState* state);
		void pushState(GameState* state);
		void popState();

		void handleEvents();
		void update();
		void draw();

		bool running();
		void quit();

		SDL_Surface* screen;

	private:
		vector<GameState*> states;

		bool game_running;
		bool game_fullscreen;
};

#endif
