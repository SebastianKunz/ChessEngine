#include "Figures/Queen.h"

Queen::Queen(const int y, const int x, const char color, FigureLoader *loader)
	: AFigure(y, x, color, Figure::QUEEN, loader) {}

bool Queen::canMoveTo(const int y, const int x, AFigure ***board)
{
	const int absX = abs(x - this->x);
	const int absY = abs(y - this->y);

	bool ret = false;

	if (absX == 0 && absY != 0)
		ret = canMoveInDirStraight(y < this->y, absY, absX, board);
	else if (absX != 0 && absY == 0)
		ret = canMoveInDirStraight(x < this->x, absY, absX, board);

	if (!ret)
	{
		if (absX != absY || absX == 0 || absY == 0)
			return false;
		ret = canMoveInDirCross(x < this->x, y < this->y, absY, absX, board);
	}

	return ret;
}

bool Queen::canMoveInDirStraight(const bool flip, const int limitY, const int limitX, AFigure ***board) const
{
	char dir = flip ? -1 : 1;
	for (int y = 1; y <= limitY; y++)
	{
		if (board[this->y + y * dir][this->x])
		{
			if (board[this->y + y * dir][this->x]->getColor() == color)
				return false;
			if (y + 1 <= limitY)
				return false;
			break ;
		}
	}
	for (int x = 1; x <= limitX; x++)
	{
		if (board[this->y][this->x + x * dir])
		{
			if (board[this->y][this->x + x * dir]->getColor() == color)
				return false;
			if (x + 1 <= limitX)
				return false;
			break ;
		}
	}
	return true;
}

bool Queen::canMoveInDirCross(const bool flipX, const bool flipY, const int limitY, const int limitX, AFigure ***board) const
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

std::vector<SDL_Point> Queen::getAllPossibleMoves(AFigure ***board)
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