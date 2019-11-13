#include "Figures/Pawn.h"

#include "GameBoard.h"

Pawn::Pawn(const int y, const int x,
	const char color, FigureLoader *loader)
	: AFigure(y, x, color, Figure::PAWN, loader),
	_isFirstMove(true)
{

}

bool Pawn::isLegalMove(const int y, const int x, AFigure ***board) const {
	if (!GameBoard::isInBounds(y, x))
		return false;

	const int moveX = x - this->x;
	const int absX = abs(moveX);
	const int moveY = color * (this->y - y);

	// capture
	if (board[y][x] && absX == 1 && moveY == 1 && board[y][x]->getColor() != color)
	{
		return true;
	}

	if (moveX != 0 || moveY <= 0)
		return false;

	if (_isFirstMove) {
		if (moveY == 1 && !board[y][x])
			return true;
		else if (moveY == 2 && !board[y][x] && GameBoard::isInBounds(y - 1, x) && !board[y - 1][x])
			return true;
		return false;
	}
	else
	{
		return moveY == 1 && absX == 0 && !board[y][x];
	}

	return false;
}

bool Pawn::canMoveTo(const int y, const int x, AFigure ***board)
{
	bool ret = isLegalMove(y, x, board);
	_isFirstMove = false;

	return ret;
}

void Pawn::setFirstMove(bool flag)
{
	_isFirstMove = flag;
}

std::vector<SDL_Point> Pawn::getAllPossibleMoves(AFigure ***board)
{
	std::vector<SDL_Point> moves;

	// this is just for debugging
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (isLegalMove(y, x, board))
				moves.push_back({x, y});
		}
	}
	return moves;


	if (isLegalMove(x, y + 1, board)) {
		moves.push_back({x, y + 1});
	}
	if (isLegalMove(x, y + 2, board)) {
		moves.push_back({x, y + 2});
	}
	if (isLegalMove(x + 1, y + 1, board)) {
		moves.push_back({x + 1, y + 1 * color});
	}
	if (isLegalMove(x - 1, y + 1, board)) {
		moves.push_back({x - 1, y + 1 * color});
	}

	return moves;
}
