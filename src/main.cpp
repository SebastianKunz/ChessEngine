#include "GameBoard.h"
#include "FigureLoader.h"
#include <iostream>

#include "Engine.h"

SDL_Window *g_window;
SDL_Renderer *g_renderer;

int get_events(SDL_Event *event)
{
}

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
    g_window = SDL_CreateWindow
    (
        "Chess", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    // Setup renderer
    g_renderer =  SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	GameBoard board(g_renderer);

	SDL_Event event;
	char quit = 0;
	bool isHighlight = true;
	int prevX = -1;
	int prevY = -1;
	while(!quit)
	{
		SDL_WaitEvent(&event);
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
					int x = bEve.x / 100;
					int y = bEve.y / 100;
					// if (x == prevX && y == prevY)
					// {
					// 	board.highlightTile(-1, -1);
					// }
					if (isHighlight)
					{
						board.highlightTile(y, x);
						prevX = x;
						prevY = y;
						isHighlight = false;
					}
					else
					{
						MoveAction action = board.moveFigureTo(prevY, prevX, y, x);
						board.print();
						if (action == MoveAction::FAIL)
						{
							std::cerr << "Unable to move figure" << std::endl;
						}
						else if (action == MoveAction::CAPTURE)
						{
							std::cout << "Captured figure" << std::endl;
						}
						else
						{
							// MOVE
							std::cout << "Moved figure" << std::endl;
						}
						isHighlight = true;
					}
				}
				break;
		}
		board.draw();

		// Render the rect to the screen
		SDL_RenderPresent(g_renderer);
	}

	SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    SDL_Quit();

    return EXIT_SUCCESS;
}