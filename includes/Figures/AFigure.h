#ifndef AFIGURE_H
# define AFIGURE_H

#include "../FigureLoader.h"

// Abstract class for figures
class AFigure
{
	public:

		// Does not take ownership of loader
		AFigure(const int y, const int x, const char color, Figure id, FigureLoader *loader);

		virtual ~AFigure() = default;

		// draws figure at current position
		bool draw();

		// Tries to move the figure to | row | | col |.
		// Returns true on success and false on failure
		bool moveTo(const int y, const int x, AFigure ***board);

		// Getter for id attribute
		Figure getId() const;

		// Getter for color attribute
		char getColor() const;

		// returns vector<SDL_Point> of possible moves
		virtual std::vector<SDL_Point> getAllPossibleMoves(AFigure ***board) = 0;

		// Returns bool wether the Figure can move to | row | | col |
		virtual bool canMoveTo(const int row, const int col, AFigure ***board) = 0;


	protected:

		// y position on board
		int y;

		// x position on board
		int x;

		// -1 = black, 1 = white
		char color;

		// instance of Figureloader, does not take ownership
		FigureLoader *loader;

		// identifier for figure
		Figure figureId;

		// Actually moves the figure to | row | | col |
		void move(const int row, const int col, AFigure ***board);

	private:
};

#endif
