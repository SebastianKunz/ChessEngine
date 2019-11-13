#pragma once

#include "AFigure.h"

class Knight : public AFigure
{
	public:
		Knight(const int y, const int x, const char color, FigureLoader *loader);
		~Knight() = default;

		bool canMoveTo(const int y, const int x, AFigure ***board) override;

		std::vector<SDL_Point> getAllPossibleMoves(AFigure ***board) override;

	private:
};
