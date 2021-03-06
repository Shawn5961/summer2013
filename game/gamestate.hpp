#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "gameengine.hpp"

class GameState
{
	public:
		virtual void init() = 0;
		virtual void cleanup() = 0;

		virtual void pause() = 0;
		virtual void resume() = 0;

		virtual void handleEvents(GameEngine* game) = 0;
		virtual void update(GameEngine* game) = 0;
		virtual void draw(GameEngine* game) = 0;

		void changeState(GameEngine* game, GameState* state)
		{
			game->changeState(state);
		}

	protected:
		GameState() { }
};

#endif
