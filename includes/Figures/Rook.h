#ifndef ROOK_H
# define ROOK_H

#include "AFigure.h"

class Rook : public AFigure
{
	public:
		Rook(const int y, const int x, const char color, FigureLoader *loader);
		~Rook() = default;

		bool canMoveTo(const int y, const int x, AFigure ***board) override;

		std::vector<SDL_Point> getAllPossibleMoves(AFigure ***board) override;

		bool canMoveInDir(const bool flip, const int limitY, const int limitX, AFigure ***board) const;

	private:

};

#endif
