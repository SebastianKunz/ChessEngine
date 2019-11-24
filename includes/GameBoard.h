
#ifndef GAMEBOARD_H
# define GAMEBOARD_H

#include "Figures/AFigure.h"

// Defines the offset in Pixel for the board positions (1, 2, 3, .. A, B, C, ...)
# define BOARD_SIDES_PX 50

enum MoveAction
{
	CAPTURE,
	FAIL,
	MOVE
};

// Representation of the gameboard
class GameBoard
{
	public:
		GameBoard(SDL_Renderer *renderer);
		~GameBoard();

		// Draws the gameboard and all highlights
		void draw();

		MoveAction moveFigureTo(const int fromY, const int fromX,
			const int toY, const int toX);

		bool setHighlightedTile(const int y, const int x);
		void unHighlightTile();

		void print();

		// static, check if | y | | x | are inside of the gameboards boundries
		static bool isInBounds(const int y, const int x);

		AFigure ***getBoard() const;

		bool isCheck();

	private:

		// The state of the board
		AFigure ***_board;

		SDL_Renderer *_renderer;
		FigureLoader *_loader;

		// currently highlighted tile
		SDL_Point _highlightedTile;

		TTF_Font *_font20;
};

#endif