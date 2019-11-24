#pragma once

#include "Engine.h"

#include <vector>

enum LogMessageLevel
{
	OK,
	ERROR
};

// UiController, handels ever Ui action that is not part of the GameBoard
// This is the section right of the gameboard
class UiController
{
	public:
		UiController(SDL_Renderer *renderer);
		~UiController() = default;

		void draw() const;

		// indicate turn switch
		void switchTurn();

		bool init();

		typedef struct	DisplayMessage
		{
			std::string		text;
			LogMessageLevel level;
		}				DisplayMessage;

		// Adds a message to the log
		void addDisplayMessage(DisplayMessage msg);

	private:

		SDL_Renderer	*_renderer;
		bool			_isWhiteTurn;
		TTF_Font		*_font30;
		TTF_Font		*_font20;

		// A list of log messages
		// TODO: turn this into array, because messages are caped at 4 anyways
		std::vector<DisplayMessage>	_logMessages;
};
