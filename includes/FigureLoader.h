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

// Loads a sprite image and copies to renderer
class FigureLoader
{
	public:
		FigureLoader(SDL_Renderer *renderer, int spriteW, int spriteH);
		~FigureLoader();

		// tries to load image from at path
		bool loadImage(const char *path);

		// releases current image
		bool releaseImage();

		// copies corresponding figure image to renderer
		bool copyFigureToRenderer(Figure figure, SDL_Rect *dstRect, char color);

	private:

		// The renderer to copy to
		SDL_Renderer *_renderer;

		// The loaded image
		SDL_Surface *_image;

		// The SDL texture that gets copied
		SDL_Texture	*_texture;

		// The width of one sprite image
		int _spriteW;

		// The height of one sprite image
		int _spriteH;
};

#endif