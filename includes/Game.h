#pragma once

#include "Engine.h"
#include "GameBoard.h"
#include "UiController.h"

// The game class controls the flow of the chess game
class Game
{
	public:
		Game();
		~Game();

		bool start();

		bool isCheck();


	private:
		bool init();

		bool _isInit;

		SDL_Renderer	*_renderer;
		SDL_Window		*_window;

		char _whitesTurn = 1;

		bool isWhitesTurn() const;

		GameBoard		*_board;
		UiController	*_uic;
};
