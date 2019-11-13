#include "Figures/Bishop.h"

Bishop::Bishop(const int y, const int x, const char color, FigureLoader *loader)
	: AFigure(y, x, color, Figure::BISHOP, loader)
{

}

bool Bishop::canMoveTo(const int y, const int x, AFigure ***board)
{
	true;
}

std::vector<SDL_Point> Bishop::getAllPossibleMoves(AFigure ***board)
{
	std::vector<SDL_Point> moves;
	return moves;
}
