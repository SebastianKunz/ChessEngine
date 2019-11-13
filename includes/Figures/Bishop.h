#ifndef BISHOP_H
# define BISHOP_H

#include "AFigure.h"

class Bishop : public AFigure
{
	public:
		Bishop(const int y, const int x, const char color, FigureLoader *loader);
		~Bishop() = default;

		bool canMoveTo(const int y, const int x, AFigure ***board) override;

		/*
			flipY: is the moving direction up or down?
			flipX: is the moving direction left or right?
		*/
		bool canMoveInDir(const bool flipY, const bool flipX,
			const int limitY, const int limitX, AFigure ***board) const;

		std::vector<SDL_Point> getAllPossibleMoves(AFigure ***board) override;

	private:
};

#endif
