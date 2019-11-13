#ifndef ENGINE_H
# define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

# define DEBUG_C (x) {std::cout << x << std::endl}

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 800

# define BOARD_ROWS 8
# define BOARD_COLS 8

# define TILE_SIZE_X SCREEN_WIDTH / BOARD_COLS
# define TILE_SIZE_Y SCREEN_WIDTH / BOARD_COLS

#endif
