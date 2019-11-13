#include "Figures/Rook.h"

Rook::Rook(const int y, const int x, const char color, FigureLoader *loader)
	: AFigure(y, x, color, Figure::ROOK, loader)
{

}

bool Rook::canMoveTo(const int y, const int x, AFigure ***board)
{
	const int moveX = x - this->x;
	const int absX = abs(moveX);
	const int moveY = y - this->y;
	const int absY = abs(moveY);
	bool ret = true;

	if (absX == 0 && absY != 0)
	{
		if (moveY > 0)
		{
			for (int i = 1; i <= absY; i++)
			{
				if (board[this->y + i][this->x])
				{
					if (board[this->y + i][this->x]->getColor() == color)
						ret = false;
					if (i + 1 <= absY)
						ret = false;
					break ;
				}
			}
		}
		else
		{
			for (int i = 1; i <= absY; i++)
			{
				if (board[this->y - i][this->x])
				{
					if (board[this->y - i][this->x]->getColor() == color)
						ret = false;
					if (i + 1 <= absY) // check if there desired pos is not yet reached
						ret = false;
					break ;
				}
			}
		}
	}
	else if (absX != 0 && absY == 0)
	{
		if (x > this->x)
		{
			for (int i = 1; i <= absX; i++)
			{
				if (board[this->y][this->x + i])
				{
					if (board[this->y][this->x + i]->getColor() == color)
						ret = false;
					if (i + 1 <= absX) // check if there desired pos is not yet reached
						ret = false;
					break ;
				}
			}
		}
		else
		{
			for (int i = 1; i <= absX; i++)
			{
				if (board[this->y][this->x - i])
				{
					if (board[this->y][this->x - i]->getColor() == color)
						ret = false;
					if (i + 1 <= absX) // check if there desired pos is not yet reached
						ret = false;
					break ;
				}
			}
		}
	}
	else
		return false;

	return ret;
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

