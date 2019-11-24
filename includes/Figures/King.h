#pragma once
#include "AFigure.h"

// Implementation of King figure
class King : public AFigure
{
	public:
		King(const int y, const int x, const char color, FigureLoader *loader);
		~King() = default;

		bool canMoveTo(const int y, const int x, AFigure ***board) override;

		std::vector<SDL_Point> getAllPossibleMoves(AFigure ***board) override;

	private:

};
