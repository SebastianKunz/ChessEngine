#pragma once
#include "AFigure.h"

class Queen : public AFigure
{
	public:
		Queen(const int y, const int x, const char color, FigureLoader *loader);
		~Queen() = default;

		bool canMoveTo(const int y, const int x, AFigure ***board) override;

		bool canMoveInDirStraight(const bool flip, const int limitY,
			const int limitX, AFigure ***board) const;

		bool canMoveInDirCross(const bool flipX, const bool flipY,
			const int limitY, const int limitX, AFigure ***board) const;

		std::vector<SDL_Point> getAllPossibleMoves(AFigure ***board) override;

	private:

};
