#ifndef ENGINE_H
# define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <stdlib.h>

# define BOARD_WIDTH 800
# define BOARD_HEIGHT 800

# define BOARD_ROWS 8
# define BOARD_COLS 8

# define TILE_SIZE_X BOARD_WIDTH / BOARD_COLS
# define TILE_SIZE_Y BOARD_HEIGHT / BOARD_COLS

#endif
