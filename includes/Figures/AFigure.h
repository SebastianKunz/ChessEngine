#ifndef AFIGURE_H
# define AFIGURE_H

#include "../FigureLoader.h"

class AFigure
{
	public:

		// Does not take ownership of loader
		AFigure(const int y, const int x, const char color, Figure id, FigureLoader *loader);
		virtual ~AFigure();
		bool draw();

		// Tries to move the figure to | row | | col |.
		// Returns true on success and false on failure
		bool moveTo(const int y, const int x, AFigure ***board);

		Figure getId() const;

		virtual std::vector<SDL_Point> getAllPossibleMoves(AFigure ***board) = 0;

		char getColor();

	protected:

		int y;
		int x;

		//0 = black
		char color;
		FigureLoader *loader;

		Figure figureId;

		// Actually moves the figure to | row | | col |
		void move(const int row, const int col, AFigure ***board);

		// Returns bool wether the Figure can move to | row | | col |
		virtual bool canMoveTo(const int row, const int col, AFigure ***board) = 0;

	private:
};

#endif
