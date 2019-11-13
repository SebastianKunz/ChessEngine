#ifndef FIGURELOADER_H
# define FIGURELOADER_H

#include "Engine.h"

enum Figure
{
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING
};

class FigureLoader
{
	public:
		FigureLoader(SDL_Renderer *renderer, int spriteW, int spriteH);
		~FigureLoader();

		// returns id
		bool loadImage(const char *file);
		bool releaseImage();

		bool copyFigureToRenderer(Figure figure, SDL_Rect *dstRect, char color);

	private:

		SDL_Renderer *_renderer;
		SDL_Surface *_image;
		SDL_Texture	*_texture;
		int _spriteW;
		int _spriteH;
};

#endif