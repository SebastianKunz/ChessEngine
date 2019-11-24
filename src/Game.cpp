#include "Game.h"

Game::Game() : _renderer(nullptr), _window(nullptr), _board(nullptr), _uic(nullptr),
	_isInit(false) {}

Game::~Game()
{
	if (_board)
		delete _board;
	if (_uic)
		delete _uic;
	SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

bool Game::init()
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	_window = SDL_CreateWindow
    (
        "Chess by Skunz", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        BOARD_WIDTH + 300 + BOARD_SIDES_PX,
        BOARD_HEIGHT + BOARD_SIDES_PX,
        SDL_WINDOW_SHOWN
    );
    _renderer =  SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	_board = new GameBoard(_renderer);
	_uic = new UiController(_renderer);
	if (!_uic->init())
	{
		delete _board;
		_board = nullptr;
		delete _uic;
		_uic = nullptr;
		SDL_DestroyRenderer(_renderer);
		SDL_DestroyWindow(_window);
		return false;
	}

	_isInit = true;
	return true;
}

bool Game::start()
{
	if (_isInit)
		return false;
	if (!init())
		return false;

	SDL_Event event;
	char quit = 0;
	bool isHighlight = true;
	int prevX = -1;
	int prevY = -1;
	while(!quit)
	{
		SDL_WaitEvent(&event);
		// if (isCheck())
		// 	std::cout << "CHECK" << std::endl;
		switch (event.type)
		{
			case SDL_QUIT:
				quit = 1;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_q:
						quit = 1;
						break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				auto bEve = event.button;
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					int x = (bEve.x - 50) / 100;
					int y = bEve.y / 100;

					if (!GameBoard::isInBounds(y, x))
						break;

					if (isHighlight)
					{
						auto boardRef = _board->getBoard();
						if (boardRef[y][x] && boardRef[y][x]->getColor() == _whitesTurn)
						{
							_board->setHighlightedTile(y, x);
							prevX = x;
							prevY = y;
							isHighlight = false;
						}
						else
						{
							_uic->addDisplayMessage({"It's not your turn", LogMessageLevel::ERROR});
						}
					}
					else
					{
						isHighlight = true;
						if (prevX == x && prevY == y)
						{
							_board->unHighlightTile();
							break ;
						}

						MoveAction action = _board->moveFigureTo(prevY, prevX, y, x);

						if (action == MoveAction::FAIL)
						{
							_uic->addDisplayMessage({"Unable to move figure", LogMessageLevel::ERROR});
						}
						else if (action == MoveAction::CAPTURE)
						{
							_uic->addDisplayMessage({"Captured Figure", LogMessageLevel::OK});
							_whitesTurn = _whitesTurn == 1 ? -1 : 1;
							_uic->switchTurn();
						}
						else
						{
							// MOVE
							_whitesTurn = _whitesTurn == 1 ? -1 : 1;
							_uic->addDisplayMessage({"Moved figure", LogMessageLevel::OK});
							_uic->switchTurn();
						}
					}
				}
				break;
		}
		_board->draw();
		_uic->draw();

		// Render the rect to the screen
		SDL_RenderPresent(_renderer);
		SDL_RenderClear(_renderer);
	}

}

bool Game::isWhitesTurn() const
{
	return _whitesTurn == -1;
}

bool Game::isCheck()
{
	SDL_Point kingPos;
	auto board = _board->getBoard();
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (board[y][x] && board[y][x]->getColor() == _whitesTurn && board[y][x]->getId() == Figure::KING)
			{
				kingPos.x = x;
				kingPos.y = y;
				break ;
			}
		}
	}

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (board[y][x])
				if (board[y][x]->canMoveTo(kingPos.y, kingPos.x, board))
					return true;
		}
	}

	return false;
}