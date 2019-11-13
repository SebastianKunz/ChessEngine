#include "FigureLoader.h"

FigureLoader::FigureLoader(SDL_Renderer *renderer, int spriteW, int spriteH) :
	_renderer(renderer), _spriteW(spriteW), _spriteH(spriteH)
{
}

FigureLoader::~FigureLoader()
{
	releaseImage();
}

bool FigureLoader::loadImage(const char *file)
{
	_image = IMG_Load(file);
	if (!_image)
		return false;
	_texture = SDL_CreateTextureFromSurface(_renderer, _image);

	if (!_texture)
		return false;

	return true;
}

bool FigureLoader::releaseImage()
{
	SDL_DestroyTexture(_texture);
	SDL_FreeSurface(_image);

	return true;
}

bool FigureLoader::copyFigureToRenderer(Figure figure, SDL_Rect *dstRect, char color)
{
	SDL_Rect srcRect { 0, color == 1 ? _spriteH : 0, _spriteW, _spriteH };

	switch (figure)
	{
	case Figure::PAWN:
		srcRect.x = _spriteW * 5;
		break;
	case Figure::ROOK:
		srcRect.x = _spriteW * 0;
		break;
	case Figure::KNIGHT:
		srcRect.x = _spriteW * 1;
		break;
	case Figure::BISHOP:
		srcRect.x = _spriteW * 2;
		break;
	case Figure::QUEEN:
		srcRect.x = _spriteW * 4;
		break;
	case Figure::KING:
		srcRect.x = _spriteW * 3;
		break;

	default:
		break;
	}

	return	SDL_RenderCopy(_renderer, _texture, &srcRect, dstRect) == 0;
}
