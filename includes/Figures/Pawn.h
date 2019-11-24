#ifndef PAWN_H
# define PAWN_H

#include "AFigure.h"

// Implementation of Pawn figure
class Pawn : public AFigure
{
	public:
		Pawn(const int y, const int x, const char color, FigureLoader *loader);
		~Pawn() = default;

		// Calls isLegalMove but also sets _isFirstMove
		bool canMoveTo(const int y, const int x, AFigure ***board) override;

		std::vector<SDL_Point> getAllPossibleMoves(AFigure ***board) override;

		bool isLegalMove(const int y, const int x, AFigure ***board) const;

	private:

		// Pawns can move differently on their first move
		bool _isFirstMove;
};

#endif