#include "Figures/Bishop.h"

Bishop::Bishop(const int y, const int x, const char color, FigureLoader *loader)
	: AFigure(y, x, color, Figure::BISHOP, loader)
{

}

bool Bishop::canMoveTo(const int y, const int x, AFigure ***board)
{
	const int absX = abs(x - this->x);
	const int absY = abs(y - this->y);

	if (absX != absY || absX == 0 || absY == 0)
		return false;

	return canMoveInDir(x < this->x, y < this->y, absY, absX, board);
}

bool Bishop::canMoveInDir(const bool flipX, const bool flipY, const int limitY, const int limitX, AFigure ***board) const
{
	const char dirX = flipX ? -1 : 1;
	const char dirY = flipY ? -1 : 1;
	int toX = 1;
	int toY = 1;

	while (toX <= limitX && toY <= limitY)
	{
		if (board[this->y + toY * dirY][this->x + toX * dirX])
		{
			if (board[this->y + toY * dirY][this->x + toX * dirX]->getColor() == color)
				return false;
			if (toY + dirY <= limitX && toX + dirX <= limitY)
				return false;
		}
		toX++;
		toY++;
	}
	return true;
}

std::vector<SDL_Point> Bishop::getAllPossibleMoves(AFigure ***board)
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
