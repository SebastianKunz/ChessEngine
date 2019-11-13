
#ifndef GAMEBOARD_H
# define GAMEBOARD_H

#include "Figures/AFigure.h"

enum MoveAction
{
	CAPTURE,
	FAIL,
	MOVE
};

class GameBoard
{
	public:
		GameBoard(SDL_Renderer *renderer);
		~GameBoard();
		void draw();
		MoveAction moveFigureTo(const int fromY, const int fromX,
			const int toY, const int toX);

		bool highlightTile(const int y, const int x);

		void print();

		static bool isInBounds(const int y, const int x);

	private:

		AFigure ***_board;

		SDL_Renderer *_renderer;
		FigureLoader *_loader;

		SDL_Point _highlightedTile;
};

#endif