#include "Figures/AFigure.h"
#include "GameBoard.h"

AFigure::AFigure(const int _y, const int _x, const char _color, Figure id, FigureLoader *_loader)
	: figureId(id), y(_y), x(_x), color(_color), loader(_loader)
{
}

AFigure::~AFigure()
{

}

Figure AFigure::getId() const
{
	return figureId;
}

bool AFigure::moveTo(const int y, const int x, AFigure ***board)
{
	if (!GameBoard::isInBounds(y, x))
		return false;
	if (canMoveTo(y, x, board))
		move(y, x, board);
	else
		return false;
	return true;
}

void AFigure::move(const int y, const int x, AFigure ***board)
{
	this->y = y;
	this->x = x;

	board[y][x] = this;
}

char AFigure::getColor()
{
	return color;
}

bool AFigure::draw()
{
	SDL_Rect dst;
	dst.h = 100;
	dst.w = 100;
	dst.x = this->x * TILE_SIZE_X;
	dst.y = this->y * TILE_SIZE_Y;
	return loader->copyFigureToRenderer(figureId, &dst, color);
}
