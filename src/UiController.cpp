#include "UiController.h"

UiController::UiController(SDL_Renderer *renderer) :
	_renderer(renderer), _isWhiteTurn(true)//, _logMessage(std::string("hallo"))
{
}

bool UiController::init()
{
	_font30 = TTF_OpenFont("fonts/PTS75F.ttf", 30);
	if (!_font30)
	{
		std::cout << TTF_GetError() << std::endl;
		return false;
	}
	_font20 = TTF_OpenFont("fonts/PTS75F.ttf", 20);
	if (!_font20)
	{
		std::cout << TTF_GetError() << std::endl;
		return false;
	}

	return true;
}

void UiController::draw() const
{
	SDL_Color color = {0, 0, 0, 255};
	SDL_Rect textRect = {BOARD_WIDTH + 50, 0, 0, 0};

	SDL_Surface* textSurface = TTF_RenderText_Blended(_font30, _isWhiteTurn ? "White" : "Black", color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);
	SDL_FreeSurface(textSurface);
	SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
	SDL_RenderCopy(_renderer, textTexture, nullptr, &textRect);

	textRect.y = 500;
	for (auto msg : _logMessages)
	{
		if (msg.level == LogMessageLevel::OK)
			color = {0, 255, 0, 255};
		else
			color = {255, 0, 0, 255};
		SDL_Surface *logMsgSurface;
		if (textRect.y == 500)
			logMsgSurface = TTF_RenderText_Blended(_font30, msg.text.c_str(), color);
		else
			logMsgSurface = TTF_RenderText_Blended(_font20, msg.text.c_str(), color);
		SDL_Texture* logTexture = SDL_CreateTextureFromSurface(_renderer, logMsgSurface);
		SDL_FreeSurface(logMsgSurface);
		textRect.y += 50;
		SDL_QueryTexture(logTexture, nullptr, nullptr, &textRect.w, &textRect.h);
		SDL_RenderCopy(_renderer, logTexture, nullptr, &textRect);
	}

	SDL_SetRenderDrawColor(_renderer, 200, 200, 200, 255);
}

void UiController::switchTurn()
{
	_isWhiteTurn = !_isWhiteTurn;
}

void UiController::addDisplayMessage(DisplayMessage msg)
{
	if (_logMessages.size() > 3)
	{
		_logMessages.pop_back();
	}
	_logMessages.insert(_logMessages.begin(), msg);
}
