#ifndef BISHOP_H
# define BISHOP_H

#include "AFigure.h"

class Bishop : public AFigure
{
	public:
		Bishop(const int y, const int x, const char color, FigureLoader *loader);
		~Bishop() = default;

		bool canMoveTo(const int y, const int x, AFigure ***board) override;

		std::vector<SDL_Point> getAllPossibleMoves(AFigure ***board) override;

	private:
};

#endif
