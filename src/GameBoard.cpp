#include "Engine.h"
#include "GameBoard.h"
#include "Figures.h"

GameBoard::GameBoard(SDL_Renderer *renderer) : _renderer(renderer), _highlightedTile({-1, -1})
{
	_loader = new FigureLoader(renderer, 56, 60);

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

			if ((y == 0 || y == 7) && (x == 2 || x == 5))
			{
				_board[y][x] = new Bishop(y, x, color, _loader);
			}

			if ((y == 0 || y == 7) && x == 4)
			{
				_board[y][x] = new King(y, x, color, _loader);
			}
			if ((y == 0 || y == 7) && x == 3)
			{
				_board[y][x] = new Queen(y, x, color, _loader);
			}


			if ((x == 0 || x == 7) && (y == 0 || y == 7))
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

void GameBoard::draw()
{
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255 );

	SDL_RenderClear(_renderer);
	std::vector<SDL_Point> moves;
	if (isInBounds(_highlightedTile.y, _highlightedTile.x) &&
		 _board[_highlightedTile.y][_highlightedTile.x])
			moves = _board[_highlightedTile.y][_highlightedTile.x]->getAllPossibleMoves(_board);

	for (int y = 0; y < 800; y += 100)
	{
		bool offY = y % 200 == 0;
		for (int x = 0; x < 800; x += 100)
		{
			bool off = x % 200 == 0;
			if (offY)
				off = !off;
			SDL_Rect r;
			r.x = x;
			r.y = y;
			r.w = 100;
			r.h = 100;

			// Set render color to blue ( rect will be rendered in this color )
			const int boardX = x / 100;
			const int boardY = y / 100;
			if (boardX == _highlightedTile.x && boardY == _highlightedTile.y)
			{
				SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255 );
			}
			else
			{
				bool isPossibleMove = false;
				for(auto const& move: moves) {
					if (move.x == boardX && move.y == boardY) {
						isPossibleMove = true;
						break;
					}
				}
				if (isPossibleMove) {
					SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 100);
				}
				else
				{
					if (off)
						SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255 );
					else
						SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255 );
				}
			}
			// Render rect
			SDL_RenderFillRect(_renderer, &r );
		}
	}

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
	highlightTile(-1, -1);
	if (!_board[fromY][fromX])
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

bool GameBoard::highlightTile(const int y, const int x)
{
	_highlightedTile.x = x;
	_highlightedTile.y = y;
	return true;
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
