#include "Figures/Rook.h"

Rook::Rook(const int y, const int x, const char color, FigureLoader *loader)
	: AFigure(y, x, color, Figure::ROOK, loader)
{

}

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
	// for (int _x = x + 1; _x < 8; _x++) {
	// 	if (!board[y][_x] || (board[y][_x] && board[y][_x]->getColor() != color))
	// 		moves.push_back({_x, y});
	// 	if (board[y][_x])
	// 		break;
	// }
	// for (int _x = x - 1; _x >= 0; _x--) {
	// 	if (!board[y][_x] || (board[y][_x] && board[y][_x]->getColor() != color))
	// 		moves.push_back({_x, y});
	// 	if (board[y][_x])
	// 		break;
	// }
	// for (int _y = y + 1; _y < 8; _y++) {
	// 	if (!board[_y][x] || (board[_y][x] && board[_y][x]->getColor() != color))
	// 		moves.push_back({x, _y});
	// 	if (board[_y][x])
	// 		break;
	// }
	// for (int _y = y - 1 < 0 ? 8 : y - 1; _y < 8; _y++) {
	// 	if (!board[_y][x] || (board[_y][x] && board[_y][x]->getColor() != color))
	// 		moves.push_back({x, _y});
	// 	if (board[_y][x])
	// 		break;
	// }
	return moves;
}

