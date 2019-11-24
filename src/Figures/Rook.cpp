#include "Figures/Rook.h"

Rook::Rook(const int y, const int x, const char color, FigureLoader *loader)
	: AFigure(y, x, color, Figure::ROOK, loader) {}

bool Rook::canMoveTo(const int y, const int x, AFigure ***board)
{
	const int absX = abs(x - this->x);
	const int absY = abs(y - this->y);

	if (absX == 0 && absY != 0)
		return canMoveInDir(y < this->y, absY, absX, board);
	else if (absX != 0 && absY == 0)
		return canMoveInDir(x < this->x, absY, absX, board);
	else
		return false;
	return false;
}

bool Rook::canMoveInDir(const bool flip, const int limitY, const int limitX, AFigure ***board) const
{
	char dir = flip ? -1 : 1;
	// Checks if you can move up/down
	for (int y = 1; y <= limitY; y++)
	{
		if (board[this->y + y * dir][this->x])
		{
			if (board[this->y + y * dir][this->x]->getColor() == color)
				return false;
			// make sure that it is last move, because we cannot capture figures behind figures
			if (y + 1 <= limitY)
				return false;
			break ;
		}
	}
	// same for x
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

std::vector<SDL_Point> Rook::getAllPossibleMoves(AFigure ***board)
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

