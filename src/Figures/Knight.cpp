#include "Figures/Knight.h"

Knight::Knight(const int y, const int x, const char color, FigureLoader *loader)
	: AFigure(y, x, color, Figure::KNIGHT, loader) {}

bool Knight::canMoveTo(const int y, const int x, AFigure ***board)
{
	const int absX = abs(x - this->x);
	const int absY = abs(y - this->y);

	if (board[y][x] && board[y][x]->getColor() == color)
		return false;

	return (absX == 2 && absY == 1) || (absX == 1 && absY == 2);
}

std::vector<SDL_Point> Knight::getAllPossibleMoves(AFigure ***board)
{
	std::vector<SDL_Point> moves;
	// this is just for debugging
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (canMoveTo(y, x, board))
				moves.push_back({x, y});
		}
	}
	return moves;
}
