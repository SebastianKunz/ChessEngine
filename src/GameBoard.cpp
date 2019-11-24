#include "Engine.h"
#include "GameBoard.h"
#include "Figures.h"

GameBoard::GameBoard(SDL_Renderer *renderer) : _renderer(renderer), _highlightedTile({-1, -1})
{
	_loader = new FigureLoader(renderer, 56, 60);

	_font20 = TTF_OpenFont("fonts/PTS75F.ttf", 40);
	if (!_font20)
		std::cout << "FAILED TO LOAD FONT" << std::endl;

	_loader->loadImage("./res/figures.png");
	_board = nullptr;
	_board = new AFigure**[8];
	char color = 1;

	// make this from a static array or so, seems cleaner
	for (int y = 0; y < 8; y++)
	{
		_board[y] = new AFigure*[8];
		for (int x = 0; x < 8; x++)
		{
			_board[y][x] = nullptr;
			if (y == 0 || y == 1)
				color = -1;
			else
				color = 1;

			if (y == 1 || y == 6)
				_board[y][x] = new Pawn(y, x, color, _loader);
			else if ((y == 0 || y == 7) && (x == 2 || x == 5))
				_board[y][x] = new Bishop(y, x, color, _loader);
			else if ((y == 0 || y == 7) && x == 4)
				_board[y][x] = new King(y, x, color, _loader);
			else if ((y == 0 || y == 7) && x == 3)
				_board[y][x] = new Queen(y, x, color, _loader);
			else if ((y == 0 || y == 7) && (x == 1 || x == 6))
				_board[y][x] = new Knight(y, x, color, _loader);
			else if ((x == 0 || x == 7) && (y == 0 || y == 7))
				_board[y][x] = new Rook(y, x, color, _loader);
		}
	}
}

GameBoard::~GameBoard()
{
	for (int y = 0; y < BOARD_ROWS; y++)
	{
		for (int x = 0; x < BOARD_COLS; x++)
		{
			if (_board[y][x])
				delete _board[y][x];
		}
		delete []_board[y];
	}
	delete []_board;
	delete _loader;
}

// TODO: optimize this so you dont loop over the gameboard multiple times
void GameBoard::draw()
{
	SDL_SetRenderDrawColor(_renderer, 50, 50, 50, 255 );

	SDL_Rect textRect = {10, 0, 50, 50};
	//draw board numbers
	for (int y = 0; y < BOARD_HEIGHT; y += 100)
	{
		SDL_Surface *logMsgSurface;
		char str[2];
		str[0] = (y + 100) / 100 + '0';
		str[1] = '\0';
		logMsgSurface = TTF_RenderText_Blended(_font20, str, {255, 255, 255, 255});
		SDL_Texture* logTexture = SDL_CreateTextureFromSurface(_renderer, logMsgSurface);
		SDL_FreeSurface(logMsgSurface);
		SDL_QueryTexture(logTexture, nullptr, nullptr, &textRect.w, &textRect.h);
		textRect.y = y + 50 - textRect.h / 2;
		SDL_RenderCopy(_renderer, logTexture, nullptr, &textRect);
	}
	//draw board letters
	textRect = {0, 800, 50, 50};
	for (int x = 0; x < BOARD_WIDTH; x += 100)
	{
		SDL_Surface *logMsgSurface;
		char str[2];
		str[0] = x / 100 + 'A';
		str[1] = '\0';
		logMsgSurface = TTF_RenderText_Blended(_font20, str, {255, 255, 255, 255});
		SDL_Texture* logTexture = SDL_CreateTextureFromSurface(_renderer, logMsgSurface);
		SDL_FreeSurface(logMsgSurface);
		SDL_QueryTexture(logTexture, nullptr, nullptr, &textRect.w, &textRect.h);
		textRect.x = x + 100 - textRect.w / 2;
		SDL_RenderCopy(_renderer, logTexture, nullptr, &textRect);
	}

	// draw the board itself (black and white tiles)
	for (int y = 0; y < BOARD_WIDTH; y += TILE_SIZE_X)
	{
		bool offY = y % 200 == 0;
		for (int x = 50; x < 850; x += 100)
		{
			bool off = (x - 50) % 200 == 0;
			if (offY)
				off = !off;
			SDL_Rect r = {x, y, 100, 100};

			if (off)
				SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255 );
			else
				SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255 );
			// Render rect
			SDL_RenderFillRect(_renderer, &r);
		}
	}

	// draw the highlighted tile
	SDL_Rect r = {0, 0, 100, 100};
	r.x = (_highlightedTile.x * 100) + 50;
	r.y = _highlightedTile.y * 100;
	if (_highlightedTile.x != -1 || _highlightedTile.y != -1)
	{
		SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 100);
		SDL_RenderFillRect(_renderer, &r);
	}

	// getsAllPossibleMoves of highlighted figure
	std::vector<SDL_Point> moves;
	if (isInBounds(_highlightedTile.y, _highlightedTile.x) &&
		 _board[_highlightedTile.y][_highlightedTile.x])
			moves = _board[_highlightedTile.y][_highlightedTile.x]->getAllPossibleMoves(_board);

	// draw the possible moves
	for (auto const& move : moves) {
		r.x = move.x * 100 + 50;
		r.y = move.y * 100;
		SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 100);
		SDL_RenderFillRect(_renderer, &r);
	}

	// draw the figures
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (_board[y][x])
				_board[y][x]->draw();
		}
	}
}

MoveAction GameBoard::moveFigureTo(const int fromY, const int fromX,
	const int toY, const int toX)
{
	unHighlightTile();

	if (!_board[fromY][fromX] || !isInBounds(fromY, fromX) || !isInBounds(toY, toX))
		return MoveAction::FAIL;

	bool isCapture = _board[toY][toX];

	if (_board[fromY][fromX]->moveTo(toY, toX, _board))
	{
		_board[fromY][fromX] = nullptr;
		if (isCapture)
			return MoveAction::CAPTURE;
		return MoveAction::MOVE;
	}

	return MoveAction::FAIL;
}

bool GameBoard::setHighlightedTile(const int y, const int x)
{
	if (!isInBounds(y, x))
		return false;

	_highlightedTile.x = x;
	_highlightedTile.y = y;
	return true;
}

void GameBoard::unHighlightTile()
{
	_highlightedTile.x = -1;
	_highlightedTile.y = -1;
}

// static
bool GameBoard::isInBounds(const int y, const int x)
{
	return y >= 0 && y < 8 && x >= 0 && x < 8;
}

void GameBoard::print()
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (_board[y][x])
				std::cout << _board[y][x]->getId() << " ";
			else
				std::cout << ". ";
		}
		std::cout << std::endl;
	}
}

AFigure ***GameBoard::getBoard() const
{
	return _board;
}
