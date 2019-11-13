#ifndef PAWN_H
# define PAWN_H

#include "AFigure.h"

class Pawn : public AFigure
{
	public:
		Pawn(const int y, const int x, const char color, FigureLoader *loader);
		~Pawn() = default;

		/*
			Pawns can move forward one square, if that square is unoccupied.
			If it has not yet moved, the pawn has the option of moving two squares forward
			provided both squares in front of the pawn are unoccupied.
			A pawn cannot move backward. Pawns are the only pieces
			that capture differently from how they move.
			They can capture an enemy piece on either of the two spaces
			adjacent to the space in front of them
			(i.e., the two squares diagonally in front of them)
			but cannot move to these spaces if they are vacant.
		*/
		bool canMoveTo(const int y, const int x, AFigure ***board) override;

		std::vector<SDL_Point> getAllPossibleMoves(AFigure ***board) override;

		bool isLegalMove(const int y, const int x, AFigure ***board) const;

		void inline setFirstMove(bool flag);

	private:

		bool _isFirstMove;
};

#endif